# # Importing Libraries
import serial
import time
import threading

arduino = serial.Serial(port='/dev/ttyS5', baudrate=115200, timeout=1)  # connect to the arduino

class Monitor(threading.Thread):
    """
    class: monitors all information sent from the arduino, and logs it to a file to be read using a command tool like tail -f
    """
    def __init__(self, monitor_callback=None, name='monitor-output-thread'):
        """
        initialize the motor class
        parameters:
            monitor_callback: a callback function to obtain extra information from the main thread
            name: the name of the thread
        """
        self.monitor_callback = monitor_callback
        super(Monitor, self).__init__(name=name)
        self.start() # start the thread

    def run(self):
        """
        code to execute on thread start()
        """
        with open("monitor_log.txt", "w") as f:
            # monitor_callback()  # callback in case extra information is needed
            while True:
                try:  # use try and except block to remove warnings when arduino sends unreadable information
                    data = arduino.readline().decode('utf-8')  # decode serial information from the arduino
                    if data:
                        f.write(data)  # write information to the file
                        f.flush()  # ensure that this information is flushed to read it live through the tail -f command
                except:
                    pass


def monitor_callback(inp):
    """
    callback function: does nothing
    """
    pass

monitor_thread = Monitor(monitor_callback)  # initialize a thread for monitoring the arduino

##
import multiprocessing
import time
import os

"""
commands:
    stop: stops the program indefinitely until another command is run
    pause: pauses for 2 seconds
    normal: the normal mode for washing clothes
    quick: quickly washes the clothes
    gentle: washes the clothes at a slow pace
    test: testing in both forward and backwards directions
    terminate: stop the program
"""

medium = 50
high = 75
slow = 25

commands = {
        "stop": [[0, -1]],
        "pause": [[0, 2]],
        "normal": ["pause", [medium, 4], [-medium, 4], [high, 2], "stop"],
        "quick": ["pause", [medium, 2], [-medium, 2], [high, 2], "stop"],
        "gentle": ["pause", [slow, 4], [-slow, 4], [medium, 2], "stop"],
        "test": [[100, 3], [0, 3], [-100, 3], [0, 3]]
        }


def threadWrite(command):
    """
    function: takes a command and parses it before sending it to the arduino
    parameters:
        command: command to execute (string - key of the commands dictionary, or list of the form [speed, delay])
    """
    with open("write_log.txt", "a") as f:  # open a file to write the output log
        def sleep(delay):
            """
            function: a custom delay function that listens to potential interrupted commands
            parameters:
                delay: delay in seconds (can be -1, meaning forever)
            """
            step = 0.001  # quantized delay step time
            number = int(delay / step)  # number of quantized delay steps
            i = 0  # initialize a counter
            while i != number:  # while i does not equal to the number
                i += 1  # increment i, by one,
                time.sleep(step)  # sleep for the quantized delay step time
                if exit_now:  # if the exit_now variable is set (i.e., a new command has been set, exit the sleep function)
                    return

        def execute(speed, delay):
            """
            function: executes a command
            parameters:
                speed: speed (RPM) [-100, 100], negative values denote reverse direction, and positive values denote forward direction
                delay: delay in seconds (can be -1, meaning forever)
            """
            f.write(f"set speed: {speed}, delay: {delay}\n")  # logging speed and delay
            arduino.write(bytes(str(speed), 'utf-8'))  # writing the speed to the arduino
            f.flush() # ensure that this information is flushed to read it live through the tail -f command
            sleep(delay) # keep this speed for the time specified by delay
            if exit_now: #if the exit_now variable is set (i.e., a new command has been set, exit the sleep function)
                return

        def recursiveExecute(command_):
            """
            function: parses and executes a command
            """
            if type(command_) == int:  # if the command is just an integer
                execute(command_, -1)  # execute the command, and use -1 to denote that this runs forever
                return  # finish quietly when interrupted
            for value in commands[command_]:  # loop through the commands in the dictionary value list
                if type(value) == str:  # if the value is of type String
                    recursiveExecute(value)  # call the function recursively
                elif type(value) == list:  # list of type: speed (RPM), and delay (s)
                    execute(*value)  # execute the command
                if exit_now:  # if the exit_now variable is set (i.e., a new command has been set, exit the sleep function)
                   return

        f.write(f"performing {command}\n")  # write to the write_log file that the command is executing
        f.flush(); os.fsync(f.fileno())  # flush to the file, and sync the file for live viewing
        if exit_now or command == "terminate":  # if the command is terminate, or the thread is to terminate
            return  # exit from the function
        recursiveExecute(command)  # call the execution function to parse and execute the command


def isInt(string):
    """
    function: check if a string is an integer
    parameters:
        string: a variable of type "str"
        returns:
            boolean: true if string is an integer, else false
    """
    try:
        int(string)
        return True
    except:
        return False


def getCommand():
    """
    gets a command checks if it is legitimate and returns the command
    """
    while True:  # loop infinitely
        command = input("provide a command here: ")  # ask for a command
        if command in commands or command == "terminate":  # if the command is in the dictionary, or it is "terminate"
            return command
        elif isInt(command):  # if the command is an integer
            return int(command)  # return the command in integer form
        else:
            print("invalid command, invoke GUI or type one of the following: ")  # otherwise raise a warning
            print(", ".join(commands.keys()))  # show the available options



command_thread = None  # initialize the command_thread variable (the commandWrite thread responsible for sending commands to the arduino)
while True:
    command = getCommand()  # obtain a legitimate command
    exit_now = True  # set the exit_now variable to true to exit any threads executing the commandWrite function
    if command_thread:
        command_thread.join()  # wait for the commandWrite thread to finish if it exits
    exit_now = False  # set the exit_now variable to false to ensure that the new thread does not exit immediately
    command_thread = threading.Thread(target=threadWrite, args=(command,))  # initialize the new thread
    command_thread.start()  # start the thread
    if command == "terminate":  # if the command is terminate, exit the while loop, and finish the program
        break



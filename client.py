# # Importing Libraries
import serial
import time
import threading

arduino = serial.Serial(port='/dev/ttyS5', baudrate=115200, timeout=1)

class Monitor(threading.Thread):
    def __init__(self, monitor_callback=None, name='monitor-output-thread'):
        self.monitor_callback = monitor_callback
        super(Monitor, self).__init__(name=name)
        self.start()

    def run(self):
        with open("monitor_log.txt", "w") as f:
            # monitor_callback() # you can get something from the callback here if you need extra information
            while True:
                try:
                    data = arduino.readline().decode('utf-8')
                    if data:
                        f.write(data)
                        # f.write(data + "\n")
                        f.flush()
                except:
                    pass


def monitor_callback(inp):
    pass

monitor_thread = Monitor(monitor_callback)

##
import multiprocessing
import time
import os

commands = {
        "pause": [[0, 2]],
        "quick cycle": ["pause", [100, 5], "pause"],
        "regular wash": ["pause", [100, 10], "pause"],
        "test": [[100, 3], [0, 3], [-100, 3], [0, 3]]
        }


def threadWrite(command):
    with open("write_log.txt", "a") as f:
        def sleep(delay):
            step = 0.001
            number = int(delay / step)  # set number to negative value to loop forever
            i = 0
            while i != number:
                i += 1
                time.sleep(step)
                if exit_now:
                    return

        def execute(speed, delay):
            f.write(f"set speed: {speed}, delay: {delay}\n")
            arduino.write(bytes(str(speed), 'utf-8'))
            f.flush()
            sleep(delay)
            if exit_now:
                return

        def recursiveExecute(command_):
            if type(command_) == int:
                execute(command_, -1)
                return # finish quietly when interrupted
            for value in commands[command_]:
                if type(value) == str:
                    recursiveExecute(value)
                elif type(value) == list: # list of type: speed (RPM), and delay (s)
                    execute(*value)
                if exit_now:
                   return

        f.write(f"performing {command}\n")
        f.flush(); os.fsync(f.fileno())
        if exit_now or command == "terminate":
            return
        recursiveExecute(command)


def isInt(string):
    try:
        int(string)
        return True
    except:
        return False


def getCommand():
    while True:
        command = input("provide a command here: ")
        if command in commands or command == "terminate":
            return command
        elif isInt(command):
            return int(command)
        else:
            print("invalid command, invoke GUI or type one of the following: ")
            print(", ".join(commands.keys()))



command_thread = None
while True:
    command = getCommand()
    exit_now = True
    if command_thread:
        command_thread.join()
    exit_now = False
    command_thread = threading.Thread(target=threadWrite, args=(command,))
    command_thread.start()
    if command == "terminate":
        break



# # Importing Libraries
import serial
import time
# arduino = serial.Serial(port='/dev/ttyS4', baudrate=115200, timeout=1)
# # arduino = serial.Serial(port='COM4', baudrate=115200, timeout=1)
# def writeRead(x):
#     arduino.write(bytes(x, 'utf-8'))
#     time.sleep(0.05)
#     data = arduino.readline()#.#decode('utf-8')
#     return data
# states = {"stop" : 0, "washing": 50, "cleaning": 70, "rest": 0, "spinning": 70}
# period = {"stop" : 1, "washing": 5, "cleaning": 5, "rest": 3, "spinning": 3}
# normal = []
# gentle = []
#
# command = input("enter a command: ")
#     # "enter an RPM" write this instead
# print(writeRead(command))
# while True:
#     data = arduino.readline()
#     print(data)
# # while True:
# #     command = input("enter a command: ")
# #     # "enter an RPM" write this instead
# #     print(writeRead(command))
#
# # while True:
# #     # time.sleep(0.05)
# #     data = arduino.readline()
# #     # data = arduino.readline().decode('utf-8')
# #     print(data)
# #     # num = input("enter a command: ") # Taking input from user
# #     # value = writeRead(num)
# #     # print(value) # printing the value
#
#
# ##


import threading

class Monitor(threading.Thread):
    def __init__(self, monitor_callback = None, name='monitor-output-thread'):
        self.monitor_callback = monitor_callback
        super(Monitor, self).__init__(name=name)
        self.start()

    def run(self):
        arduino = serial.Serial(port='/dev/ttyS4', baudrate=115200, timeout=1)
        with open("monitor_log.txt", "w") as f:
            # monitor_callback() # you can get something from the callback here if you need extra information
            while True:
                try:
                    data = arduino.readline().decode('utf-8')
                    f.write(data + "\n")
                    f.flush()
                except:
                    pass


def monitor_callback(inp):
    pass

#start the Keyboard thread
# monitor_thread = Monitor(monitor_callback)

##
import multiprocessing
import time

commands = {
        "pause": [[0, 2]],
        "quick cycle": ["pause", [100, 5], "pause"],
        "regular wash": ["pause", [100, 10], "pause"]
        }


def threadWrite(command):
    with open("write_log.txt", "w") as f:
        def sleep(delay):
            step = 0.05
            for i in range(int(delay / step)): # applying polling strategy
                time.sleep(step)
                if exit_now:
                    return

        def execute(speed, delay):
            f.write(f"set speed: {speed}, delay: {delay}\n")
            f.flush()
            sleep(delay)
            if exit_now:
                return

        def recursiveExecute(command_str):
            for value in commands[command_str]:
                if type(value) == str:
                    recursiveExecute(value)
                else: # list of type: speed (RPM), and delay (s)
                    execute(*value)
                if exit_now:
                   return

        f.write(f"performing {command}\n")
        f.flush()
        if exit_now or command == "terminate":
            return
        recursiveExecute(command)


def getCommand():
    while True:
        command = input("provide a command here: ")
        if command in commands:
            return command
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

##

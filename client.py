# # Importing Libraries
# import serial
# import time
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
        # arduino = serial.Serial(port='/dev/ttyS4', baudrate=115200, timeout=1)
        with open("log.txt", "w") as f:
            while True:
                # self.monitor_callback(input()) #waits to get input + Return
                try:
                    # data = arduino.readline().decode('utf-8')
                    data = input("input some stuff here: ")
                    if data == "finish":
                        break
                    f.write(data + "\n")
                    f.flush()
                except:
                    pass




def monitor_callback(inp):
    pass

#start the Keyboard thread
kthread = Monitor(monitor_callback)

# while True:
#     pass
#     # data = input()

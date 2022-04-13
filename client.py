# Importing Libraries
import serial
import time
arduino = serial.Serial(port='/dev/ttyS4', baudrate=115200, timeout=1)
# arduino = serial.Serial(port='COM4', baudrate=115200, timeout=1)
def writeRead(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()#.#decode('utf-8')
    return data
states = {"stop" : 0, "washing": 50, "cleaning": 70, "rest": 0, "spinning": 70}
period = {"stop" : 1, "washing": 5, "cleaning": 5, "rest": 3, "spinning": 3}
normal = []
gentle = []

command = input("enter a command: ")
    # "enter an RPM" write this instead
print(writeRead(command))
while True:
    data = arduino.readline()
    print(data)
# while True:
#     command = input("enter a command: ")
#     # "enter an RPM" write this instead
#     print(writeRead(command))

# while True:
#     # time.sleep(0.05)
#     data = arduino.readline()
#     # data = arduino.readline().decode('utf-8')
#     print(data)
#     # num = input("enter a command: ") # Taking input from user
#     # value = writeRead(num)
#     # print(value) # printing the value



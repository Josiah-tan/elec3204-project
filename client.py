# Importing Libraries
import serial
import time
arduino = serial.Serial(port='/dev/ttyS4', baudrate=115200, timeout=1)
# arduino = serial.Serial(port='COM4', baudrate=115200, timeout=1)
def writeRead(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline().decode('utf-8')
    return data

while True:
    command = input("enter a command: ")
    print(writeRead(command))
    # arduino.write(bytes(command, 'utf-8'))

# while True:
#     # time.sleep(0.05)
#     data = arduino.readline()
#     # data = arduino.readline().decode('utf-8')
#     print(data)
#     # num = input("enter a command: ") # Taking input from user
#     # value = writeRead(num)
#     # print(value) # printing the value



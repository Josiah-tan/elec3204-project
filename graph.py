# import relevant libraries
import matplotlib.pyplot as plt
import numpy as np

plots = {}  # initialize a dictionary to store all parsed information
plt.clf()  # clear all figures
with open('monitor_log.txt', 'r') as myfile:  # read from the log file
    for data in myfile:  # read line by line
        data = data.replace('\n', '')  # replace any new lines with nothing
        key, *vals = data.split(" ")  # split the key and the values
        vals = [float(val) for val in vals]  # change the values to be floats
        if key in plots:  # if the key is already in the dictionary
            plots[key].append(vals)  # add the new data to the dictionary
        else:
            plots[key] = [vals]  # create a new element in the dictionary and store the data into the dictionary

for key, val in plots.items():  # loop through all the entries in the dictionary
    val = zip(*val)  # zip all the elements in the list to transform [[x1, y1], [x2, y2]] -> [[x1, x2], [y1, y2]]
    key = key.replace(':', '')  # replace any ':' with nothing
    print(key)  # print out the key value
    if key == "referen":  # ignore referen, use 'reference', only
        continue
    plt.plot(*val, label=key, linewidth=0.5)  # plot with thinner line width (default = 1), to make more visible
# plot and save
plt.title("Motor Trajectory")
plt.ylabel("y")
plt.xlabel("x")
plt.legend()
plt.show()
plt.savefig("output.png")


import matplotlib.pyplot as plt
import numpy as np

plots = {}
plt.clf()
with open('monitor_log.txt', 'r') as myfile:
    for data in myfile:
        data = data.replace('\n', '')
        key, *vals = data.split(" ")
        vals = [float(val) for val in vals]
        if key in plots:
            plots[key].append(vals)
        else:
            plots[key] = [vals]

for key, val in plots.items():
    val = zip(*val)
    key = key.replace(':', '')
    print(key)
    plt.plot(*val, label=key, linewidth=0.5)
plt.title("Motor Trajectory")
plt.ylabel("y")
plt.xlabel("x")
plt.legend()
plt.show()
plt.savefig("output.png")

# plt.plot(range(0, 1, 100))
# plt.show()
# plt.savefig("output.png")


##


# importing the required module
import matplotlib.pyplot as plt
plt.clf()

# x axis values
x = [1,2,3]
# corresponding y axis values
y = [2,4,1]

# plotting the points
plt.plot(x, y)

# naming the x axis
plt.xlabel('x - axis')
# naming the y axis
plt.ylabel('y - axis')

# giving a title to my graph
plt.title('My first graph!')
 
 # function to show the plot
plt.show()
plt.savefig("output.png")


##


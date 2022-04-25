import matplotlib.pyplot as plt

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
    plt.plot(*val, label=key)
    plt.title("Motor Trajectory")
    plt.ylabel("y")
    plt.xlabel("x")
    plt.legend()
    plt.show()
    plt.savefig("nice.png")

"""
#vary area
x = [250, 500, 750, 1000, 1250] 
y_thruput = [617761, 464638, 236298, 208097, 94915]
y_delay = [0.033178, 0.519835, 0.452778, 0.150654, 0.020663]
y_del = [0.997158,  0.719633, 0.365618, 0.339692, 0.146384]
y_drop = [0.002067, 0.276896, 0.628437, 0.653253, 0.834856]

#vary nodes
x = [20, 40, 60, 80, 100]
y_thruput = [441130, 467503, 457747, 351962, 318310]
y_delay = [0.527618, 0.540829, 1.076952, 1.552786, 2.022063]
y_del = [0.672523, 0.753418, 0.732019, 0.558973, 0.502019]
y_drop = [0.325769, 0.243229, 0.264909, 0.436960, 0.493438]

#vary flows
x = [10, 20, 30, 40, 50]
y_thruput = [254836, 437887, 422265, 597157, 542952]
y_delay = [0.019428, 1.054755, 2.414075, 3.053429, 3.678216]
y_del = [0.851257, 0.680936, 0.429712, 0.478027, 0.338557]
y_drop = [0.148743, 0.315580, 0.567356, 0.519283, 0.658649]

"""

"""
plt.xlabel("Area Size(m)")
plt.xlabel("Number of Nodes")
plt.xlabel("Number of Flows")

plt.ylabel("Throughput(bits/sec)")
plt.ylabel("End-to-end Delay(seconds")
plt.ylabel("Delivery Ratio")
plt.ylabel("Drop Ratio")

plt.title("Area Size(m) vs Throughput(bits/sec)")
plt.title("Area Size(m) vs End-to-end Delay(seconds)")
plt.title("Area Size(m) vs Delivery Ratio")
plt.title("Area Size(m) vs Drop Ratio")

plt.title("Number of Nodes vs Throughput(bits/sec)")
plt.title("Number of Nodes vs End-to-end Delay(seconds)")
plt.title("Number of Nodes vs Delivery Ratio")
plt.title("Number of Nodes vs Drop Ratio")

plt.title("Number of Flows vs Throughput(bits/sec)")
plt.title("Number of Flows vs End-to-end Delay(seconds)")
plt.title("Number of Flows vs Delivery Ratio")
plt.title("Number of Flows vs Drop Ratio")
"""

import matplotlib.pyplot as plt

x = [10, 20, 30, 40, 50]
y = [0.148743, 0.315580, 0.567356, 0.519283, 0.658649]

plt.scatter(x, y)
plt.plot(x, y)

labels = x
plt.xticks(x, labels, rotation = "horizontal")

plt.xlabel("Number of Flows")
plt.ylabel("Drop Ratio")
plt.title("Number of Flows vs Drop Ratio")
plt.grid(True)

plt.show()

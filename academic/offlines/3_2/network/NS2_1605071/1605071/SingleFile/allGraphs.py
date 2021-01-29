import matplotlib.pyplot as plt

x_area = [250, 500, 750, 1000, 1250] 

y_thru = [617761, 464638, 236298, 208097, 94915]
plot1 = plt.figure(1)
plt.scatter(x_area, y_thru)
plt.plot(x_area, y_thru)
labels = x_area
plt.xticks(x_area, labels, rotation = "horizontal")
plt.xlabel("Area Size(m)")
plt.ylabel("Throughput(bits/sec)")
plt.title("Area Size(m) vs Throughput(bits/sec)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/areaVSthru.png')

y_delay = [0.033178, 0.519835, 0.452778, 0.150654, 0.020663]
plot2 = plt.figure(2)
plt.scatter(x_area, y_delay)
plt.plot(x_area, y_delay)
labels = x_area
plt.xticks(x_area, labels, rotation = "horizontal")
plt.xlabel("Area Size(m)")
plt.ylabel("End-to-end Delay(seconds)")
plt.title("Area Size(m) vs End-to-end Delay(seconds)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/areaVSdelay.png')

y_deli = [0.997158,  0.719633, 0.365618, 0.339692, 0.146384]
plot3 = plt.figure(3)
plt.scatter(x_area, y_deli)
plt.plot(x_area, y_deli)
labels = x_area
plt.xticks(x_area, labels, rotation = "horizontal")
plt.xlabel("Area Size(m)")
plt.ylabel("Delivery Ratio")
plt.title("Area Size(m) vs Delivery Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/areaVSdeli.png')

y_drop = [0.002067, 0.276896, 0.628437, 0.653253, 0.834856]
plot4 = plt.figure(4)
plt.scatter(x_area, y_drop)
plt.plot(x_area, y_drop)
labels = x_area
plt.xticks(x_area, labels, rotation = "horizontal")
plt.xlabel("Area Size(m)")
plt.ylabel("Drop Ratio")
plt.title("Area Size(m) vs Drop Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/areaVSdrop.png')


x_node = [20, 40, 60, 80, 100]

y_thru = [441130, 467503, 457747, 351962, 318310]
plot5 = plt.figure(5)
plt.scatter(x_node, y_thru)
plt.plot(x_node, y_thru)
labels = x_node
plt.xticks(x_node, labels, rotation = "horizontal")
plt.xlabel("Number of Nodes")
plt.ylabel("Throughput(bits/sec)")
plt.title("Number of Nodes vs Throughput(bits/sec)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/nodeVSthru.png')

y_delay = [0.527618, 0.540829, 1.076952, 1.552786, 2.022063]
plot6 = plt.figure(6)
plt.scatter(x_node, y_delay)
plt.plot(x_node, y_delay)
labels = x_node
plt.xticks(x_node, labels, rotation = "horizontal")
plt.xlabel("Number of Nodes")
plt.ylabel("End-to-end Delay(seconds)")
plt.title("Number of Nodes vs End-to-end Delay(seconds)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/nodeVSdelay.png')

y_deli = [0.672523, 0.753418, 0.732019, 0.558973, 0.502019]
plot7 = plt.figure(7)
plt.scatter(x_node, y_deli)
plt.plot(x_node, y_deli)
labels = x_node
plt.xticks(x_node, labels, rotation = "horizontal")
plt.xlabel("Number of Nodes")
plt.ylabel("Delivery Ratio")
plt.title("Number of Nodes vs Delivery Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/nodeVSdeli.png')

y_drop = [0.325769, 0.243229, 0.264909, 0.436960, 0.493438]
plot8 = plt.figure(8)
plt.scatter(x_node, y_drop)
plt.plot(x_node, y_drop)
labels = x_node
plt.xticks(x_node, labels, rotation = "horizontal")
plt.xlabel("Number of Nodes")
plt.ylabel("Drop Ratio")
plt.title("Number of Nodes vs Drop Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/nodeVSdrop.png')


x_flow = [10, 20, 30, 40, 50]

y_thruput = [254836, 437887, 422265, 597157, 542952]
plot9 = plt.figure(9)
plt.scatter(x_flow, y_thru)
plt.plot(x_flow, y_thru)
labels = x_flow
plt.xticks(x_flow, labels, rotation = "horizontal")
plt.xlabel("Number of Flows")
plt.ylabel("Throughput(bits/sec)")
plt.title("Number of Flows vs Throughput(bits/sec)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/flowVSthru.png')

y_delay = [0.019428, 1.054755, 2.414075, 3.053429, 3.678216]
plot10 = plt.figure(10)
plt.scatter(x_flow, y_delay)
plt.plot(x_flow, y_delay)
labels = x_flow
plt.xticks(x_flow, labels, rotation = "horizontal")
plt.xlabel("Number of Flows")
plt.ylabel("End-to-end Delay(seconds")
plt.title("Number of Flows vs End-to-end Delay(seconds)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/flowVSdelay.png')

y_deli = [0.851257, 0.680936, 0.429712, 0.478027, 0.338557]
plot11 = plt.figure(11)
plt.scatter(x_flow, y_deli)
plt.plot(x_flow, y_deli)
labels = x_flow
plt.xticks(x_flow, labels, rotation = "horizontal")
plt.xlabel("Number of Flows")
plt.ylabel("Delivery Ratio")
plt.title("Number of Flows vs Delivery Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/flowVSdeli.png')

y_drop = [0.148743, 0.315580, 0.567356, 0.519283, 0.658649]
plot12 = plt.figure(12)
plt.scatter(x_flow, y_drop)
plt.plot(x_flow, y_drop)
labels = x_flow
plt.xticks(x_flow, labels, rotation = "horizontal")
plt.xlabel("Number of Flows")
plt.ylabel("Drop Ratio")
plt.title("Number of Flows vs Drop Ratio")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/flowVSdrop.png')



plt.show()
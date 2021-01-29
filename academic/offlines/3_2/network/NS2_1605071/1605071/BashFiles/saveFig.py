#saves figures
import matplotlib.pyplot as plt

fhand = open('myfile.txt', 'r')

count = 0
x_area = []
y_thru = []
y_delay = []
y_deli = []
y_drop = []
for line in fhand:
    line = line.rstrip()
    x = line.split()
    word = x[0]
    if word == "Area":
        for t in x:
            try:
                x_area.append(int(t))
            except ValueError:
                pass

    elif word == "Throughput":
        for t in x:
            try:
                y_thru.append(float(t))
            except ValueError:
                pass

    elif word == "Average":
        for t in x:
            try:
                y_delay.append(float(t))
            except ValueError:
                pass

    elif word == "Delivery":
        for t in x:
            try:
                y_deli.append(float(t))
            except ValueError:
                pass

    elif word == "Drop":
        for t in x:
            try:
                y_drop.append(float(t))
            except ValueError:
                pass

    count = count + 1
    if count == 45: break

print("Varying area size:")
print(x_area)
print(y_thru)
print(y_delay)
print(y_deli)
print(y_drop)


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

print("================================================")

x_node = []
y_thru = []
y_delay = []
y_deli = []
y_drop = []
for line in fhand:
    line = line.rstrip()
    x = line.split()
    word = x[0]
    if word == "Nodes":
        for t in x:
            try:
                x_node.append(int(t))
            except ValueError:
                pass

    elif word == "Throughput":
        for t in x:
            try:
                y_thru.append(float(t))
            except ValueError:
                pass

    elif word == "Average":
        for t in x:
            try:
                y_delay.append(float(t))
            except ValueError:
                pass

    elif word == "Delivery":
        for t in x:
            try:
                y_deli.append(float(t))
            except ValueError:
                pass

    elif word == "Drop":
        for t in x:
            try:
                y_drop.append(float(t))
            except ValueError:
                pass

    count = count + 1
    if count == 90: break

print("Varying number of nodes:")
print(x_node)
print(y_thru)
print(y_delay)
print(y_deli)
print(y_drop)


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

print("================================================")

x_flow = []
y_thru = []
y_delay = []
y_deli = []
y_drop = []
for line in fhand:
    line = line.rstrip()
    x = line.split()
    word = x[0]
    if word == "Flows":
        for t in x:
            try:
                x_flow.append(int(t))
            except ValueError:
                pass

    elif word == "Throughput":
        for t in x:
            try:
                y_thru.append(float(t))
            except ValueError:
                pass

    elif word == "Average":
        for t in x:
            try:
                y_delay.append(float(t))
            except ValueError:
                pass

    elif word == "Delivery":
        for t in x:
            try:
                y_deli.append(float(t))
            except ValueError:
                pass

    elif word == "Drop":
        for t in x:
            try:
                y_drop.append(float(t))
            except ValueError:
                pass

    #count = count + 1
    #if count == 90: break

print("Varying number of flows:")
print(x_flow)
print(y_thru)
print(y_delay)
print(y_deli)
print(y_drop)


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


plot10 = plt.figure(10)
plt.scatter(x_flow, y_delay)
plt.plot(x_flow, y_delay)
labels = x_flow
plt.xticks(x_flow, labels, rotation = "horizontal")
plt.xlabel("Number of Flows")
plt.ylabel("End-to-end Delay(seconds)")
plt.title("Number of Flows vs End-to-end Delay(seconds)")
plt.grid(True)
fig = plt.gcf()
fig.savefig('graphs/flowVSdelay.png')


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
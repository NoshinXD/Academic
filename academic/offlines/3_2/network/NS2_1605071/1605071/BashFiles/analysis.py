fhand = open('trace.tr', 'r')

received_packets = 0
sent_packets = 0
dropped_packets = 0
total_delay = 0
received_bytes = 0
    
start_time = 1000000
end_time = 0

# constants
header_bytes = 20

sent_time = {}
received_time = {}

count = 0
for line in fhand:
    line = line.rstrip()
    x = line.split()

    event = x[0]
    time_sec = float(x[1])
    node = x[2]
    layer = x[3]
    packet_id = x[5]
    packet_type = x[6]
    packet_bytes = x[7]

    if start_time > time_sec:
        start_time = time_sec

    if layer == "AGT" and packet_type == "exp":
        if event == "s":
            sent_time[packet_id] = time_sec
            sent_packets = sent_packets + 1
        
        elif event == "r":
            delay = time_sec - sent_time[packet_id]
            if delay < 0 : print("ERROR")
            total_delay = total_delay + delay

            sbytes = float(packet_bytes) - header_bytes
            received_bytes = received_bytes + sbytes

            received_packets = received_packets + 1

    if packet_type == "exp" and event == "D":
        dropped_packets = dropped_packets + 1


    count = count + 1
    #if count == 30: break

#print("outside for")

end_time = time_sec
simulation_time = end_time - start_time

print("======================================================================")

print("Sent packets:", sent_packets)
print("Dropped Packets:", dropped_packets)
print("Received Packets:", received_packets)

"""
print("-------------------------------------------------------------")
if simulation_time != 0:
    print("Throughput:", (received_bytes * 8) / simulation_time, "bits/sec")
if received_packets != 0:
    print("Average Delay: ", (total_delay / received_packets), "seconds")
if sent_packets != 0:
    print("Delivery ratio: ", (received_packets / sent_packets))
    print("Drop ratio: ", (dropped_packets / sent_packets))
"""

print("-------------------------------------------------------------")

if simulation_time != 0:
    throughput = round((received_bytes * 8) / simulation_time)
    print("Throughput :", throughput, "bits/sec")
if received_packets != 0:
    avd_delay = total_delay / received_packets
    print("Average Delay : {:.6f}".format(avd_delay), "seconds")
if sent_packets != 0:
    delivery_ratio = received_packets / sent_packets
    print("Delivery ratio :  {:.6f}".format(delivery_ratio))
    drop_ratio = dropped_packets / sent_packets
    print("Drop ratio :  {:.6f}".format(drop_ratio))

print("======================================================================")

f = open("myfile.txt", "a")
f.write("Throughput : " + str(throughput) + " bits/sec\n")
f.write("Average Delay : {:.6f}".format(avd_delay) + " seconds\n")
f.write("Delivery ratio :  {:.6f}".format(delivery_ratio) + "\n")
f.write("Drop ratio :  {:.6f}".format(drop_ratio) + "\n")
f.write("======================================================================\n")
f.close()
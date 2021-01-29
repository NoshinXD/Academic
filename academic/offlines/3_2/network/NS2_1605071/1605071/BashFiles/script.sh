#!/bin/bash
clear

rm -r graphs
mkdir graphs

rm "myfile.txt"
touch "myfile.txt"

area=1
node=7
flow=12
for i in {1..5}
do
   ns wireless.tcl $area $node $flow
   python3 analysis.py
   ((area=area+1))
done
echo "------------------"
area=2
node=6
flow=12
for i in {1..5}
do
   ns wireless.tcl $area $node $flow
   python3 analysis.py
   ((node=node+1))
done
echo "------------------"
area=2
node=7
flow=11
for i in {1..5}
do
   ns wireless.tcl $area $node $flow
   python3 analysis.py
   ((flow=flow+1))
done


#python3 graph_from_file.py
python3 saveFig.py
#saigo no
# simulator
#node_pos: x!=0; y!=0
set ns [new Simulator]

# ======================================================================
# varying area/nodes/flow
puts "##############################"
set fp [open input.txt r]
set areaCount 0

while {[gets $fp line]!=-1} {
    incr areaCount
    if {$areaCount==[lindex $argv 0]} {
            break
    }
}
close $fp

set dimval [string range $line 0 3]
puts "Area size : $dimval"

if {![string is integer -strict $dimval]} {
    error "$dimval isn't a proper integer"
}

set fp1 [open input.txt r]
set nodeCount 0
while {[gets $fp1 line]!=-1} {
    incr nodeCount
    if {$nodeCount==[lindex $argv 1]} {
            break
    }
}
close $fp1

set val(nn) [string range $line 0 3]
puts "number of Nodes : $val(nn)"

if {![string is integer -strict $val(nn)]} {
    error "$val(nn) isn't a proper integer"
}

set fp2 [open input.txt r]
set flowCount 0
while {[gets $fp2 line]!=-1} {
    incr flowCount
    if {$flowCount==[lindex $argv 2]} {
            break
    }
}
close $fp2

set val(nf) [string range $line 0 3]
puts "Number of Flows : $val(nf)"

if {![string is integer -strict $val(nf)]} {
    error "$val(nf) isn't a proper integer"
}

puts "##############################"

set f [open "myfile.txt" a+]
#puts $f "##############################"
puts $f "Area size : $dimval"
puts $f "Nodes : $val(nn)"
puts $f "Flows : $val(nf)"
puts $f "##############################"
close $f

# ======================================================================


# ======================================================================
# Define options

set val(chan)         Channel/WirelessChannel  ;# channel type
set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
set val(ant)          Antenna/OmniAntenna      ;# Antenna type
set val(ll)           LL                       ;# Link layer type
set val(ifq)          Queue/DropTail/PriQueue  ;# Interface queue type
set val(ifqlen)       50                       ;# max packet in ifq
set val(netif)        Phy/WirelessPhy          ;# network interface type
set val(mac)          Mac/802_11               ;# MAC type
set val(rp)           DSDV                     ;# ad-hoc routing protocol 
#set val(nn)           40                       ;# number of mobilenodes
# =======================================================================

# trace file
set trace_file [open trace.tr w]
$ns trace-all $trace_file

#set dimval 500

# nam file
set nam_file [open animation.nam w]
#$ns namtrace-all-wireless $nam_file 500 500
$ns namtrace-all-wireless $nam_file $dimval $dimval

# topology: to keep track of node movements
set topo [new Topography]
#$topo load_flatgrid 500 500 ;# 500m x 500m area

#set dimval 1250
$topo load_flatgrid $dimval $dimval

# general operation director for mobilenodes
create-god $val(nn)


# node configs
# ======================================================================

# $ns node-config -addressingType flat or hierarchical or expanded
#                  -adhocRouting   DSDV or DSR or TORA
#                  -llType	   LL
#                  -macType	   Mac/802_11
#                  -propType	   "Propagation/TwoRayGround"
#                  -ifqType	   "Queue/DropTail/PriQueue"
#                  -ifqLen	   50
#                  -phyType	   "Phy/WirelessPhy"
#                  -antType	   "Antenna/OmniAntenna"
#                  -channelType    "Channel/WirelessChannel"
#                  -topoInstance   $topo
#                  -energyModel    "EnergyModel"
#                  -initialEnergy  (in Joules)
#                  -rxPower        (in W)
#                  -txPower        (in W)
#                  -agentTrace     ON or OFF
#                  -routerTrace    ON or OFF
#                  -macTrace       ON or OFF
#                  -movementTrace  ON or OFF

# ======================================================================

$ns node-config -adhocRouting $val(rp) \
                -llType $val(ll) \
                -macType $val(mac) \
                -ifqType $val(ifq) \
                -ifqLen $val(ifqlen) \
                -antType $val(ant) \
                -propType $val(prop) \
                -phyType $val(netif) \
                -topoInstance $topo \
                -channelType $val(chan) \
                -agentTrace ON \
                -routerTrace ON \
                -macTrace OFF \
                -movementTrace OFF

# create nodes

set dimval [expr $dimval-1]

for {set i 0} {$i < $val(nn) } {incr i} {
    set node($i) [$ns node]
    $node($i) random-motion 1       ;# disable random motion

    #$node($i) set X_ [expr (500 * $i) / $val(nn)]
    #$node($i) set Y_ [expr (500 * $i) / $val(nn)]

    $node($i) set X_ [expr {int(rand()*$dimval) + 1}]
    $node($i) set Y_ [expr {int(rand()*$dimval) + 1}]

    $node($i) set Z_ 0

    $ns initial_node_pos $node($i) 20
    
    set Xdest [expr {int(rand()*$dimval) + 1}]
    set Ydest [expr {int(rand()*$dimval) + 1}]
    set speed [expr {int(rand()*5) + 1}]
    $ns at 1.0 "$node($i) setdest $Xdest $Ydest $speed"
} 





# Traffic
#set val(nf)         20                ;# number of flows

for {set i 0} {$i < $val(nf)} {incr i} {
    #set src $i
    #set dest [expr $i + 10]

    set src [expr {int(rand()*$val(nn))}]
    set dest [expr {int(rand()*$val(nn))}]
    while {$src == $dest} {
        set dest [expr {int(rand()*$val(nn))}]
    }

    # Traffic config
    # create agent
    set udp [new Agent/UDP]
    set null [new Agent/Null]
    # attach to nodes
    $ns attach-agent $node($src) $udp
    $ns attach-agent $node($dest) $null
    # connect agents
    $ns connect $udp $null
    $udp set fid_ $i

    # Traffic generator
    set expo [new Application/Traffic/Exponential]
    # attach to agent
    $expo attach-agent $udp
    $expo set type_ EXPO
    $expo set packet_size_ 1000
    #$expo set rate_ 1mb
    $expo set random_ false

    
    # start traffic generation
    $ns at 1.0 "$expo start"
}



# End Simulation

# Stop nodes
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at 50.0 "$node($i) reset"
}

# call final function
proc finish {} {
    global ns trace_file nam_file
    $ns flush-trace
    close $trace_file
    close $nam_file
}

proc halt_simulation {} {
    global ns
    puts "Simulation ending"
    $ns halt
}

$ns at 50.0001 "finish"
$ns at 50.0002 "halt_simulation"




# Run simulation
puts "Simulation starting"
$ns run


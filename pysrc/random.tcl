# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ''AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
## Maintainer: Tiago Camilo <tandre@dei.uc.pt>
# Version Date: 2006/05/15 
#
#
# ======================================================================
# Define options
# =====================================================================
#set val(chan)           Channel/WirelessChannel    ;#Channel Type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             100                          ;# number of mobilenodes
set val(rp)             AODV                       ;# choose your routing protocol
set val(x)	        60
set val(y)	        100
set val(engmodel)       EnergyModel ;
set val(stop)           300      ;# time of simulation end
set ns                  [new Simulator]
set tracefd             [open traceout.tr w]
set namtrace            [open nameout.nam w]

$ns trace-all $tracefd
$ns use-newtrace
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo       [new Topography]
$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)
set chan_1_ [new $val(chan)]
# configure the nodes
$ns node-config 			-adhocRouting $val(rp) 			-llType $val(ll) 			-macType $val(mac) 			-ifqType $val(ifq) 			-ifqLen $val(ifqlen)			-antType $val(ant) 			-propType $val(prop) 			-phyType $val(netif)  			-topoInstance $topo  			-agentTrace ON 			-routerTrace ON  			-macTrace OFF  			-movementTrace ON  			-energyModel $val(engmodel) 			-initialEnergy 10.000000 			-idlePower 0.000100 			-channel $chan_1_
       set node_(0) [$ns node]
$ns node-config -initialEnergy 10.000000 
       set node_(1) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(2) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(3) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(4) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(5) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(6) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(7) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(8) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(9) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(10) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(11) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(12) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(13) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(14) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(15) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(16) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(17) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(18) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(19) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(20) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(21) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(22) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(23) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(24) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(25) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(26) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(27) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(28) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(29) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(30) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(31) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(32) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(33) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(34) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(35) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(36) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(37) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(38) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(39) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(40) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(41) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(42) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(43) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(44) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(45) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(46) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(47) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(48) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(49) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(50) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(51) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(52) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(53) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(54) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(55) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(56) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(57) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(58) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(59) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(60) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(61) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(62) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(63) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(64) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(65) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(66) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(67) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(68) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(69) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(70) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(71) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(72) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(73) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(74) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(75) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(76) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(77) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(78) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(79) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(80) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(81) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(82) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(83) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(84) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(85) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(86) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(87) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(88) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(89) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(90) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(91) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(92) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(93) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(94) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(95) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(96) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(97) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(98) [$ns node]

$ns node-config -initialEnergy 10.000000 
       set node_(99) [$ns node]

source ./random_topology.tcl

# Define node initial position in nam
$ns initial_node_pos $node_(0) 50
for {set i 1} {$i < $val(nn)} { incr i } {
# defines the node size for nam
$ns initial_node_pos $node_($i) 30
}

# Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
$ns at $val(stop) "$node_($i) reset";
}

# ending nam and the simulation 
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at $val(stop) "puts \"end simulation\" ; $ns halt"

proc print {} {
global ns 
}

proc stop {} {
global ns tracefd namtrace
$ns flush-trace
close $tracefd
close $namtrace
}

$ns run

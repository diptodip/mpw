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
set val(nn)             10                          ;# number of mobilenodes
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
$ns node-config 			-adhocRouting $val(rp) 			-llType $val(ll) 			-macType $val(mac) 			-ifqType $val(ifq) 			-ifqLen $val(ifqlen)			-antType $val(ant) 			-propType $val(prop) 			-phyType $val(netif)  			-topoInstance $topo  			-agentTrace ON 			-routerTrace ON  			-macTrace OFF  			-movementTrace ON  			-energyModel $val(engmodel) 			-initialEnergy 20.000000 			-idlePower 0.000100 			-channel $chan_1_
       set node_(0) [$ns node]
$ns node-config -initialEnergy 20.000000 
       set node_(1) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(2) [$ns node]

$ns node-config -initialEnergy 20.000000 
       set node_(3) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(4) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(5) [$ns node]

$ns node-config -initialEnergy 30.000000 
       set node_(6) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(7) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(8) [$ns node]

$ns node-config -initialEnergy 40.000000 
       set node_(9) [$ns node]

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

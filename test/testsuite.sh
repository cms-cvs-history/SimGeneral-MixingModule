#! /bin/zsh
#############################################################################
#                       Test suite for MixingModule                         #
#############################################################################
# loops over bunchcrossings -5 , 3
# for each bunchcrossing the MixingModule is executed, configured with this bunchcrossing only
# then histograms are created and stored in file histos.root
# they may be looked at by executing testsuite.C interactively in root

integer bcrstart=-5
integer bcrend=3

integer i
for ((i=bcrstart; i<=bcrend; i++))
do
   echo "\n===================> preparing for $i"
# execute Mixing Module
   echo executing MixingModule $i....
   /bin/rm /tmp/testsuite1_$i.cfg  2>&1 >/dev/null
   sed "s/xxx/$i/" data/testsuite1.cfg >/tmp/testsuite1_$i.cfg
   cmsRun --parameter-set /tmp/testsuite1_$i.cfg
# create histos
echo creating histos $i ...
    /bin/rm /tmp/testsuite2_$i.cfg 2>&1 >/dev/null
    sed "s/xxx/$i/" data/testsuite2.cfg | sed "s/bcrs/$bcrstart/" | sed "s/bcre/$bcrend/" >/tmp/testsuite2_$i.cfg
    cmsRun --parameter-set /tmp/testsuite2_$i.cfg
done

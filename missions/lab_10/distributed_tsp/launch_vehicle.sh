#!/bin/bash 
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_BUILD="no"
VNAME="anonymous"
MOOS_PORT="9001"
UDP_LISTEN_PORT="9201"
SHOREIP="localhost"
SHORE_LISTEN="9200"

for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --shore=IP address of shoreside       \n" 
	printf "  --mport=MOOSDB Port #                 \n" 
	printf "  --lport=pShare UDPListen Port #       \n" 
	printf "  --just_make, -j    \n" 
	printf "  --vname=VNAME      \n" 
	printf "  --help, -h         \n" 
	exit 0;
    elif [ "${ARGI:0:8}" = "--vname=" ] ; then
        VNAME="${ARGI#--vname=*}"
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI:0:8}" = "--shore=" ] ; then
	SHOREIP="${ARGI#--shore=*}"
    elif [ "${ARGI:0:7}" = "--mport" ] ; then
	MOOS_PORT="${ARGI#--mport=*}"
    elif [ "${ARGI:0:7}" = "--lport" ] ; then
	UDP_LISTEN_PORT="${ARGI#--lport=*}"
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_BUILD="yes"
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done



#-----------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-----------------------------------------------------------
VNAME1="gilda"  
VNAME2="henry"  
START_POS1="0,0"    
START_POS2="80,0"   
LOITER_POS1="x=0,y=-75"
LOITER_POS2="x=125,y=-50"
#set random sequence region and points number
# REGION_X_MIN=-25
# REGION_X_MAX=200
# REGION_Y_MIN=-175
# REGION_Y_MAX=-25
# RANDOM_POINT=100
# ASSIGN_BY_REGION="true" # assign point by region or not

SHORE_LISTEN="9300"

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1      START_POS=$START_POS1                  \
    VPORT="9001"       SHARE_LISTEN="9301"                    \
    VTYPE="kayak"      SHORE_LISTEN=$SHORE_LISTEN           

nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2      START_POS=$START_POS2                  \
    VPORT="9002"       SHARE_LISTEN="9302"                    \
    VTYPE="kayak"      SHORE_LISTEN=$SHORE_LISTEN            

nsplug meta_vehicle.bhv targ_$VNAME1.bhv -f VNAME=$VNAME1     \
    START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       

nsplug meta_vehicle.bhv targ_$VNAME2.bhv -f VNAME=$VNAME2     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2          


#-----------------------------------------------------------
#  Part 3: Launch the processes
#-----------------------------------------------------------
printf "Launching $VNAME1 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME1.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME2.moos >& /dev/null &
printf "Done \n"

uMAC targ_$VNAME.moos

kill %1 
printf "Done.   \n"



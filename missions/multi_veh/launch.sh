#!/bin/bash 
#-------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-------------------------------------------------------
TIME_WARP=1
JUST_MAKE="no"
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
	printf "%s [SWITCHES] [time_warp]   \n" $0
	printf "  --just_make, -j    \n" 
	printf "  --help, -h         \n" 
	exit 0;
    elif [ "${ARGI//[^0-9]/}" = "$ARGI" -a "$TIME_WARP" = 1 ]; then 
        TIME_WARP=$ARGI
    elif [ "${ARGI}" = "--just_build" -o "${ARGI}" = "-j" ] ; then
	JUST_MAKE="yes"
    else 
	printf "Bad Argument: %s \n" $ARGI
	exit 0
    fi
done

#-------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-------------------------------------------------------
VNAME1="veh_1"           # The first vehicle Community
VNAME2="veh_2"           # The second vehicle Community
VNAME3="veh_3"
VNAME4="veh_4"
VNAME5="veh_5"
VNAME6="veh_6"
START_POS1="0,0"         
START_POS2="0,15"        
LOITER_POS1="0,-75"
LOITER_POS2="125,-75"
SHORE_LISTEN="9300"
BOAT_LEN_DEF="8"

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1          SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  BOAT=ship BOAT_LEN=15

nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2          SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=ship BOAT_LEN=18 

nsplug meta_vehicle.moos targ_$VNAME3.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME3          SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=ship BOAT_LEN=20
nsplug meta_vehicle.moos targ_$VNAME4.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME4          SHARE_LISTEN="9304"              \
    VPORT="9004"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=ship BOAT_LEN=22
nsplug meta_vehicle.moos targ_$VNAME5.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME5          SHARE_LISTEN="9305"              \
    VPORT="9005"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=kayak BOAT_LEN=8 
nsplug meta_vehicle.moos targ_$VNAME6.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME6          SHARE_LISTEN="9306"              \
    VPORT="9006"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=kayak BOAT_LEN=8 

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
    SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN                 \
    SPORT="9000"       

nsplug meta_vehicle.bhv targ_$VNAME1.bhv -f VNAME=$VNAME1     \
    START_POS=$START_POS1 LOITER_POS=$LOITER_POS1       

nsplug meta_vehicle.bhv targ_$VNAME2.bhv -f VNAME=$VNAME2     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2       

nsplug meta_vehicle.bhv targ_$VNAME3.bhv -f VNAME=$VNAME3     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2       
nsplug meta_vehicle.bhv targ_$VNAME4.bhv -f VNAME=$VNAME4     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2       
nsplug meta_vehicle.bhv targ_$VNAME5.bhv -f VNAME=$VNAME5     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2       
nsplug meta_vehicle.bhv targ_$VNAME6.bhv -f VNAME=$VNAME6     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2       
if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Launching $VNAME1 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME1.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME2.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME3.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME4.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME5.moos >& /dev/null &
printf "Launching $VNAME2 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME6.moos >& /dev/null &
printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3
printf "Done killing processes.   \n"

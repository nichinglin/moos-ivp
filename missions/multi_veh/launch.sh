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
VNAME7="veh_7"
VNAME8="veh_8"
VNAME9="veh_9"
START_POS1="2509,-1413"         
START_POS2="795,-171"          
START_POS3="3768,-1154"         
START_POS4="3105,-766"         
START_POS5="3392,-153"   
START_POS6="1292,-233"  
START_POS7="2891,-2080"
START_POS8="241,10"
START_POS9="0,0"
#LOITER_POS1="0,-75:10,10"
LOITER_POS1="2509,-1413:2180,-1620"
LOITER_POS2="795,-171:1856,-42:3768,-1154:4051,-2101:3768,-1154"
LOITER_POS3="3768,-1154:4051,-2101:3768,-1154:1856,-42:795,-171"
LOITER_POS4="3105,-766:3392,-153"
LOITER_POS5="3105,-766:3392,-153"
LOITER_POS6="1292,-233:1731,-450:2274,-957:2891,-2080:3194,-2618"
LOITER_POS7="1292,-233:1731,-450:2274,-957:2891,-2080:3194,-2618"
LOITER_POS8="241,10:1292,-233"
LOITER_POS9="0,0:241,10"
SHORE_LISTEN="9300"
BOAT_LEN_DEF="8"

nsplug meta_vehicle.moos targ_$VNAME1.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME1          SHARE_LISTEN="9301"              \
    VPORT="9001"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS1  BOAT=kayak BOAT_LEN=52 
nsplug meta_vehicle.bhv targ_$VNAME1.bhv -f VNAME=$VNAME1     \
    START_POS=$START_POS1 LOITER_POS=$LOITER_POS1   

nsplug meta_vehicle.moos targ_$VNAME2.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME2          SHARE_LISTEN="9302"              \
    VPORT="9002"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS2  BOAT=ship BOAT_LEN=77 
nsplug meta_vehicle.bhv targ_$VNAME2.bhv -f VNAME=$VNAME2     \
    START_POS=$START_POS2 LOITER_POS=$LOITER_POS2  

nsplug meta_vehicle.moos targ_$VNAME3.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME3          SHARE_LISTEN="9303"              \
    VPORT="9003"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS3  BOAT=ship BOAT_LEN=66 
nsplug meta_vehicle.bhv targ_$VNAME3.bhv -f VNAME=$VNAME3     \
    START_POS=$START_POS3 LOITER_POS=$LOITER_POS3  

nsplug meta_vehicle.moos targ_$VNAME4.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME4          SHARE_LISTEN="9304"              \
    VPORT="9004"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS4  BOAT=ship BOAT_LEN=50 
nsplug meta_vehicle.bhv targ_$VNAME4.bhv -f VNAME=$VNAME4     \
    START_POS=$START_POS4 LOITER_POS=$LOITER_POS4  

nsplug meta_vehicle.moos targ_$VNAME5.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME5          SHARE_LISTEN="9305"              \
    VPORT="9005"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS5  BOAT=ship BOAT_LEN=63 
nsplug meta_vehicle.bhv targ_$VNAME5.bhv -f VNAME=$VNAME5     \
    START_POS=$START_POS5 LOITER_POS=$LOITER_POS5   

nsplug meta_vehicle.moos targ_$VNAME6.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME6          SHARE_LISTEN="9306"              \
    VPORT="9006"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS6  BOAT=kayak BOAT_LEN=68 
nsplug meta_vehicle.bhv targ_$VNAME6.bhv -f VNAME=$VNAME6     \
    START_POS=$START_POS6 LOITER_POS=$LOITER_POS6   

nsplug meta_vehicle.moos targ_$VNAME7.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME7          SHARE_LISTEN="9307"              \
    VPORT="9007"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS7  BOAT=kayak BOAT_LEN=52 
nsplug meta_vehicle.bhv targ_$VNAME7.bhv -f VNAME=$VNAME7     \
    START_POS=$START_POS7 LOITER_POS=$LOITER_POS7   

nsplug meta_vehicle.moos targ_$VNAME8.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME8          SHARE_LISTEN="9308"              \
    VPORT="9008"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS8  BOAT=kayak BOAT_LEN=52 
nsplug meta_vehicle.bhv targ_$VNAME8.bhv -f VNAME=$VNAME8     \
    START_POS=$START_POS8 LOITER_POS=$LOITER_POS8   

nsplug meta_vehicle.moos targ_$VNAME9.moos -f WARP=$TIME_WARP \
    VNAME=$VNAME9          SHARE_LISTEN="9309"              \
    VPORT="9009"           SHORE_LISTEN=$SHORE_LISTEN       \
    START_POS=$START_POS9  BOAT=kayak BOAT_LEN=52 
nsplug meta_vehicle.bhv targ_$VNAME9.bhv -f VNAME=$VNAME9     \
    START_POS=$START_POS9 LOITER_POS=$LOITER_POS9   

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
    SNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN                 \
    SPORT="9000"       
   
    
                     
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
printf "Launching $VNAME3 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME3.moos >& /dev/null &
printf "Launching $VNAME4 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME4.moos >& /dev/null &
printf "Launching $VNAME5 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME5.moos >& /dev/null &
printf "Launching $VNAME6 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME6.moos >& /dev/null &
printf "Launching $VNAME7 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME7.moos >& /dev/null &
printf "Launching $VNAME8 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME8.moos >& /dev/null &
printf "Launching $VNAME9 MOOS Community (WARP=%s) \n" $TIME_WARP
pAntler targ_$VNAME9.moos >& /dev/null &
printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1 %2 %3
printf "Done killing processes.   \n"

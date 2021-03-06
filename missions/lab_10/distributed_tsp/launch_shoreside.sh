#!/bin/bash 
#-----------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#-----------------------------------------------------------
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

#-----------------------------------------------------------
#  Part 2: Create the .moos and .bhv files. 
#-----------------------------------------------------------
VNAME1="gilda"  
VNAME2="henry"  
# START_POS1="0,0"    
# START_POS2="80,0"   
# LOITER_POS1="x=0,y=-75"
# LOITER_POS2="x=125,y=-50"
#set random sequence region and points number
REGION_X_MIN=-25
REGION_X_MAX=200
REGION_Y_MIN=-175
REGION_Y_MAX=-25
RANDOM_POINT=100
ASSIGN_BY_REGION="true" # assign point by region or not

SHORE_LISTEN="9300"        

nsplug meta_shoreside.moos targ_shoreside.moos -f WARP=$TIME_WARP \
   VNAME="shoreside"  SHARE_LISTEN=$SHORE_LISTEN  VPORT="9000"  \
   ASSIGN_BY_REGION=$ASSIGN_BY_REGION                           \
   VNAME1=$VNAME1    VNAME2=$VNAME2                           \
   REGION_X_MIN=$REGION_X_MIN    REGION_X_MAX=$REGION_X_MAX   \
   REGION_Y_MIN=$REGION_Y_MIN    REGION_Y_MAX=$REGION_Y_MAX   \
   RANDOM_POINT=$RANDOM_POINT
        
if [ ${JUST_MAKE} = "yes" ] ; then
    exit 0
fi

#-------------------------------------------------------
#  Part 3: Launch the processes
#-------------------------------------------------------
printf "Launching $SNAME MOOS Community (WARP=%s) \n"  $TIME_WARP
pAntler targ_shoreside.moos >& /dev/null &
printf "Done \n"

uMAC targ_shoreside.moos

printf "Killing all processes ... \n"
kill %1
sleep 1
mykill
printf "Done killing processes.   \n"



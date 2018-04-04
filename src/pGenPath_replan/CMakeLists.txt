#--------------------------------------------------------
# The CMakeLists.txt for:                       pGenPath_replan
# Author(s):                              Monica Lin
#--------------------------------------------------------

SET(SRC
  GenPath_replan.cpp
  GenPath_replan_Info.cpp
  main.cpp
  XYSegList.cpp
)

ADD_EXECUTABLE(pGenPath_replan ${SRC})

TARGET_LINK_LIBRARIES(pGenPath_replan
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


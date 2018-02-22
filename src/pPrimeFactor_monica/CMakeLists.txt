#--------------------------------------------------------
# The CMakeLists.txt for:                       pPrimeFactor_monica
# Author(s):                              Monica Lin
#--------------------------------------------------------

SET(SRC
  PrimeFactor_monica.cpp
  PrimeFactor_monica_Info.cpp
  main.cpp
  PrimeEntry.cpp
)

ADD_EXECUTABLE(pPrimeFactor_monica ${SRC})

TARGET_LINK_LIBRARIES(pPrimeFactor_monica
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)


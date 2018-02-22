/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor_monica.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef PrimeFactor_monica_HEADER
#define PrimeFactor_monica_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "PrimeEntry.h"

class PrimeFactor_monica : public CMOOSApp
{
 public:
   PrimeFactor_monica();
   ~PrimeFactor_monica();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();

  unsigned int  m_received_index;
  unsigned int  m_calculated_index;

  std::vector<PrimeEntry> node;

 private: // Configuration variables

 private: // State variables
};

#endif 

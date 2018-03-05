/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: Test.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef Test_HEADER
#define Test_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class Test : public CMOOSApp
{
 public:
   Test();
   ~Test();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();

   double m_sub_double;     // sub double msg
   double m_param_double;    //paremete double
   std::string m_sub_string; // sub string msg
   std::string m_param_str;  //paremete string
};

#endif 

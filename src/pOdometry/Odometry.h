/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: Odometry.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef Odometry_HEADER
#define Odometry_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h" 
#include "NodeRecord.h"

class Odometry : public AppCastingMOOSApp        // (this will show info on screen) Instead of CMOOSApp
{
 public:
   Odometry();
   ~Odometry();

   bool buildReport();                              // Add this line to show info on screen

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();


 protected:
   void RegisterVariables();

 private: // Configuration variables
   bool   m_first_reading;
   double m_current_x;
   double m_current_y;
   double m_previous_x;
   double m_previous_y;

   double m_odometry_dis;
 private: // State variables
};

#endif 

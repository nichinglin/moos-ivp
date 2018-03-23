/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: GenPath.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef GenPath_HEADER
#define GenPath_HEADER

#include <deque>
#include "XYSegList.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class GenPath : public AppCastingMOOSApp
{
 public:
   GenPath();
   ~GenPath();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

   std::deque<std::string> m_visit_point_list;
   XYSegList m_seglist;
   bool m_genpath_run;

   //app casting value
   int m_radius;
   int m_points_received;
   int m_ivalid_point_recived;
   std::string m_first_received;
   std::string m_last_received;
   std::string m_navxy_received;
   int m_visit_points;
   int m_unvisit_points;
   
 private: // Configuration variables

 private: // State variables
};

#endif 

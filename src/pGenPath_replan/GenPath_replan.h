/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: GenPath_replan.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef GenPath_replan_HEADER
#define GenPath_replan_HEADER

#include <deque>
#include "XYSegList.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class GenPath_replan : public AppCastingMOOSApp
{
 public:
   GenPath_replan();
   ~GenPath_replan();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

   std::deque<std::string> m_visit_point_list; // visit point list
   XYSegList m_seglist; // list for navi points
   XYPoint m_nav_point; // now point
   int m_wpt_index;  // next point index
   //double m_visit_radius;
   bool m_genpath_run;
   bool m_arrive_end;

   //app casting value
   double m_radius;
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

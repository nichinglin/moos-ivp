/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: Odometry.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "Odometry.h"
#include <math.h>

using namespace std;

//---------------------------------------------------------
// Constructor

Odometry::Odometry()
{
   //init
   m_first_reading = true;
   m_current_x = 0;
   m_current_y = 0;
   m_previous_x = 0;
   m_previous_y = 0;

   odometry_dis = 0;
}

//---------------------------------------------------------
// Destructor

Odometry::~Odometry()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Odometry::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key   = msg.m_sKey;
    double ddata = msg.m_dfVal;

    // get msg NAV_X and NAV_Y (Subscriber)
    if(key == "NAV_X") {
      m_previous_x = m_current_x;
      m_current_x = ddata;
    }
    else if(key == "NAV_Y") {
      m_previous_y = m_current_y;
      m_current_y = ddata;
    }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Odometry::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();

   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Odometry::Iterate()
{
  double dx = m_current_x - m_previous_x;
  double dy = m_current_y - m_previous_y;
  if(m_first_reading == true) {
    m_first_reading = false;
    odometry_dis = 0.0;
  }
  odometry_dis += sqrt(dx*dx + dy*dy);
  Notify("ODOMETRY_DIST", odometry_dis); //publish ODEMETRY_DIST msg
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Odometry::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);
      
      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void Odometry::RegisterVariables()
{
  // Subscribe msg register
  // Register("FOOBAR", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
}


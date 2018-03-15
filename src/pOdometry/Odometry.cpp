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
   m_current_x = 0.0;
   m_current_y = 0.0;
   m_previous_x = 0.0;
   m_previous_y = 0.0;

   m_odometry_dis = 0.0;
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
  AppCastingMOOSApp::OnNewMail(NewMail);        // Add this line to show info on screen
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key   = msg.m_sKey;
    double ddata = msg.m_dfVal;

    // ----------Get Subscriber msg --------------
    if(key == "NAV_X") {
      //m_previous_x = m_current_x;
      m_current_x = ddata;
    }
    else if(key == "NAV_Y") {
      //m_previous_y = m_current_y;
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

  //-------------- update fuction ----------------
bool Odometry::Iterate()
{
  AppCastingMOOSApp::Iterate();                  // Add this line to show info on screen
  if(m_first_reading == true) {
    m_first_reading = false;
    m_odometry_dis = 0.0;
  }
  if(m_first_reading == false) {
    double dx = m_current_x - m_previous_x;
    double dy = m_current_y - m_previous_y;
    m_odometry_dis += sqrt(dx*dx + dy*dy);
    m_previous_x = m_current_x;
    m_previous_y = m_current_y;
  }
   //------------ publish ODEMETRY_DIST msg ---------------
  Notify("ODOMETRY_DIST", m_odometry_dis);
  AppCastingMOOSApp::PostReport();               // Add this line to show info on screen
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Odometry::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();               // Add this line to show info on screen
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      //string param = MOOSChomp(original_line, "=");
      string value = stripBlankEnds(*p);
      

      //----------- Get parm ------------
      //if(MOOSStrCmp(param, "FOO")) {
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
  AppCastingMOOSApp::RegisterVariables();      // Add this line to show info on screen
  // ------------ Subscribe ------------
  // Register("FOOBAR", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
}

//---------------------------------------------------------
// Procedure: buildReport

bool Odometry::buildReport()
{
  m_msgs << "NAV_X: " << m_current_x << endl;
  m_msgs << "NAV_Y: " << m_current_y << endl;
  m_msgs << "ODOMETRY_DIST: " << m_odometry_dis <<endl;

  std::ostringstream iss;
  iss << m_odometry_dis;
  reportEvent("ODOMETRY_DIST" + iss.str());
  return(true);
}

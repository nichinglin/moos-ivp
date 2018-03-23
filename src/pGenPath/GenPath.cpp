/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: GenPath.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "GenPath.h"

using namespace std;

#define DEBUG 1
//---------------------------------------------------------
// Constructor

GenPath::GenPath()
{
  m_visit_point_list.clear();
  m_genpath_run = true;

  m_radius = 3;
  m_points_received = 0;
  m_ivalid_point_recived = 0;
  m_first_received = "false";
  m_last_received = "false";
  m_navxy_received = "false";
  m_visit_points = 0;
  m_unvisit_points = 0;
}

//---------------------------------------------------------
// Destructor

GenPath::~GenPath()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GenPath::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);
  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    //double dval  = msg.GetDouble();

    if(key == "FOO") 
      cout << "great!";
    else if (key == "VISIT_POINT") {
      string sval  = msg.GetString(); 
      m_visit_point_list.push_back(sval);
      m_points_received++;
    }
    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }
	
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath::Iterate()
{
  AppCastingMOOSApp::Iterate();
  Notify("GENPATH_RUN", m_genpath_run);
  // get all msg from VISIT_POINT and spilt into m_seglist
  while(!m_visit_point_list.empty()){
    string visit_point = m_visit_point_list.front();          // get front value
    vector<string> contenor = parseString(visit_point, ',');  // split by ,
    stringstream view_point_msg;
    double x, y;
    int id;
    int param_cnt =0;
    // spilt point msg into x, y, id, firstpoint, or lastpoint
    for(int i=0; i<contenor.size(); i++) {
      string param = biteStringX(contenor[i], '=');
      string value = contenor[i];
      if(tolower(param) == "x") {
        if(DEBUG) cout << "x: " << x << endl;
        setDoubleOnString(x, value);
        param_cnt++;
      }
      else if(tolower(param) == "y") {
        if(DEBUG) cout << "y: " << y << endl;
        setDoubleOnString(y, value);
        param_cnt++;
      }
      else if(tolower(param) == "id") {
        id = atoi(value.c_str());
        param_cnt++;
        break;
      }
      else if (tolower(param) == "lastpoint") {
        string update_str = m_seglist.get_spec();
        Notify("UPDATES_GENPATH", update_str);
        m_last_received = "true";
        break;
      }
      else if (tolower(param) == "firstpoint") {
        m_first_received = "true";
        break;
      }
      else {
        m_ivalid_point_recived++;
        break;
      }
    }
    if(param_cnt == 3) {
      m_navxy_received = "true";
      m_seglist.add_vertex(x, y);
    }
    m_visit_point_list.pop_front();
    // if(m_visit_points == m_points_received-2) {
    //   string update_str = m_seglist.get_spec();
    //   Notify("UPDATES_GENPATH", update_str);
    // }
  }

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = toupper(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "FOO") {
      handled = true;
    }
    else if(param == "BAR") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GenPath::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("VISIT_POINT", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool GenPath::buildReport() 
{
  m_visit_points = m_seglist.get_points();
  m_unvisit_points = m_points_received - m_visit_points -2; //-2 --> first and last point
  //m_msgs << "Visit Radius: " << m_radius         << "                 \n";
  m_msgs << "Total Points Received: " << m_points_received << "       \n";
  m_msgs << "Invalid Points Received: " << m_ivalid_point_recived << "\n";
  m_msgs << "First Point Received: " << m_first_received << "         \n";
  m_msgs << "Last Point Received: " << m_last_received << "           \n";
  m_msgs << "NAV_X/Y Received: " << m_navxy_received << "             \n";
  m_msgs << "                                                         \n";
  m_msgs << "Tour Status" << "                                        \n";
  m_msgs << " ------------------------" << "                          \n";
  m_msgs << "Points Visited: " << m_visit_points << "                 \n";
  m_msgs << "Points Unvisited: " << m_unvisit_points << "             \n";

  return(true);
}





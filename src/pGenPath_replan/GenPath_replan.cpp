/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: GenPath_replan.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "GenPath_replan.h"

using namespace std;

#define DEBUG true

//---------------------------------------------------------
// Constructor

GenPath_replan::GenPath_replan()
{
  m_visit_point_list.clear();
  m_genpath_run = true;
  //m_visit_radius = 5.0;
  m_wpt_index = 0;

  m_radius = 5.0;
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

GenPath_replan::~GenPath_replan()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GenPath_replan::OnNewMail(MOOSMSG_LIST &NewMail)
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
    else if (key == "NAV_X") {
      double dval  = msg.GetDouble();
      m_nav_point.x = dval;
      //if(DEBUG) cout << m_nav_point.x <<endl;
    }
    else if (key == "NAV_Y") {
      double dval  = msg.GetDouble();
      m_nav_point.y = dval;
      //if(DEBUG) cout << m_nav_point.y <<endl;
    }
    else if (key == "WPT_INDEX") {
      double dval  = msg.GetDouble();
      m_wpt_index = dval;
    }
    else if (key == "ARRIVE_END") {
      string sval  = msg.GetString();
      m_arrive_end = false;
      if(sval == "true")
        m_arrive_end = true;
    }

    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath_replan::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath_replan::Iterate()
{
  AppCastingMOOSApp::Iterate();
  Notify("GENPATH_RUN", m_genpath_run);

  // get all msg from VISIT_POINT and spilt into m_seglist
  while(!m_visit_point_list.empty()){
    string visit_point = m_visit_point_list.front();          // get front value
    vector<string> contenor = parseString(visit_point, ',');  // split by ,
    double x, y;
    int id;
    int param_cnt =0;
    // spilt point msg into x, y, id, firstpoint, or lastpoint
    for(int i=0; i<contenor.size(); i++) {
      string param = biteStringX(contenor[i], '=');
      string value = contenor[i];
      param = tolower(param);
      if(param == "x") {
        //if(DEBUG) cout << "x: " << x << endl;
        setDoubleOnString(x, value);
        param_cnt++;
      }
      else if(param == "y") {
        //if(DEBUG) cout << "y: " << y << endl;
        setDoubleOnString(y, value);
        param_cnt++;
      }
      else if(param == "id") {
        id = atoi(value.c_str());
        param_cnt++;
        break;
      }
      else if (param == "lastpoint") {
        string update_str = m_seglist.get_spec();
        Notify("UPDATES_GENPATH", update_str);
        m_last_received = "true";
        break;
      }
      else if (param == "firstpoint") {
        m_first_received = "true";
        break;
      }
      else {
        m_ivalid_point_recived++;
        break;
      }
    }
    // get point assign x, y, and id
    if(param_cnt == 3) {
      m_navxy_received = "true";
      m_seglist.add_vertex(x, y);
    }
    m_visit_point_list.pop_front();
  }

    if(!m_seglist.empty()) {
      m_seglist.rm_visit_vertex(m_wpt_index, m_nav_point.x, m_nav_point.y);
      // string update_str = m_seglist.get_spec();
      // Notify("UPDATES_GENPATH", update_str);
    }
    //if(m_wpt_index == (m_visit_points-1)) {
    if(m_arrive_end) {
      //cout << "wpt-index == points received" << endl;
      string update_str = m_seglist.get_spec();
      if(update_str != "points = ") {
        Notify("UPDATES_GENPATH", update_str);
        m_arrive_end = false;
        Notify("ARRIVE_END", "false");
      }
      else {
        Notify("UPDATES_GENPATH", "");
        Notify("LOITER", "false");
        Notify("RETURN", "true");
        //otify("RETURN", "true");
      }
    }

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath_replan::OnStartUp()
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
    else if(param == "VISIT_RADIUS") {
      handled = setDoubleOnString(m_radius, value);
      m_seglist.set_visit_radius(m_radius);
    }
    else if(param == "VISIT_RADIUS") {
      handled = setDoubleOnString(m_radius, value);
      m_seglist.set_visit_radius(m_radius);
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GenPath_replan::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("VISIT_POINT", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("WPT_INDEX", 0);
  Register("ARRIVE_END", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool GenPath_replan::buildReport() 
{
  m_visit_points = m_seglist.get_points();
  m_unvisit_points = m_points_received - m_visit_points -2; //-2 --> first and last point
  m_msgs << "Visit Radius: " << m_radius         << "                 \n";
  m_msgs << "NAV_X,NAV_Y: " << m_nav_point.x << "," << m_nav_point.y << "       \n";
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
  //m_msgs << "WPT Repo: " << m_wpt_repo << "             \n";


  return(true);
}





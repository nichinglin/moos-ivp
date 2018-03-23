/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: PointAssign.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PointAssign.h"
#include "XYPointView.h"

#define DEBUG 1

using namespace std;

//---------------------------------------------------------
// Constructor

PointAssign::PointAssign()
{
  m_vname[0] = "henry";
  m_vname[1] = "gilda";
  m_assign_by_region=false;
  m_visit_point_list.clear();
  m_state_run = true;
}

//---------------------------------------------------------
// Destructor

PointAssign::~PointAssign()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PointAssign::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);
  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    //double dval  = msg.GetDouble();
    //string sval  = msg.GetString(); 

    if(key == "FOO") 
      cout << "great!";
    else if (key == "VISIT_POINT") {
      string sval  = msg.GetString(); 
      //if(DEBUG) cout << "point:" << sval << endl;
      m_visit_point_list.push_back(sval);
    }
    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);

   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PointAssign::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PointAssign::Iterate()
{
  AppCastingMOOSApp::Iterate();
  Notify("POINTASSIGN_RUN", m_state_run);
  // get all point one by one from front
  while(!m_visit_point_list.empty()){
    string visit_point = m_visit_point_list.front();
    vector<string> contenor = parseString(visit_point, ',');
    stringstream view_point_msg;
    double x, y;
    int id;
    string veh, color;
    int param_cnt =0;
    // spilt point msg into x, y, id, firstpoint, or lastpoint
    for(int i=0; i<contenor.size(); i++) {
      string param = biteStringX(contenor[i], '=');
      string value = contenor[i];
      if(tolower(param) == "x") {
        setDoubleOnString(x, value);
        param_cnt++;
      }
      else if(tolower(param) == "y") {
        setDoubleOnString(y, value);
        param_cnt++;
      }
      else if(tolower(param) == "id") {
        id = atoi(value.c_str());
        param_cnt++;
      }
    }
    // send view point to pMarineViewer and split point into two vehicles msg
    if(param_cnt == 3) {
      // set which vehicle to publish
      if(m_assign_by_region) {
        if(x < 87.5)
          veh = toupper(m_vname[0]);
        else
          veh = toupper(m_vname[1]);
      }
      else {
        veh = toupper(m_vname[id%2]);
      }
      // set point color
      if(veh == toupper(m_vname[0]))
        color = "pink";
      else
        color = "red";

      postViewPoint(x, y, id, color);

      stringstream ss;
      ss << "VISIT_POINT_" << toupper(veh);
      Notify(ss.str(),visit_point);
    }
    else {
      for(int i=0; i<2; i++) {
        stringstream ss;
        ss << "VISIT_POINT_" << toupper(m_vname[i]);
        Notify(ss.str(),visit_point);
      }
    }
    m_visit_point_list.pop_front();
  }
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

void PointAssign::postViewPoint(double x, double y, int id, string color)
{
  XYPointView point(x,y);
  //point.set_label(label);
  point.set_color(color);
  point.set_id(id);

  string spec = point.get_spec();
  Notify("VIEW_POINT", spec);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PointAssign::OnStartUp()
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
    else if (param == "ASSIGN_BY_REGION") {
      //if(DEBUG) cout << "assign_by_region:" << value << endl;
      if(value == "true")
        m_assign_by_region = true;
      else
        m_assign_by_region = false;
      handled = true;
    }
    else if (param == "VNAME1") {
      m_vname[0] = value;
      handled = true;
    }
    else if (param == "VNAME2") {
      m_vname[1] = value;
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

void PointAssign::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("VISIT_POINT", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool PointAssign::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "PointAssign                                  \n";
  m_msgs << "============================================ \n";

  m_msgs << "m_assign_by_region: " << m_assign_by_region << "\n";
  m_msgs << "m_vname1: " << m_vname[0] << "\n";
  m_msgs << "m_vname2: " << m_vname[1] << "\n";
  m_msgs << "============================================ \n";

  return(true);
}





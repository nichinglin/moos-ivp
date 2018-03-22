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

  while(!m_visit_point_list.empty()){
    string visit_point = m_visit_point_list.front();
    vector<string> contenor = parseString(visit_point, ',');
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
      }
      else if (tolower(param) == "lastpoint") {
        string update_str = m_seglist.get_spec();
        Notify("UPDATES_GENPATH", update_str);
      }
    }
    if(param_cnt == 3) {
      m_seglist.add_vertex(x, y);
      // string update_str = m_seglist.get_spec();
      // Notify("UPDATES_GENPATH", update_str);
    }
    m_visit_point_list.pop_front();
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
  m_msgs << "============================================ \n";
  m_msgs << "File:                                        \n";
  m_msgs << "============================================ \n";

  //m_msgs << "Z_UPDATES_GENPATH: " << m_seglist.get_spec();

  // ACTable actab(4);
  // actab << "Alpha | Bravo | Charlie | Delta";
  // actab.addHeaderLines();
  // actab << "one" << "two" << "three" << "four";
  // m_msgs << actab.getFormattedString();s

  return(true);
}





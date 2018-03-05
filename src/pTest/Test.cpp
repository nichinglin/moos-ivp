/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: Test.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "Test.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Test::Test()
{
  m_sub_double = 0;
  m_sub_string = "hello word";
  m_param_str = "default";
  m_param_double = 0;

}

//---------------------------------------------------------
// Destructor

Test::~Test()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Test::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key = msg.GetKey();      // key = msg name
    string sval = msg.GetString();  // sval = msg.data
    double dval = msg.GetDouble();  // dval = msg.data

    if(key == "INPUT_MSG") {  // msg name INPUT_MSG
      m_sub_double = dval;
    } else if (key == "CHATTER") {  // msg name CHATTER
      m_sub_string = sval;
    }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Test::OnConnectToServer()
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

bool Test::Iterate()
{
  double out = m_sub_double*m_sub_double;  // do algorithm
  cout << "param_str: " << m_param_str << " m_param_double: " << m_param_double << endl;
  cout << "input: " << m_sub_double << "   output: " << out << endl;
  stringstream ss;
  ss << "parameters: " << m_param_double << "," << m_param_str \
     << " subscriber" << m_sub_double << "," << m_sub_string << endl;
  Notify("POW_OUT", out); // pub double msg name POW_OUT
  Notify("LISTENER", m_sub_string); // pub string msg name STRING_OUT
  Notify("REPO", ss.str());  // pub string msg name REPO
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Test::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);
      double dval = atof(value.c_str());
      
      if(param == "PARAM_STR") {
        m_param_str = value;
      }
      else if(param == "PARAM_DOU") {
        m_param_double = dval;
      }
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void Test::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("INPUT_MSG", 0);
  Register("CHATTER", 0);
}


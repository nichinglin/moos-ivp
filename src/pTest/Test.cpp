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
  m_data = 0;
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

    if(key == "IN_MSG") {
      m_data = dval;
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
  double out = m_data*m_data;
  cout << "input: " << m_data << "   output: " << out << endl;
  Notify("OUT_DATA", out);
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

void Test::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("IN_MSG", 0);
}


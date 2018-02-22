/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor_monica.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PrimeFactor_monica.h"

#define DEBUG 1
#define ITER 10000000

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactor_monica::PrimeFactor_monica()
{
  m_received_index = 0;
  m_calculated_index = 0;
}

//---------------------------------------------------------
// Destructor

PrimeFactor_monica::~PrimeFactor_monica()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactor_monica::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    
    string key = msg.GetKey();
    string sval = msg.GetString();

    if(key == "NUM_VALUE") {
      PrimeEntry *tmp = new PrimeEntry();

      uint64_t n;
      std::stringstream ss(sval);
      ss >> n;
      tmp->setOriginalVal(n);
      tmp->setReceivedIndex(m_received_index++);
      node.push_back(*tmp);
    }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactor_monica::OnConnectToServer()
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

bool PrimeFactor_monica::Iterate()
{
  if(node.size()>0) {
    PrimeEntry tmp = node.back();

    double tic,toc;
    tic = MOOSTime();

    node.back().factor(ITER);

    toc = MOOSTime();
    node.back().setTime(toc-tic);
    // node tail finish calculating prime factors
    if(node.back().done()) {
      node.back().setCalculatedIndex(m_calculated_index++);
      string s = node.back().getReport();
      if(DEBUG)
        cout << "get from Iterate:" << s << endl;
      Notify("PRIME_RESULT", s); //publish msg
      node.pop_back();
    }
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactor_monica::OnStartUp()
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

void PrimeFactor_monica::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("NUM_VALUE", 0);
}


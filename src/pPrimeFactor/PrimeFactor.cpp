/************************************************************/
/*    NAME: Monica Lin                                              */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <iostream>
#include <stdlib.h>     /* atoi */
#include "MBUtils.h"
#include "PrimeFactor.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactor::PrimeFactor()
{
  m_mun_valse = "0";
  m_out_valse = "";
  m_out_result = "";
}

//---------------------------------------------------------
// Destructor

PrimeFactor::~PrimeFactor()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactor::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key   = msg.GetKey();
    //double ddata = msg.m_dfVal;
    string sval  = msg.GetString();


    //string key   = msg.m_sKey;
    //string sdata = msg.m_sVal;

    // get msg NAV_X and NAV_Y (Subscriber)
    if(key == "NUM_VALUE") {
      m_mun_valse = sval;
    }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactor::OnConnectToServer()
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

bool PrimeFactor::Iterate()
{
  // string to uint64_t
  uint64_t value;
  std::istringstream iss(m_mun_valse);
  iss >> value;
  //prime
  for(uint64_t x=2; x<=value; x++) {
    while(value%x == 0) {
      m_out_valse += x + "*";
    }
  }
  m_out_result = "orig=" + m_mun_valse + ",received=" + "?" + ",calculated=" + "?" + ",solve_time=" + "?" + ",primes=" + m_out_valse + ",username=monica";

  Notify("PRIME_RESULT", m_out_valse); //publish msg
  Notify("PRIME_RESULT__", 0.0); //publish msg
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactor::OnStartUp()
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

void PrimeFactor::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("NUM_VALUE", 0);
}


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
  m_start_calculate = false;
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
      if(sval != m_mun_valse)
        m_start_calculate = true;
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
  uint64_t value = string2uint64();
  if(m_start_calculate){
  m_start_calculate = false;

  double tic,toc;
  tic = MOOSTime();
  
  string prime_ans = PrimeFactorCalculate(value);
  Notify("PRIME_RESULT", prime_ans); //publish msg

  toc = MOOSTime();  
  //m_out_result = "orig=" + m_mun_valse + ",received=" + "?" + ",calculated=" + "?" + ",solve_time=" + "?" + ",primes=" + m_out_valse + ",username=monica";

  //Notify("PRIME_RESULT_VALID", m_out_result); //publish msg
  Notify("CALCULATE_TIME", toc-tic); //publish msg
  }
  return(true);
}

uint64_t PrimeFactor::string2uint64()
{
  // string to uint64_t
  uint64_t inumber;
  std::istringstream iss(m_mun_valse);
  iss >> inumber;
  return inumber;
}

//even/odd calcutation
void PrimeFactor::EvenOddCalculate(uint64_t inumber)
{
  string s = "";
  if(inumber%2)
    s = "even";
  else
    s = "odd";
  stringstream ss("");
  ss << inumber << ", " << s;
  Notify("ODD_EVEN", ss.str());
}

//prime factor calcutation
string PrimeFactor::PrimeFactorCalculate(uint64_t inumber)
{
  stringstream ss("");
  if(inumber<3) {
    ss << inumber;
    return ss.str();
  }
  for(uint64_t x=2; x<=inumber; x++) {
    while(inumber%x == 0) {
      if(inumber/x != 1)
        ss << x << "*";
      else
        ss << x;
      inumber /= x;
    }
  }
  //Notify("PRIME_RESULT", ss.str()); //publish msg
  return ss.str();
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


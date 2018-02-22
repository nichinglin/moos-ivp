
#include <iostream>
#include "PrimeEntry.h"

#define DEBUG 0

using namespace std;

PrimeEntry::PrimeEntry()
{
  m_start_index = 2;
  m_solve_time = 0;
  m_done = false;
  username = "monica";
}
void PrimeEntry::setOriginalVal(unsigned long int v)
{
  m_orig = v;
  m_factors.push_back(v);
}
bool PrimeEntry::factor(unsigned long int max_steps)
{
  if(!m_done) {
    while(max_steps--) {
      uint64_t number = m_factors.back();
      if( m_start_index > sqrt(m_factors.back())) {
        if(DEBUG) {
          cout << "m_factors.back() is a prime" << m_factors.back() <<endl;
        }
        m_factors.pop_back();
        m_factors.push_back(number);
        number = 1;
        m_factors.push_back(number);
        m_start_index = 2;
      }
      if(number < 2) { // done!
        if(DEBUG)
          cout << "fine prime factor done!" << endl;
        m_done = true;
        getReport();
        return false;
      }
      if (number%m_start_index == 0) {
        if(DEBUG)
          cout << "fine a prime factor for this." << endl;
        m_factors.pop_back();
        m_factors.push_back(m_start_index);
        m_factors.push_back(number/m_start_index);
        m_start_index = 2;
      } else {
          m_start_index++;
      }
    }
  }
  if(DEBUG) {
    cout << "factor...." << endl;
    cout << m_factors.back() << ",now factor: " << m_start_index << endl;
  }
}

void PrimeEntry::setTime(double v) {
  if(DEBUG)
    cout << m_solve_time << endl;
  m_solve_time+=v;
}

std::string  PrimeEntry::getReport()
{
  string s;
  if(m_done) {
    //PRIME_RESULT = "orig=90090,received=34,calculated=33,solve_time=2.03,
    //                primes=2:3:3:5:7:11:13,username=jane"
    std::stringstream ss;
    ss << "orig=" << m_orig \
       << ",received=" << m_received_index \
       << ",calculated=" << m_calculated_index \
       << ",solve_time=" << m_solve_time \
       << ",primes=";
    for (int i=0; i<m_factors.size()-1; i++) {
      ss << m_factors[i];
      if(i < m_factors.size()-2)
        ss << ":";
    }
    ss << ",username=" << username;
    s = ss.str();
  }
  if(DEBUG) {
    if(m_done) {
      cout << s << endl;
    }
  }
  return s;
}

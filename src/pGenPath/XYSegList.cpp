/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYSegList.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include "XYSegList.h"

using namespace std;

//#define MAX 9999

XYSegList::XYSegList() {
  m_xypoint_list.clear();
}

void XYSegList::add_vertex(double x, double y) {
  XYPoint p(x,y);
  m_xypoint_list.push_back(p);

}

void XYSegList::greedy_path() {
  XYPoint point_pre;
  vector<XYPoint> path_list;
  while(!m_xypoint_list.empty()){
    vector<XYPoint>::iterator it;
    vector<XYPoint>::iterator p_next;
    double min_dis = MAX;
    for(it=m_xypoint_list.begin(); it!=m_xypoint_list.end(); ++it) {
      XYPoint &point_now = *it;
      double d = pow((point_now.x-point_pre.x),2) + pow((point_now.y-point_pre.y),2);
      d = sqrt(d);
      if(d < min_dis) {
        min_dis = d;
        p_next = it;
      }
    }
    path_list.push_back(*p_next);
    m_xypoint_list.erase(p_next);
  }
  m_xypoint_list = path_list;
}

string XYSegList::get_spec() {
  greedy_path();
  stringstream ss;
  ss << "points = ";
  vector<XYPoint>::iterator it;
  for (it=m_xypoint_list.begin(); it!=m_xypoint_list.end(); ++it) {
    XYPoint &point_msg = *it;
    if(it != m_xypoint_list.begin())
      ss << ":";
    ss << point_msg.x << "," << point_msg.y;
  }
  return ss.str();
}
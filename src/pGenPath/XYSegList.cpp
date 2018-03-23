/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYSegList.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include "XYSegList.h"

using namespace std;

#define MAX 9999

XYSegList::XYSegList() {
  m_point_list.clear();
  m_xypoint_list.clear();
  // m_start_x = 0.0;
  // m_start_y = 0.0;
}

void XYSegList::add_vertex(double x, double y) {
  XYPoint xy;
  xy.x = x;
  xy.y = y;
  xy.dis = MAX;
  m_xypoint_list.push_back(xy);

}

void XYSegList::greedy_path() {
}

string XYSegList::get_spec() {
  stringstream ss;
  ss << "points = ";
  deque<XYPoint>::iterator it;
  for (it=m_xypoint_list.begin(); it!=m_xypoint_list.end(); ++it) {
    XYPoint &point_msg = *it;
    if(it != m_xypoint_list.begin())
      ss << ":";
    ss << point_msg.x << "," << point_msg.y;
  }
  return ss.str();
}
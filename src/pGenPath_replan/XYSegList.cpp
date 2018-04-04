/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYSegList.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include "XYSegList.h"

#define DEBUG true

using namespace std;


XYSegList::XYSegList() {
  m_xypoint_list.clear();
  m_rm_list.clear();
  m_points_num = 0;
  m_visit_radius = 5.0;
}

void XYSegList::add_vertex(double x, double y) {
  XYPoint p(x,y);
  m_xypoint_list.push_back(p);
}

void XYSegList::rm_visit_vertex(int index, double nav_x, double nav_y) {
  vector<XYPoint>::iterator it = m_xypoint_list.begin() + index;
  XYPoint &point = *it;
  //if(DEBUG) cout << "point(x,y): " << point.x << "," << point.y << endl;
  //if(DEBUG) cout << "nav (x,y): " << nav_x << "," << nav_y << endl;
  double d = (pow((point.x-nav_x),2) + pow((point.y-nav_y),2));
  d = sqrt(d);
  //cout << d << endl;
  if(d < m_visit_radius) {
    int tmp;
    if(!m_rm_list.empty())
      tmp = m_rm_list.back();
    else
      tmp = -1;
    //cout << "delete: " << tmp << "," << index << endl;
    if(tmp != index) {
      m_rm_list.push_back(index);
      cout << "DELETE!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
    //m_xypoint_list.erase(it);
  }
}

bool XYSegList::empty() {
  return m_xypoint_list.empty();
}

// ------------------------------------
// greedy path:
// 0. Set a starting point as previous point
// 1. Calculate distance between previous point and other point
// 2. Get the point that has mininum distance between previous point and set it as next point
// 3. set next point as previous point
// 4. go back to step 1.
void XYSegList::greedy_path() {
  XYPoint point_pre;
  vector<XYPoint> path_list;
  while(!m_xypoint_list.empty()){
    vector<XYPoint>::iterator it;
    vector<XYPoint>::iterator p_next;
    double min_dis = MAX;
    // find local mininum
    for(it=m_xypoint_list.begin(); it!=m_xypoint_list.end(); ++it) {
      XYPoint &point_now = *it;
      double d = (pow((point_now.x-point_pre.x),2) + pow((point_now.y-point_pre.y),2));
      d = sqrt(d);
      if(d < min_dis) {
        min_dis = d;
        p_next = it;
      }
    }
    path_list.push_back(*p_next);
    point_pre = *p_next;
    m_xypoint_list.erase(p_next);
  }
  m_xypoint_list = path_list;
}

string XYSegList::get_spec() {

  vector<int>::iterator p;
  //for (p=m_rm_list.begin(); p!=m_rm_list.end(); ++p) {
  while (!m_rm_list.empty()) {
    int rm_index = m_rm_list.back();
    //int &rm_index = *p;
    vector<XYPoint>::iterator it = m_xypoint_list.begin() + rm_index;
    m_xypoint_list.erase(it);
    m_rm_list.pop_back();
  }
  m_rm_list.clear();

  if(m_xypoint_list.empty())
    return "points = 0.0,0.0";
  else {
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
    //cout << "get spec repo!!!" << endl;
    return ss.str();
    
  }

}
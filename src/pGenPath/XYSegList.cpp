/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYPoint.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include "XYSegList.h"

using namespace std;

XYSegList::XYSegList() {
  m_point_list.clear();
}

void XYSegList::add_vertex(double x, double y) {
  m_x.push_back(x);
  m_y.push_back(y);
  stringstream ss;
  if(!m_point_list.empty())
    ss << ":";
  ss << x << "," << y;
  m_point_list.push_back(ss.str());
}

void XYSegList::greedy_path() {
    // Sort jobs according to finish time
    sort(arr, arr+n, activityCompare);
 
    cout << "Following activities are selected n";
 
    // The first activity always gets selected
    int i = 0;
    cout << "(" << arr[i].start << ", " << arr[i].finish << "), ";
 
    // Consider rest of the activities
    for (int j = 1; j < n; j++)
    {
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it
      if (arr[j].start >= arr[i].finish)
      {
          cout << "(" << arr[j].start << ", "
              << arr[j].finish << "), ";
          i = j;
      }
    }}

string XYSegList::get_spec() {
  string update_str = "points = ";
  vector<string>::iterator it;
  for (it=m_point_list.begin(); it!=m_point_list.end(); ++it) {
    string &point_msg = *it;
    update_str += point_msg;
  }
  return update_str;
}
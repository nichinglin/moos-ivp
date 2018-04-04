/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYSegList.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include <deque>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <math.h>

#ifndef XYSegList_HEADER
#define XYSegList_HEADER

#define MAX 9999

class XYPoint
{
public:
	XYPoint() :x(0.0),y(0.0),dis(MAX){}
	XYPoint(double _x, double _y) :x(_x),y(_y),dis(MAX){}
	~XYPoint() {}

	double x;
	double y;
	double dis;
};

class XYSegList
{
public:
	XYSegList();
	~XYSegList() {}

	void add_vertex(double x, double y);      // add new point into list
	void rm_visit_vertex(int index, double nav_x, double nav_y);          // remove if within visit raduius
	void set_visit_radius(double v) {m_visit_radius = v;} // set visit radius
	std::string get_spec();                   // msg type for WayPoint BHV. such as "points = 10,50:-20,30:0,-10"
	int get_points() {return m_xypoint_list.size();}   // visit point number
	bool empty();

protected:
	void greedy_path();                      // path planing

	std::vector<XYPoint> m_xypoint_list;
	std::vector<int> m_rm_list;
	int m_points_num;
	double m_visit_radius;
};

#endif 
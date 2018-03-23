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

	void add_vertex(double x, double y);     // add new point into list
	std::string get_spec();                  // msg type for WayPoint BHV. such as "points = 10,50:-20,30:0,-10"
	int get_points() {return m_points_num;}  // visit point number

protected:
	void greedy_path();                      // path planing

	std::vector<XYPoint> m_xypoint_list;
	int m_points_num;
};

#endif 
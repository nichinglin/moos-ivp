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

	void add_vertex(double x, double y);
	std::string get_spec();

protected:
	void greedy_path();

	std::vector<XYPoint> m_xypoint_list;
};

#endif 
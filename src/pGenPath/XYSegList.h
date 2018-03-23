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

#ifndef XYSegList_HEADER
#define XYSegList_HEADER

class XYPoint
{
public:
	XYPoint() {}
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

	std::vector<std::string> m_point_list;

	std::deque<XYPoint> m_xypoint_list;
};

#endif 
/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYPoint.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include <vector>
#include <iterator>
#include <sstream>

#ifndef XYSegList_HEADER
#define XYSegList_HEADER

class XYSegList
{
public:
	XYSegList();
	~XYSegList() {}

	void add_vertex(double x, double y);
	std::string get_spec();

protected:
	void greedy_path();

	struct Activitiy
	{
		int start, finish;
	};
	bool activityCompare(Activitiy s1, Activitiy s2)
	{
		return (s1.finish < s2.finish);
	}

	std::vector<double> m_x;
	std::vector<double> m_y;
	std::vector<std::string> m_point_list;
};

#endif 
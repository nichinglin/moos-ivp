/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYPoint.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include <iterator>

#ifndef XYPointView_HEADER
#define XYPointView_HEADER

class XYPointView
{
public:
	XYPointView(double x, double y);
	~XYPointView(){}

	void set_label(std::string v) {m_label=v;}
	void set_color(std::string v) {m_color=v;}
	void set_param(std::string v) {m_size=v;}
	std::string get_spec();

protected:
	double m_x;
	double m_y;
	std::string m_label;
	std::string m_color;
	std::string m_size;
};

#endif 
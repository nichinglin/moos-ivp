/************************************************************/
/*    NAME: Monica Lin                                      */
/*    ORGN: NCTU                                            */
/*    FILE: XYPoint.h                                       */
/*    DATE: March 20th, 2018                                */
/************************************************************/

#include <sstream>
#include "XYPointView.h"

using namespace std;

XYPointView::XYPointView(double x, double y)
  :m_x(x),m_y(y)
{
  m_size = "5";
  m_id = 99999;
  m_color = "red";
}

string XYPointView::get_spec(){
  //(" << m_id << ")
  stringstream view_point_msg;
  view_point_msg << "x=" << m_x << "," \
                 << "y=" << m_y << "," \
                 << "label=," \
                 << "vertex_color=" << m_color << "," \
                 << "vertex_size=" << m_size;
  return view_point_msg.str();
}
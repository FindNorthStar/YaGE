#ifndef DRAW_PAINT_H
#define DRAW_PAINT_H
#include <cairo.h>
#include "point.h"
#include "color.h"
#include "font.h"

namespace yage {
namespace draw {

class Paint
{
  private:
    cairo_matrix_t matrix_;
    Point viewport_left_top_;
    Point viewport_right_bottom_;
  public:
    double line_width;
    Color line_color;
    Color fill_color;
    Color font_color;
    Color background_color;
    Font font;

    Paint();
    void set_translate(double tx, double ty);
    void set_rotate(double radians);
    void set_scale(double sx,double sy);
    void set_viewport(Point left_top,Point right_bottom);
    void get_viewport(Point& left_top,Point& right_bottom) const;
    void set_viewport_full_canvas();
    static bool is_viewport_full_canvas(Point& left_top,Point& right_bottom);
    bool is_viewport_full_canvas() const;
    const cairo_matrix_t* pro_get_cairo_matrix() const;
};

}
}

#endif // PAINT_H

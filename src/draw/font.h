#ifndef FONT_H_
#define FONT_H_
#include <pango/pango-font.h>
#include <string>

namespace yage {
namespace draw {

class Font {
private:
    PangoFontDescription *description_;
public:
    Font(std::string family = "", int size = 12, bool is_bold = false, bool is_italic = false);
	Font(Font &font);
    ~Font();

    std::string get_font_family(void) const;
    int get_size(void) const;
    bool get_bold_status(void) const;
    bool get_italic_status(void) const;

    void set_font_family(std::string family);
    void set_size(int size);
    void set_bold_status(bool is_bold);
    void set_italic_status(bool is_italic);

    PangoFontDescription *pro_get_pango_font(void);
    void pro_set_pango_font(PangoFontDescription *description);
};


}
}


#endif //FONT_H_

#include "uitext.hpp"

UIText::UIText(int x, int y, int bg, int fg, String text):UIElement(x, y, bg, fg),_text(text) {}

UIText::~UIText() {
}

void UIText::draw(Screen& screen, BoxState& state, int bg, int fg) {
    int16_t x1, y1;
    uint16_t w, h;
    display_t& d = screen.get_display();

    d.setFont(FONT);
    d.setTextSize(1);

    d.getTextBounds(_text, _x, _y, &x1, &y1, &w, &h);

    int padding = 2;

    int x0 = x1 - padding;
    int y0 = y1 - padding;
    int w0 = w + 2 * padding;
    int h0 = h + 2 * padding;

    d.fillRect(x0, y0, w0, h0, bg);

    d.setTextColor(fg, bg);
    d.setCursor(_x, _y);
    d.print(_text.c_str());
}

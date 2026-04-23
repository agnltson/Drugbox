#include "uitime.hpp"

UITime::UITime(int x, int y, int bg, int fg, int id)
    : UIElement(x, y, bg, fg), _compartment_id(id) {}

UITime::~UITime() {}

void UITime::draw(Screen& screen, BoxState& state, int bg, int fg) {
    Time time = state.get_compartment(_compartment_id).get_reminder_time();
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", (int)time.hour(), (int)time.minute());

    int16_t x1, y1;
    uint16_t w, h;
    display_t& d = screen.get_display();

    d.getTextBounds(String(buf), _x, _y, &x1, &y1, &w, &h);

    int padding = 2;

    int x0 = x1 - padding;
    int y0 = y1 - padding;
    int w0 = w + 2 * padding;
    int h0 = h + 2 * padding;

    d.fillRect(x0, y0, w0, h0, bg);

    d.setTextColor(fg, bg);
    d.setCursor(_x, _y);
    d.print(buf);
}

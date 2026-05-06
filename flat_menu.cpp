#include "flat_menu.hpp"
#include "uitext.hpp"

#define LINE_H 20
#define LINE_START 20      // y de la première ligne de contenu
#define TITLE_Y 20         // y du titre
#define MARGIN_X 10        // x de tous les éléments
#define LIST_START 20      // y du premier élément de liste (draw_list)

FlatMenu::FlatMenu() : _cursor(0), _in_action(false) {
    _actions.push_back({"Voir cooldown",  ACTION_VIEW_COOLDOWN, ASTATE_IDLE, 0});
    _actions.push_back({"Prendre pilule", ACTION_TAKE_PILL,     ASTATE_IDLE, 0});
    _actions.push_back({"Regler rappel",  ACTION_SET_REMINDER,  ASTATE_IDLE, 0});
}

void FlatMenu::draw(Screen& screen, BoxState& state, int bg, int fg) {
    if (_in_action)
        draw_action(screen, state, bg, fg);
    else
        draw_list(screen, state, bg, fg);
}

void FlatMenu::draw_list(Screen& screen, BoxState& state, int bg, int fg) {
    for (int i = 0; i < _actions.size(); ++i) {
        UIText item(MARGIN_X, LIST_START + LINE_H * (i + 1), bg, fg, _actions[i].label);
        if (i == _cursor)
            item.draw(screen, state, fg, bg);
        else
            item.draw(screen, state, bg, fg);
    }
}

void FlatMenu::draw_action(Screen& screen, BoxState& state, int bg, int fg) {
    Action& a = _actions[_cursor];
    UIText title(MARGIN_X, TITLE_Y, bg, fg, a.label);
    title.draw(screen, state, bg, fg);

    switch (a.type) {
        case ACTION_VIEW_COOLDOWN: {
            Time next = state.get_next_take(state.get_current_time());
            char buf[16];
            snprintf(buf, sizeof(buf), "Interdit: %02d:%02d", next.hour(), next.minute());
            UIText t1(MARGIN_X, LINE_START + LINE_H,   bg, fg, buf);
            UIText t2(MARGIN_X, LINE_START + 2*LINE_H, bg, fg, "retour=menu");
            t1.draw(screen, state, bg, fg);
            t2.draw(screen, state, bg, fg);
            break;
        }
        case ACTION_TAKE_PILL: {
            char buf[24];
            if (a.state == ASTATE_CONFIRM) {
                snprintf(buf, sizeof(buf), "+%dh apres prise", a.param);
                UIText t1(MARGIN_X, LINE_START + LINE_H,   bg, fg, buf);
                UIText t2(MARGIN_X, LINE_START + LINE_H*2, bg, fg, "ok=valider");
                UIText t3(MARGIN_X, LINE_START + LINE_H*3, bg, fg, "retour=annuler");
                t1.draw(screen, state, bg, fg);
                t2.draw(screen, state, bg, fg);
                t3.draw(screen, state, bg, fg);
            } else {
                snprintf(buf, sizeof(buf), "Reappliquer +%dh", a.param);
                UIText t1(MARGIN_X, LINE_START,            bg, fg, buf);
                UIText t2(MARGIN_X, LINE_START + LINE_H,   bg, fg, "suiv=changer duree");
                UIText t3(MARGIN_X, LINE_START + LINE_H*2, bg, fg, "ok=confirmer");
                UIText t4(MARGIN_X, LINE_START + LINE_H*3, bg, fg, "retour=menu");
                t1.draw(screen, state, bg, fg);
                t2.draw(screen, state, bg, fg);
                t3.draw(screen, state, bg, fg);
                t4.draw(screen, state, bg, fg);
            }
            break;
        }
        case ACTION_SET_REMINDER: {
            char buf[16];
            snprintf(buf, sizeof(buf), "Dans: %02dh", a.param);
            UIText t1(MARGIN_X, LINE_START + LINE_H,   bg, fg, buf);
            UIText t2(MARGIN_X, LINE_START + LINE_H*2, bg, fg, "suiv=+1h");
            UIText t3(MARGIN_X, LINE_START + LINE_H*3, bg, fg, "ok=sauvegarder");
            UIText t4(MARGIN_X, LINE_START + LINE_H*4, bg, fg, "retour=annuler");
            t1.draw(screen, state, bg, fg);
            t2.draw(screen, state, bg, fg);
            t3.draw(screen, state, bg, fg);
            t4.draw(screen, state, bg, fg);
            break;
        }
    }
}

UIMessage FlatMenu::handle_input(input_type_e type) {
    if (_in_action)
        return handle_action_input(type);

    switch (type) {
        case IP_NEXT:   // "suivant" — défile vers le bas cycliquement
            _cursor = (_cursor + 1) % _actions.size();
            break;
        case IT_SELECT:
            _in_action = true;
            _actions[_cursor].state = ASTATE_IDLE;
            break;
        default: break;
    }
    return UIMessage();
}

UIMessage FlatMenu::handle_action_input(input_type_e type) {
    Action& a = _actions[_cursor];

    if (type == IT_RETURN) {
        _in_action = false;
        a.state = ASTATE_IDLE;
        return UIMessage();
    }

    switch (a.type) {
        case ACTION_VIEW_COOLDOWN:
            // rien à faire, retour géré au-dessus
            break;

        case ACTION_TAKE_PILL:
            if (type == IT_SELECT) {
                if (a.state == ASTATE_CONFIRM) {
                    _in_action = false;
                    a.state = ASTATE_IDLE;
                    return UIMessage(UIM_SET_NEXT_TAKE, Time(a.param, 0));
                } else {
                    a.state = ASTATE_CONFIRM;
                }
            } else if (type == IP_NEXT) {
                // "suivant" change la durée de cooldown proposée
                a.param = (a.param % 24) + 1;
            }
            break;

        case ACTION_SET_REMINDER:
            if (type == IT_SELECT) {
                _in_action = false;
                return UIMessage(UIM_SET_NEXT_TAKE, Time(a.param, 0));
            }
            if (type == IP_NEXT)
                a.param = (a.param % 24) + 1;
            else if (type == IT_SELECT) {
                _in_action = false;
                return UIMessage(UIM_SET_NEXT_TAKE, Time(a.param, 0));
            }
            break;
    }
    return UIMessage();
}

#pragma once
#include <vector>
#include "drawable.hpp"
#include "interactive.hpp"
#include "box_state.hpp"

typedef enum {
    ACTION_VIEW_COOLDOWN,
    ACTION_TAKE_PILL,
    ACTION_SET_REMINDER,
} action_type_e;

typedef enum {
    ASTATE_IDLE,        // liste principale, curseur sur cet item
    ASTATE_ACTIVE,      // action en cours (sous-interaction)
    ASTATE_CONFIRM,     // confirmation avant de valider
} action_state_e;

struct Action {
    const char* label;
    action_type_e type;
    action_state_e state = ASTATE_IDLE;
    int param = 0;       // ex: nb heures pour le cooldown
};

class FlatMenu : public Drawable, public Interactive {
public:
    FlatMenu();
    void draw(Screen& screen, BoxState& state, int bg, int fg) override;
    UIMessage handle_input(input_type_e type) override;
private:
    std::vector<Action> _actions;
    int _cursor;         // quel item est sélectionné dans la liste
    bool _in_action;     // sommes-nous dans une sous-interaction ?

    void draw_list(Screen& screen, BoxState& state, int bg, int fg);
    void draw_action(Screen& screen, BoxState& state, int bg, int fg);
    UIMessage handle_action_input(input_type_e type);
};

#pragma once

#include "time.hpp"

typedef enum {
    UIM_EMPTY,
    UIM_SET_NEXT_TAKE,  // remplace UIM_TOOK_PILL et UIM_SET_COOLDOWN
} uimessage_type_e;

class UIMessage {
    public:
    UIMessage(uimessage_type_e type, Time offset);
    UIMessage();
    uimessage_type_e get_type() { return _type; }
    Time get_offset() { return _offset; }
    private:
    uimessage_type_e _type;
    Time _offset;
};

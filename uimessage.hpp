#pragma once

#include "time.hpp"

typedef enum {
    UIM_EMPTY,
    UIM_TOOK_PILL,
    UIM_SET_COOLDOWN,
} uimessage_type_e;

class UIMessage {
    public:
    UIMessage(uimessage_type_e type, Time offset);
    UIMessage();
    private:
    uimessage_type_e _type;
    Time _offset;
};

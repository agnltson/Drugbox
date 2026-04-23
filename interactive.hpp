#pragma once

#include "input_type.hpp"
#include "uimessage.hpp"

class Interactive {
    public:
    virtual UIMessage handle_input(input_type_e type) = 0;
};

#pragma once

#include "input_type.hpp"

class Interactive {
    public:
    virtual void handle_input(input_type_e type) = 0;
};

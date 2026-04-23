#include "uimessage.hpp"

UIMessage::UIMessage(uimessage_type_e type, Time offset):_type(type),_offset(offset) {}
UIMessage::UIMessage():_type(UIM_EMPTY),_offset(0, 0) {}

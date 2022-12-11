//
// Created by Abdelouahad Ait hamd on 12/9/22.
//

#include "OutOfBoundExecption.h"

ft::OutOfBoundExecption::OutOfBoundExecption(const std::string &message)_NOEXCEPT
: _message(message) {}


const char *ft::OutOfBoundExecption::what() const _NOEXCEPT  {
    return   std::string("Out of bound exception: " + _message).c_str();
}

ft::OutOfBoundExecption::~OutOfBoundExecption() _NOEXCEPT {

}

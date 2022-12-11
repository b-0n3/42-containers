//
// Created by Abdelouahad Ait hamd on 12/9/22.
//

#ifndef FT_CONTAINERS_OUTOFBOUNDEXECPTION_H
#define FT_CONTAINERS_OUTOFBOUNDEXECPTION_H
#include <exception>
#include <string>
namespace  ft {
    class OutOfBoundExecption : std::exception {
    private:
        std::string _message;
    public:
        OutOfBoundExecption(std::string const &message) _NOEXCEPT;

        virtual const char *what()const _NOEXCEPT ;

        virtual  ~OutOfBoundExecption() _NOEXCEPT;
    };

};
#endif //FT_CONTAINERS_OUTOFBOUNDEXECPTION_H

//
// Created by tsofi on 28/04/2019.
//

#ifndef LIST_WET1EXCEPTIONS_H
#define LIST_WET1EXCEPTIONS_H

#include <exception>

namespace Wet1Utils {
    class Wet1Exceptions : public std::exception{
    public:
        virtual ~Wet1Exceptions() throw(){}
    };

    class KeyNotExist:public Wet1Exceptions{
        virtual const char* what() const throw(){
            return "Wet1Exception: Cannot find key in tree.";
        }
    };

    class IllegalValue:public Wet1Exceptions{
        virtual const char* what() const throw(){
            return "Wet1Exception: Illegal value.";
        }
    };

    class OutOfBounds:public Wet1Exceptions{
        virtual const char* what() const throw(){
            return "Wet1Exception: Out of bounds.";
        }
    };

    class NullArgument:public Wet1Exceptions{
        virtual const char* what() const throw(){
            return "Wet1Exception: Null Argument.";
        }
    };
}


#endif //LIST_WET1EXCEPTIONS_H

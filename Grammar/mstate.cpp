#include "mstate.h"
#include "mstate_impl.h"
#include "util.h"


#define PRINTENUM(ENUM) \
    case ENUM: \
        out << #ENUM; \
        break


namespace mstate
{
    mstate parse_character(char character)
    {
        if(is_space(character))
        {
            return SPACEM;
        } else if(is_digit(character))
        {
            return DIGITM;
        } else if(is_letter(character))
        {
            return LETTERM;
        } else if (
                is_sign(character) 
            || character == '=' 
            || character == ';' 
            || character == ','
            || character == '('
            || character == ')'
            || character == '}'
            || character == '{'
        ) {
            return SIGNM;
        }else if (character == '.')
        {
            return DOTM;
        } else if (character == '\"')
        {
            return QUOTEM;
        } else
            return ELSEM;
    }

    std::ostream& operator <<(std::ostream& out, mstate ms)
    {
        switch (ms)
        {
        PRINTENUM(LETTERM);
        PRINTENUM(DIGITM);
        PRINTENUM(SPACEM);
        PRINTENUM(SIGNM);
        PRINTENUM(DOTM);
        PRINTENUM(QUOTEM);
        PRINTENUM(ELSEM);
        }
        return out;
    }
}

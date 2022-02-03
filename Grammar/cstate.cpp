#include "cstate.h"
#include "cstate_impl.h"
#include <ostream>


#define PRINTENUM(ENUM) \
    case ENUM: \
        out << #ENUM; \
        break

namespace cstate
{

    std::ostream& operator<<(std::ostream& out, cstate cs)
    {
        switch (cs)
        {
        PRINTENUM(NULLM);
        PRINTENUM(LETTER);
        PRINTENUM(DIGIT1);
        PRINTENUM(DIGIT2);
        PRINTENUM(DIGIT3);
        PRINTENUM(SPACE1);
        PRINTENUM(SPACE2);
        PRINTENUM(SPACE3);
        PRINTENUM(SPACE4);
        PRINTENUM(SPACEN1);
        PRINTENUM(SPACEN2);
        PRINTENUM(SIGN1);
        PRINTENUM(SIGN2);
        PRINTENUM(SIGN3);
        PRINTENUM(SIGN4);
        PRINTENUM(SIGNN);
        PRINTENUM(QUOTE1);
        PRINTENUM(QUOTE2);
        case STAR:
            out << "\"*\"";
            break;
        PRINTENUM(DOT1);
        PRINTENUM(DOT2);
        PRINTENUM(INTEGER);
        PRINTENUM(KEYWORD);
        PRINTENUM(FLOAT);
        PRINTENUM(STRING);
        }
        return out;
    }
}

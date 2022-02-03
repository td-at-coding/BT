#include <iostream>
#include "pattern.h"
#include "pattern_impl.h"

#define PRINTENUM(ENUM) \
    case ENUM: \
        out << #ENUM; \
        break

#define PRINTENUM2(ENUM, TEXT) \
        std::cout << "\t" #ENUM " " TEXT "\n" ; \


namespace pattern
{

    std::ostream& operator << (std::ostream& out, pattern o )
    {
        switch (o)
        {
        PRINTENUM(BEGINNING);
        PRINTENUM(END);
        PRINTENUM(KEYWORD1);
        PRINTENUM(KEYWORD2);
        PRINTENUM(KEYWORD3);
        PRINTENUM(KEYWORD4);
        PRINTENUM(KEYWORD5);
        PRINTENUM(STRING);
        PRINTENUM(INTEGER);
        PRINTENUM(SIGNPM);
        PRINTENUM(SIGNP1);
        PRINTENUM(SIGNP2);
        PRINTENUM(SIGNP3);
        PRINTENUM(SIGN);
        PRINTENUM(SIGNE);
        PRINTENUM(SCOPEBEGIN);
        PRINTENUM(SCOPEEND);
        PRINTENUM(FSCOPEBEGIN);
        PRINTENUM(FSCOPEEND);
        PRINTENUM(ARGBEGIN);
        PRINTENUM(ARGEND);
        PRINTENUM(COMMA);
        PRINTENUM(CALL1);
        PRINTENUM(CALL2);
        PRINTENUM(COMMAC);
        }
        return out;
    }


    void print_styles ()
    {
        PRINTENUM2(KEYWORD1, "[color=red, label=KEYWORD]");
        PRINTENUM2(KEYWORD2, "[color=red, label=KEYWORD]");
        PRINTENUM2(KEYWORD3, "[color=red, label=KEYWORD]");
        PRINTENUM2(KEYWORD4, "[color=red, label=KEYWORD]");
        PRINTENUM2(KEYWORD5, "[color=red, label=KEYWORD]");
        PRINTENUM2(SIGNP1, "[color=yellow, label=PLUS]");
        PRINTENUM2(SIGNP2, "[color=yellow, label=PLUS]");
        PRINTENUM2(SIGNP3, "[color=yellow, label=PLUS]");
        PRINTENUM2(CALL1, "[color=green, label=CALL]");
        PRINTENUM2(CALL2, "[color=green, label=CALL]");
        PRINTENUM2(COMMAC, "[color=green, label=COMMA]");
        PRINTENUM2(COMMA, "[color=green, label=COMMA]");
    }
}
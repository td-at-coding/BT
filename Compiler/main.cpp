#include <iostream>
#include "Parser.h"
using namespace std;

ostream& operator << (ostream& out, const Parser& parser)
{
    // for (size_t i = 0; i < parser.functions.size(); i++)
    // {
    //     out << parser.functions[i];
    // }
    // out << endl <<"functions: " << parser.functions.size() << endl; 
    parser.states[0].print_values();
    out << endl <<"states: " << parser.states.size() << endl; 
    // out << endl <<"states_storage: " << parser.states[0].storage.size() << endl; 
    return out;
}

int main()
{
    string A = 
        "a = 2;"
        "c = 5 + a + 3;"
        // "k& = 3;"
        "addab = take(a, b) return a + b;"
        "addabc = take(a, b) c = 5; y = 7; return a + b + c;"
        "kc = take() return 5;"
        "y = addab(4,3);"
        "h = addabc(4,3);"
        "ho = kc();"
        // "hh = addabc(4,3) + 1;"
    ;
    string B = 
        "c = c + 2;"
    ;


    bool parsing;
    Parser parser;
    parsing = parser.insert(A);
    cout << "parsing is " << parsing << endl;
    parsing = parser.insert(B);
    cout << "parsing is " << parsing << endl;
    cout << parser;

    cout << "parsing texts." << endl;
}


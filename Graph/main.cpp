#include <iostream>
#include <string>
// #include "StateMachine.h"
// #include "loader.h"
#include "Grammar.h"
#include "Reader.h"
#include "cstate_impl.h"
#include <fstream>
using namespace std;


int main()
{
    Grammar& g = create_grammar();
    Reader& r = create_reader();
    cout << g;
    delete_grammar(g);
    delete_reader(r);
    return 0;
}
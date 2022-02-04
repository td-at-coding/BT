#include <iostream>
#include <string>
// #include "Expression.h"
#include "var_type.h"
#include "util.h"
// #include "StateMachine.h"
#include <fstream>
#include "Linter.h"
#include "Parser.h"
#include "Term.h"
using namespace std;

int main()
{
    

    string line = "";
    cout << "press q to exit" << endl;
    State state;
    Linter linter;
    Parser parser;
    std::vector<Term> terms;
    state.insert_data("a","2", INTEGER);
    state.insert_function("five = take() return 5;");
    state.insert_function("ten = take() eight = 8; return eight + 2;");
    state.insert_function("sum = take(a,b) return a + b;");
    state.insert_function("print = take(a) return a;");
    while(true)
    {
        cout << "> ";
        getline(cin, line);
        try
        {
            /* code */
            if(line == "q" || line == "Q") break;
            else if (line == "clear") {
                system(line.c_str());
                continue;
            }
            else if(linter.lint_program(line) == false)
            {
                cout << "invalid syntax" << endl;
                return 1;
            }
            else if (parser.run_program(line,state,terms) )
            {
                for (size_t i = 0; i < terms.size(); i++)
                {
                    Term& term = terms[i];
                    cout << term << "; ";
                }
                cout <<  endl;
                terms.clear();
                
            }
        }
        catch(char const* error)
        {
            std::cerr << error << '\n';
            cout << line << endl;
        }
        catch (std::invalid_argument const& ex)
        {
            std::cerr << "invalid argument " << ex.what() << '\n';
            cout << line << endl;
        }
        
    }
    return 0;
}
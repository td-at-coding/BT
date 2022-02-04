#include "Grammar.h"
#include "Reader.h"
#include "State.h"

class Parser
{
public:
    bool run_program(
        std::string program
        , State& state
        , std::vector<Term> & terms
    );
    bool run_program(
          std::string program
        , std::vector<std::pair<std::string,cstate::cstate>>& list
        , State& state
        , std::vector<Term> & terms
    );
    ~Parser();
private:
    Grammar& g = create_grammar();
    Reader& r = create_reader();
};


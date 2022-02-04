#include "Parser.h"


bool Parser::run_program(
    std::string program
    , State& state
    , std::vector<Term> & terms
)
{
    auto list = parse_program(r,program);
    return is_valid_program(g,list, state, terms);
}

bool Parser::run_program(
    std::string program
    , std::vector<std::pair<std::string,cstate::cstate>>& list
    , State& state
    , std::vector<Term> & terms

)
{
    list = parse_program(r, program);
    return is_valid_program(g, list, state, terms);
}


Parser::~Parser()
{
    delete_grammar(g);
    delete_reader(r);
}
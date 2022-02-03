#include "Linter.h"


bool Linter::lint_program(std::string program)
{
    auto list = parse_program(r,program);
    return is_valid_pattern(g,list);
}

bool Linter::lint_program(
    std::string program
    , std::vector<std::pair<std::string,cstate::cstate>>& list
)
{
    list = parse_program(r, program);
    return is_valid_pattern(g, list);
}


Linter::~Linter()
{
    delete_grammar(g);
    delete_reader(r);
}
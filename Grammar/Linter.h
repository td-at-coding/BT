#include "Grammar.h"
#include "Reader.h"


class Linter
{
public:
    bool lint_program(std::string program);
    bool lint_program(
          std::string program
        , std::vector<std::pair<std::string,cstate::cstate>>& list
    );
    ~Linter();
private:
    Grammar& g = create_grammar();
    Reader& r = create_reader();
};


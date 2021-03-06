#include "StateMachine.h"
#include "pattern.h"
#include "cstate.h"
#include <vector>
#include <utility>
#include "State.h"

struct Grammar;


Grammar& create_grammar();
void delete_grammar(Grammar& grammar);

std::ostream& operator<<(std::ostream& out, const Grammar& grammar);

bool is_valid_pattern(
    const Grammar& grammar
    , const std::vector<std::pair<std::string,cstate::cstate>>& feed
);

bool is_valid_program(
    const Grammar& grammar
    , const std::vector
    <
        std::pair
        <
            std::string
            , cstate::cstate
        >
    >& feed
    , State& s
    , std::vector<Term>& value
);
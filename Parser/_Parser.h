#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "State.h"

class Parser
{
private:
    std::vector<State> states;
public:
    Parser();
    bool is_valid_object(const std::string& str);
    bool is_valid_function(const std::string& str);
    bool is_valid_state(const std::string& str);
    bool insert(const std::string& str);
    friend std::ostream& operator << (std::ostream& out, const Parser& parser);
};





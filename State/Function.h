#pragma once
#include <string>
#include <vector>
#include "Data.h"

class Term;
class State;

class Function
{
private:
    std::vector<Data> arguments;
    std::vector<Data> statements;
    std::string return_expression;
    std::string name;
    bool get_value(const std::string name, std::string& value) const;
    bool get_value(const std::string name, float& value) const;
    bool get_value(const std::string name, int& value) const;
public:
    bool init(std::string str);
    bool evaluate(std::vector<Data> args, const State& state, Term& value);
    bool contains_name(std::string name) const;
    std::string get_name() const;
    std::string get_return_expression() const;
    size_t get_length() const;
};

std::vector<std::string> combine(const std::vector<std::string>& terms,const std::vector<std::string>& ops);
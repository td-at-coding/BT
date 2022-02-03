#pragma once
#include <vector>
#include "Data.h"
#include "Function.h"

class Term;

class State
{
public:
    State();
    unsigned get_scope() const;
    bool contains_name(std::string name) const;
    bool contains_function(std::string name) const;
    bool get_value(const std::string name, std::string& value) const;
    bool get_value(const std::string name, float& value) const;
    bool get_value(const std::string name, int& value) const;
    bool get_function(const std::string name, Function& func) const;
    bool get_type(const std::string name, var_type& value) const;
    bool insert_name(std::string name);
    bool insert_function(std::string function);
    bool insert_data(std::string name, std::string value, var_type type);
    bool set_value(std::string name, std::string value, var_type type);
    bool load_value(std::vector<Term>& terms, const std::string& name, int first_letter);
    void print_values() const;
    void clear();
private:
    // class data
    static unsigned global_scope;
    // object data
    unsigned scope;
    std::vector<Data> storage;
    std::vector<Function> functions;
};
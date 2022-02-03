#pragma once
#include <string>
#include <vector>

enum oper_types : int;

class Operation
{
private:
    int priority;
    std::vector<std::string> operands;
    oper_types type;
    int id;
    static int id_tracker;
public:
    Operation* next = nullptr;
    Operation* previous = nullptr;
    Operation();
    bool init(std::vector<std::string> operands, oper_types type, int priority);
    int get_priority() const;
    int get_id() const;
    std::vector<std::string> get_operands() const;
    bool set_operand1(std::string value);
    bool set_operand2(std::string value);
    oper_types get_type() const;
    std::string operator()() const;

};

bool greater_priority(const Operation& A, const Operation& B);

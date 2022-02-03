#include "Operation.h"
#include "oper_types.h"
#include <iostream>


int Operation::id_tracker = 0;


Operation::Operation()
{
    id = id_tracker++;
}

int Operation::get_priority() const
{
    return priority;
}


int Operation::get_id() const
{
    return id;
}


std::vector<std::string> Operation::get_operands() const
{
    return operands;
}

oper_types Operation::get_type() const
{
    return type;
}
bool Operation::init
    (
        std::vector<std::string> operands, 
        oper_types type, 
        int priority
    )
{
    this->operands = operands;
    this->type = type;
    this->priority = priority;
    return true;
}

std::string Operation::operator()() const
{
    std::string value;
    switch (type)
    {
    case PLUS:
        {
            // std::cout <<"operation[" << parameter.get_priority() <<"] = "<< operands[0] << " + " << operands[1] << std::endl;
            return std::to_string(std::stoi(operands[0]) + std::stoi(operands[1]));
            break;
        }
    case MINUS:
        {
            // std::cout <<"operation[" << parameter.get_priority() <<"] = "<< operands[0] << " - " << operands[1] << std::endl;
            return std::to_string(std::stoi(operands[0]) - std::stoi(operands[1]));
            break;
        }
    case MULTI:
        {
            // std::cout <<"operation[" << parameter.get_priority() <<"] = "<< operands[0] << " * " << operands[1] << std::endl;
            return std::to_string(std::stoi(operands[0]) * std::stoi(operands[1]));
            break;
        }
    case DIV:
        {
            // std::cout <<"operation[" << parameter.get_priority() <<"] = "<< operands[0] << " / " << operands[1] << std::endl;
            return std::to_string(std::stoi(operands[0]) / std::stoi(operands[1]));
            break;
        }
    
    default:
        return "";
        break;
    }
}



bool greater_priority(const Operation& A, const Operation& B)
{
    return A.get_priority() < B.get_priority();
}


bool Operation::set_operand1(std::string value)
{
    // std::cout << "before operands[0] = "<< operands[0] << " value = " << value << std::endl; 
    operands[0] = value;
    // std::cout << "after operands[0] = "<< operands[0] << " value = " << value << std::endl; 
    return true;
}
bool Operation::set_operand2(std::string value)
{
    operands[1] = value;
    return true;
}
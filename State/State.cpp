#include "State.h"
#include "var_type.h"
#include "Term.h"
#include <iostream>


unsigned State::global_scope = 0;


State::State()
    : scope(++global_scope)
{}

void State::clear()
{
    storage.clear();
    functions.clear();
}


bool State::contains_name(std::string name) const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name) return true;
    }
    for (size_t i = 0; i < functions.size(); i++)
    {
        if(functions[i].get_name() == name) return true;
    }
    return false;
}

bool State::contains_function(std::string name) const
{
    for (size_t i = 0; i < functions.size(); i++)
    {
        if(functions[i].get_name() == name) return true;
    }
    return false;
}


bool State::get_value(const std::string name, std::string& value) const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            storage[i].get_value(value);
            return true;
        }
        
    }
    return false;
}
bool State::get_value(const std::string name, float& value) const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            storage[i].get_value(value);
            return true;
        }
        
    }
    return false;
}

bool State::get_value(const std::string name, int& value) const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            storage[i].get_value(value);
            return true;
        }
        
    }
    return false;
}
bool State::get_function(const std::string name, Function& func) const
{
    for (size_t i = 0; i < functions.size(); i++)
    {
        if(functions[i].get_name() == name) {
            func = functions[i];
            return true;
        }
    }
    return false;
}

bool State::get_type(const std::string name, var_type& type) const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            type = storage[i].get_type();
            return true;
        }
        
    }
    return false;
}

bool State::insert_name(std::string name)
{
    storage.push_back({name});
    return true;
}

bool State::insert_data(std::string name, std::string value, var_type type)
{
    if(this->contains_name(name) == false)
        storage.push_back({name,value,type});
    else
        set_value(name,value,type);
    return true;
}


bool State::set_value(std::string name, std::string value, var_type type)
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            storage[i].set_value(value,type);
            return true;
        }
        
    }
    return false;
}

void State::print_values() const
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        std::cout << storage[i].get_name() << 
            " size of " << storage[i].get_name().length() 
            << " value of (" << storage[i].get_value() <<
            ") size of " << storage[i].get_value().length() << std::endl;
    }
    for (size_t i = 0; i < functions.size(); i++)
    {
        std::cout << functions[i].get_name() << 
            " size of " << functions[i].get_name().length() 
            << " value of (" << functions[i].get_return_expression() <<
            ") size of " << functions[i].get_return_expression().length() <<
            " function arguments: " << functions[i].get_length()
            << std::endl;
    }
}

bool State::insert_function(std::string function)
{
    Function func;
    func.init(function);
    functions.push_back(func);
    return true;
}

bool State::load_value(std::vector<Term>& terms, const std::string& name, int first_letter)
{
    for (size_t i = 0; i < storage.size(); i++)
    {
        if(storage[i].get_name() == name)
        {
            Term A;
            switch (storage[i].get_type())
            {
            case INTEGER:
            {
                int value;
                storage[i].get_value(value);
                A.init(name,value,first_letter);
                break;
            }
            case FLOAT:
            {
                float value;
                storage[i].get_value(value);
                A.init(name,value,first_letter);
                break;
            }
            case STRING:
            {
                std::string value;
                storage[i].get_value(value);
                A.init(name,value,first_letter);
                break;
            }
            default:
                throw "invalid type";
                break;
            }
            terms.push_back(A);
            return true;
        }
        
    }
    return false;
}
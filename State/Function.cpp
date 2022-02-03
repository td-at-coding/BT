#include "Function.h"
#include <iostream>
#include <sstream>
#include "var_type.h"
#include "Term.h"
#include "Expression.h"
#include "State.h"
#include "util.h"

std::vector<std::string> combine(const std::vector<std::string>& terms,const std::vector<std::string>& ops)
{
    std::vector<std::string> result;
    int j = 0;
    for (size_t i = 0; i < ops.size(); i++)
    {
        while(
            ops[i] == ";" 
            || ops[i] == "take" 
            || ops[i] == "return"
            || ops[i] == "()"
            || ops[i] == "("
            || ops[i] == ")"
        ) continue; 
        result.push_back(ops[i]);
        result.push_back(terms[j]);
        if (ops[i] == ")" || ops[i] == "(")
        {}
        else j++;
        
    }
    
    return result;
}

bool Function::init(std::string str)
{
    std::size_t operand1, operand2;
    // str = remove_space(str);
    std::vector<std::string> terms = split_any(str, " \t\v\r\n\f(),[];=+-*/{}", {"take","return"});
    std::vector<std::string> operations = split_by(str, "=+-*/,();",{"take","return"});
    // std::vector<std::string> result = combine(terms,operations);
    this->name = str.substr(0,str.find_first_of(" \t\n\r\f\v="));
    // std::cout << "str.find(\"return\")+6 : " << str.find("return")+6 << std::endl;
    // std::cout << "str.length()-1 : " << str.length()-1 << std::endl;
    this->return_expression = str.substr(str.find("return")+6);
    this->return_expression.erase(this->return_expression.find_first_of(";"));
    this->return_expression = this->return_expression.substr(this->return_expression.find_first_not_of(" \t\n\r\f\v"));
    // std::cout << "return_expression : " << return_expression<< std::endl;
    std::string first_st;
    std::stringstream unit(str);
    getline(unit, first_st,';');
    // TODO: get arguments
    operand1 = first_st.find_first_of("(");
    operand2 = first_st.find_first_of(')');
    std::string args = first_st.substr(operand1+1,operand2-operand1-1);
    if(args.length() != 0 )
    {
        // std::cout << "args : (" << args << ") "<< std::endl;
        std::string arg_segment;
        std::stringstream arg_stream(args);
        static int index;
        index = 0;
        while (getline(arg_stream, arg_segment,','))
        {
            arg_segment.erase(arg_segment.find_last_not_of(" \t\n\r\f\v")+1);
            arg_segment.erase(0,arg_segment.find_first_not_of(" \t\n\r\f\v"));
            // std::cout << "arg" << index++ << " (" << arg_segment <<") "<< std::endl;
            arguments.push_back(arg_segment);
        }
    }
    
    first_st = first_st.substr(first_st.find_first_of(")")+1);
    // std::cout << "first_st : " << first_st<< std::endl;
    if (first_st.find("return") != std::string::npos) return true;
    // TODO: get statements and continue
    first_st = first_st.substr(first_st.find_first_not_of(" \t\n\r\f\v"));
    // std::cout << "first_st : " << first_st << std::endl;
    std::string name, value;
    name = first_st.substr(0,first_st.find_first_of(" \t\n\r\f\v"));
    // std::cout << "name : (" << name << ")"<< std::endl;
    first_st = first_st.substr(first_st.find_first_of("=")+1);
    // std::cout << "first_st : " << first_st << std::endl;
    value = first_st.substr(first_st.find_first_not_of(" \t\n\r\f\v"));
    // std::cout << "value : (" << value << ")"<< std::endl;
    statements.push_back({name,value,INTEGER});
    while (getline(unit, first_st,';'))
    {
        if (first_st.find("return") != std::string::npos) return true;
        first_st = first_st.substr(first_st.find_first_not_of(" \t\n\r\f\v"));
        // std::cout << "first_st : " << first_st << std::endl;
        std::string name, value;
        name = first_st.substr(0,first_st.find_first_of(" \t\n\r\f\v"));
        // std::cout << "name : (" << name << ")"<< std::endl;
        first_st = first_st.substr(first_st.find_first_of("=")+1);
        // std::cout << "first_st : " << first_st << std::endl;
        value = first_st.substr(first_st.find_first_not_of(" \t\n\r\f\v"));
        // std::cout << "value : (" << value << ")"<< std::endl;
        statements.push_back({name,value,INTEGER});

    }
    
    return true;
}
bool Function::evaluate(std::vector<Data> args, const State& state, Term& value)
{
    if(args.size() != arguments.size()) return false;
    for (size_t i = 0; i < args.size(); i++)
    {
        arguments[i].set_value(args[i].get_value(), args[i].get_type());
    }
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_type() == EXPRESSION)
        {
            // TODO fill in variables from arguments
        }
    }
    std::string ret_expr = return_expression;
    if(ret_expr.find_first_of("+-*/") != std::string::npos){
        int total = 0;
        while(ret_expr.find_first_of("+-*/") != std::string::npos)
        {
            std::string new_value = ret_expr.substr(0, ret_expr.find_first_of(" \t\n\r\f\v+-*/"));
            // std::cout << "new value: (" << new_value << ") in? " << contains_name(new_value) << std::endl; 
            if(contains_name(new_value))
            {
                int name_value;
                get_value(new_value,name_value);
                // std::cout <<"new_value: ("<< new_value<< ") name_value: (" << name_value << ")" << std::endl;
                total+= name_value;
            }
            else
                total+= std::stoi(new_value);
            ret_expr = ret_expr.substr(ret_expr.find_first_of("+-*/")+1);
            ret_expr = ret_expr.substr(ret_expr.find_first_not_of(" \t\n\r\f\v"));
        }
        // std::cout << "ret_expr (" << ret_expr << ")" << std::endl;
        if(contains_name(ret_expr))
        {
            int name_value;
            get_value(ret_expr,name_value);
            // std::cout <<"new_value: ("<< ret_expr<< ") name_value: (" << name_value << ")" << std::endl;
            total+= name_value;
        }
        else
            total+= std::stoi(ret_expr);
        value.init("",total,0);

    } else if( return_expression == arguments[0].get_name() && arguments.size() == 1)
    {
        value.init("",arguments[0].get_value(),0);
    } else value.init("",return_expression,0);

    return true;
}

bool Function::evaluate(std::string& value)
{
    if(0 != arguments.size()) return false;
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_type() == EXPRESSION)
        {
            // TODO fill in variables from arguments
        }
    }
    std::vector<Term> terms = get_terms(return_expression);
    std::string ret_expr = return_expression;
    if(ret_expr.find_first_of("+-*/") != std::string::npos){
        int total = 0;
        while(ret_expr.find_first_of("+-*/") != std::string::npos)
        {
            std::string new_value = ret_expr.substr(0, ret_expr.find_first_of(" \t\n\r\f\v+-*/"));
            std::cout << "new value: (" << new_value << ") in? " << contains_name(new_value) << std::endl; 
            if(contains_name(new_value))
            {
                int name_value;
                get_value(new_value,name_value);
                std::cout <<"new_value: ("<< new_value<< ") name_value: (" << name_value << ")" << std::endl;
                total+= name_value;
            }
            else
                total+= std::stoi(new_value);
            ret_expr = ret_expr.substr(ret_expr.find_first_of("+-*/")+1);
            ret_expr = ret_expr.substr(ret_expr.find_first_not_of(" \t\n\r\f\v"));
        }
        std::cout << "ret_expr (" << ret_expr << ")" << std::endl;
        if(contains_name(ret_expr))
        {
            int name_value;
            get_value(ret_expr,name_value);
            std::cout <<"new_value: ("<< ret_expr<< ") name_value: (" << name_value << ")" << std::endl;
            total+= name_value;
        }
        else
            total+= std::stoi(ret_expr);
        value = std::to_string(total);
    } else value = return_expression;

    return true;
}


std::string Function::get_name() const
{
    return name;
}
size_t Function::get_length() const
{
    return arguments.size();
}
std::string Function::get_return_expression() const
{
    return return_expression;
}

bool Function::contains_name(std::string name) const
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if(arguments[i].get_name() == name) return true;
    }
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_name() == name) return true;
    }
    return false;
}


bool Function::get_value(const std::string name, std::string& value) const
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if(arguments[i].get_name() == name)
        {
            arguments[i].get_value(value);
            return true;
        }
        
    }
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_name() == name)
        {
            statements[i].get_value(value);
            return true;
        }
        
    }
    return false;
}
bool Function::get_value(const std::string name, float& value) const
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if(arguments[i].get_name() == name)
        {
            arguments[i].get_value(value);
            return true;
        }
        
    }
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_name() == name)
        {
            statements[i].get_value(value);
            return true;
        }
        
    }
    return false;
}

bool Function::get_value(const std::string name, int& value) const
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if(arguments[i].get_name() == name)
        {
            arguments[i].get_value(value);
            return true;
        }
        
    }
    for (size_t i = 0; i < statements.size(); i++)
    {
        if(statements[i].get_name() == name)
        {
            statements[i].get_value(value);
            return true;
        }
        
    }
    return false;
}
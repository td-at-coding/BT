#include "_Parser.h"
#include "var_type.h"
#include <sstream>
#include <iostream>


Parser::Parser()
{
    states.push_back({});
}

bool Parser::is_valid_object(const std::string& str)
{
    // return true;
    return str.find("=") != std::string::npos ;
}

bool Parser::is_valid_function(const std::string& str)
{
    return true;
}

bool Parser::insert(const std::string& str)
{
    std::string statement;
    std::string function_str = "";
    // if(!is_valid_state(str)) return false;
    std::stringstream unit(str);
    State& state = states[0];
    bool func_scope = false;
    while(getline(unit, statement,';'))
    {
        // statement = statement.substr(
        //     statement.find_first_not_of(" "), 
        //     statement.find_last_not_of(" ") 
        // );
        statement.erase(statement.find_last_not_of(" \t\n\r\f\v=") + 1);
        statement.erase(0, statement.find_first_not_of(" \t\n\r\f\v="));
        if(
            func_scope == false
            && (
                statement.find("return")!= std::string::npos 
                || statement.find("take")!= std::string::npos 
            )
        ) func_scope = true;
        if(func_scope)
        {
            function_str += statement + ';';
        }

        if(is_valid_object(statement) && !func_scope)
        {
            std::string name = statement.substr(0,statement.find_first_of(" \t\n\r\f\v="));
            std::string value = statement.substr(statement.find_first_of("=")+1);
            value = value.substr(statement.find_first_not_of(" \t\n\r\f\v=")+1);
            if(value.find_first_of("+-*/") != std::string::npos){
                int total = 0;
                while(value.find_first_of("+-*/") != std::string::npos)
                {
                    std::string new_value = value.substr(0, value.find_first_of(" \t\n\r\f\v+-*/"));
                    std::cout << "new value: " << new_value << std::endl; 
                    if(state.contains_name(new_value))
                    {
                        int name_value;
                        state.get_value(new_value,name_value);
                        total+= name_value;
                    }
                    else    
                        total+= std::stoi(new_value);
                    value = value.substr(value.find_first_of("+-*/")+1);
                    value = value.substr(value.find_first_not_of(" \t\n\r\f\v"));
                }
                if(state.contains_name(value))
                {
                    float name_value;
                    state.get_value(value,name_value);
                    total+= name_value;
                }
                else
                    total+= std::stoi(value);
                value = std::to_string(total);
            }
            std::cout << "object value: (" << value << ") " << std::endl;
            if(
                value.find_first_of(".") != std::string::npos
                && value.find_first_of("1234567890") != std::string::npos
                &&  value.find_first_not_of(".1234567890") == std::string::npos
            )
                state.insert_data(name, value, FLOAT);
            else if(
                value.find_first_of("1234567890") != std::string::npos
                &&  value.find_first_not_of("1234567890") == std::string::npos
            )
                state.insert_data(name, value, INTEGER);
            else if(
                value.find_first_of(")") != std::string::npos
                && value.find_first_of("(") != std::string::npos
            )
            {
                // TODO: implement other types
                std::size_t operand1 = value.find_first_of("("),
                operand2 = value.find_first_of(')');
                std::string func_name = value.substr(0,operand1);
                std::cout << "func_name: (" << func_name << ") " << std::endl;
                std::string args = value.substr(operand1+1,operand2-operand1-1);
                if(args.length() != 0 )
                {
                    std::cout << "args : (" << args << ") "<< std::endl;
                    std::string arg_segment;
                    std::stringstream arg_stream(args);
                    static int index;
                    index = 0;
                    std::vector<Data> arguments;
                    while (getline(arg_stream, arg_segment,','))
                    {
                        arg_segment.erase(arg_segment.find_last_not_of(" \t\n\r\f\v")+1);
                        arg_segment.erase(0,arg_segment.find_first_not_of(" \t\n\r\f\v"));
                        std::cout << "arg" << index++ << " (" << arg_segment <<") "<< std::endl;
                        arguments.push_back({"",arg_segment,INTEGER});
                    }
                    Function func;
                    state.get_function(func_name,func);
                    // func.evaluate(arguments,value);
                }
                state.insert_data(name, value, INTEGER);
            }
            else state.insert_data(name, value, EXPRESSION);
        }
        // else if  return false;
        if(
            func_scope
            && statement.find("return")!= std::string::npos
        ) {
            func_scope = false;
            if(is_valid_function(statement))
                state.insert_function(function_str);
            function_str = "";
        }

    }
    // states.push_back(state);
    return true;
}


bool Parser::is_valid_state(const std::string& str)
{
    return 
        str.find("return") == str.find("take")
        && str.find("=") + str.find("return") == str.find(";")
    ;
}

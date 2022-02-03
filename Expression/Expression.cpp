#include <bits/stdc++.h>
#include <iostream>
#include "Expression.h"
#include "oper_types.h"
#include "util.h"
#include "var_type.h"


const std::string delimiters = "=+-*/{} \t\v\r\n\f(),[];";

bool Expression::eval(std::string str, std::string& value)
{
    if(str.find_first_of("+-*/") != std::string::npos)
    {
        str = remove_space(str);
        std::vector<Term> term_counter = get_terms(str);
        std::vector<std::pair<int, oper_types>> sign_counter = get_signs(str);
        std::pair<std::vector<int>,std::vector<int>> scopes = get_scopes(str);
        std::vector<std::pair<int, oper_types>> oper_priority = get_priority(scopes,sign_counter);
        int sign_priority = get_sign_priority(oper_priority);
        for (int j = sign_priority; j > -1; j--)
        {
            int priority = j;
            for (int i = oper_priority.size()-1; i >= 0; i--)
            {
                switch (oper_priority[i].second)
                {
                case MULTI:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] *= term_counter[i+1];
                        term_counter.erase(term_counter.begin()+(i+1));
                        oper_priority.erase(oper_priority.begin()+i);
                    }
                    break;
                }
                case DIV:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] /= term_counter[i + 1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                    }
                    break;
                }
                
                default:
                    break;
                }
            }

            for (size_t i = oper_priority.size()-1; i < -1; i--)
            {
                switch (oper_priority[i].second)
                {
                case PLUS:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] += term_counter[i+1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                    }
                    break;
                }
                case MINUS:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] -= term_counter[i+1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                    }
                    break;
                }
                
                default:
                    break;
                }
            }

        }
        value = term_counter[0];
    }
    return true;
}

bool Expression::eval(std::string str, std::string& value, State& state)
{
    str = remove_space(str);
    if(str.find_first_of("+-*/=,()") != std::string::npos)
    {
        std::vector<Term> term_counter = get_terms(str,state);
        std::vector<std::pair<int, oper_types>> sign_counter = get_signs(str);
        std::pair<std::vector<int>,std::vector<int>> scopes = get_scopes(str);
        std::vector<std::pair<int, oper_types>> oper_priority = get_priority(scopes,sign_counter);
        int sign_priority = get_sign_priority(oper_priority);
        for (int j = sign_priority; j > -1; j--)
        {
            int priority = j;
            std::vector<Data> list;
            for (int i = oper_priority.size()-1; i >= 0; i--)
            {
                switch (oper_priority[i].second)
                {
                case MULTI:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] *= term_counter[i+1];
                        term_counter.erase(term_counter.begin()+(i+1));
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                case DIV:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] /= term_counter[i + 1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                
                default:
                    break;
                }
            }

            for (size_t i = oper_priority.size()-1; i < -1; i--)
            {
                switch (oper_priority[i].second)
                {
                case PLUS:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] += term_counter[i+1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                case MINUS:
                {
                    if(oper_priority[i].first == priority)
                    {
                        term_counter[i] -= term_counter[i+1];
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                
                default:
                    break;
                }
            }

            for (size_t i = oper_priority.size()-1; i < -1; i--)
            {
                switch (oper_priority[i].second)
                {
                case APOSTROPHE:
                {
                    if(oper_priority[i].first == priority)
                    {
                        // term_counter[i] += term_counter[i+1];
                        var_type t;
                        term_counter[i+1].get_type(t);
                        switch (t)
                        {
                        case INTEGER:
                        {
                            int value;
                            term_counter[i+1].get_value(value);
                            list.push_back({std::to_string(value),t});
                            break;
                        }
                        case FLOAT:
                        {
                            float value;
                            term_counter[i+1].get_value(value);
                            list.push_back({std::to_string(value),t});
                            break;
                        }
                        case STRING:
                        {
                            std::string value;
                            term_counter[i+1].get_value(value);
                            list.push_back({value,t});
                            break;
                        }
                        
                        default:
                            break;
                        }
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                case CALL:
                {
                    if(oper_priority[i].first == priority - 1)
                    {
                        // term_counter[i] += term_counter[i+1];
                        var_type t;
                        Function func;
                        term_counter[i+1].get_type(t);
                        switch (t)
                        {
                        case INTEGER:
                        {
                            int value;
                            term_counter[i+1].get_value(value);
                            list.push_back({std::to_string(value),t});
                            break;
                        }
                        case FLOAT:
                        {
                            float value;
                            term_counter[i+1].get_value(value);
                            list.push_back({std::to_string(value),t});
                            break;
                        }
                        case STRING:
                        {
                            std::string value;
                            term_counter[i+1].get_value(value);
                            list.push_back({value,t});
                            break;
                        }
                        
                        default:
                            break;
                        }
                        state.get_function(std::string(term_counter[i]),func);
                        func.evaluate(list,state,term_counter[i]);
                        list.clear();
                        term_counter.erase(term_counter.begin()+i+1);
                        oper_priority.erase(oper_priority.begin()+i);
                        break;
                    }
                }
                default:
                    break;
                }
            }

        }
        if(oper_priority[0].second == ASSIGNMENT)
        {
            var_type t1 = NONE, t2;
            term_counter[0].get_type(t1);
            if(term_counter[1].get_type(t2))
            {
                switch (t2)
                {
                case INTEGER:
                {
                    int value;
                    term_counter[1].get_value(value);
                    state.set_value(term_counter[0].get_actual_value(),std::to_string(value),INTEGER);
                    break;
                }
                case FLOAT:
                {
                    float value;
                    term_counter[1].get_value(value);
                    std::string new_value = std::to_string(value);
                    new_value.erase ( new_value.find_last_not_of('0') + 1, std::string::npos );
                    state.set_value(term_counter[0].get_actual_value(),new_value,FLOAT);
                    break;
                }
                case STRING:
                {
                    std::string value;
                    term_counter[1].get_value(value);
                    state.set_value(term_counter[0].get_actual_value(),value,STRING);
                    break;
                }
                
                default:
                    break;
                }
            }
                
        }
        
        value = term_counter[term_counter.size()-1];
    }
    else if (state.contains_name(str) )
    {
        var_type t;
        if(state.get_type(str,t))
        {
            switch (t)
            {
            case INTEGER:
            {
                int val;
                state.get_value(str,val);
                value = std::to_string(val);
                break;
            }
            case FLOAT:
            {
                float val;
                state.get_value(str,val);
                value = std::to_string(val);
                value.erase ( value.find_last_not_of('0') + 1, std::string::npos );
                break;
            }
            case STRING:
            {
                std::string val;
                state.get_value(str,val);
                value = val;
                break;
            }
            
            default:
                throw "bad data type";
                break;
            }
        }
    }
    return true;
}




bool Expression::different_priority() const
{
    // return different_priority;
    size_t size =parameters.size();
    if(size == 1) return false;
    int main_priority = parameters[0].get_priority();
    for (size_t i = 1; i < size; i++)
    {
        if(parameters[i].get_priority() != main_priority) return true;

    }
    return false;
}


std::vector<std::pair<int,oper_types>> get_priority(
    std::pair<std::vector<int>,std::vector<int>> scopes, 
    const std::vector<std::pair<int,oper_types>>& signs
)
{
    std::vector<std::pair<int,oper_types>> priority;
    for (size_t i = 0; i < signs.size(); i++)
    {
        const std::pair<int,oper_types>& sign = signs[i];
        int scope = 0;
        for (size_t j = 0; j < scopes.first.size(); j++)
        {
            // std::cout << "range " << scopes.first[j] << ", " << scopes.second[j] << " sign: "<<sign.first;
            if(scopes.first[j] < sign.first  && scopes.second[j] > sign.first )
            {
                scope++;
            }
        }
        // std::cout<< std::endl;
        priority.push_back(std::make_pair(scope,sign.second));
        
    }
    return priority;
    
}


bool Expression::get_by_id(int id, Operation& op)
{
    for (size_t i = 0; i < parameters.size(); i++)
    {
        if(id == parameters[i].get_id())
        {
            op = parameters[i];
            return true;
        }
        
    }
    
    return false;
}


std::pair<std::vector<int>,std::vector<int>> get_scopes(std::string str)
{
    std::pair<std::vector<int>,std::vector<int>> scopes;


    for (size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == '{' || str[i] == '('){
            scopes.first.push_back(i);
        }
    }

    for (size_t i = 0; i < str.size(); i++)
    {
        if(str[i] == '}' || str[i] == ')'){
            scopes.second.push_back(i);
        }
    }
    
    return scopes;

}

std::vector<Term> get_terms(std::string str)
{
    std::vector<Term> term_counter;
    // sequence of integers
    bool integer_pro = false;
    int first_integer, interpoint = 0;
    std::string word = "";
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool integer = is_digit(character) || character == '.';
        if(character == '.') interpoint++;
        if(interpoint > 1) throw "bad integer parsing";
        if(integer == true && integer_pro == false)
        {
            integer_pro = true;
            first_integer = i;
            word+= character;
        } else if (integer == false && integer_pro == true)
        {
            Term A;
            if(interpoint == 1)
                A.init(word,FLOAT,first_integer);
            else
                A.init(word,INTEGER,first_integer);
            term_counter.push_back(A);
            word = "";
            integer_pro = false;
            interpoint = 0;
        } else if (integer == true && integer_pro == true)
        {
            word+= character;
        }
    }
    if(word != "") 
    {
        Term A;
        if(interpoint == 1)
            A.init(word,FLOAT,first_integer);
        else
            A.init(word,INTEGER,first_integer);
        term_counter.push_back(A);
    }
    return term_counter;

}

std::vector<Term> get_terms(std::string str, State& state)
{
    std::vector<Term> collection;
    std::string term = "";
    bool term_on = false;
    // integer sequence
    bool integer_pro = false;
    // string sequence
    bool string_pro = false;
    int first_letter, interpoint = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool integer = is_digit(character) || character == '.';
        bool string = character == '\"';
        if(character == '.' && integer_pro==true) interpoint++;
        bool any = false;
        for (size_t j = 0; j < delimiters.size(); j++)
        {
            if(character == delimiters[j])
                any = true;
        }
        if(any == false && term_on == false)
        {
            term+= character;
            term_on = true;
            first_letter = i;
            if(integer == true) integer_pro = true;
            if(string == true) string_pro = true;
        } else if(any == false && term_on == true)
        {
            if(integer == false) integer_pro = false;
            term+= character;
        } else if(any == true && term_on == true)
        {
            if(integer_pro == true) 
            {
                Term A;
                if(interpoint == 1)
                    A.init(term,FLOAT,first_letter);
                else
                    A.init(term,INTEGER,first_letter);
                collection.push_back(A);
                integer_pro = false;
            } else if(state.load_value(collection,term,first_letter))
            {
            } else if(state.contains_function(term))
            {
                Term A;
                Function func;
                state.get_function(term,func);
                if(func.get_length() == 0)
                {
                    std::string value;
                    func.evaluate(value);
                    A.init(value,INTEGER,first_letter);
                    collection.push_back(A);
                } else 
                {
                    A.init(term,FUNCTION,first_letter);
                    collection.push_back(A);
                }
            } else if(string_pro == true )
            {
                Term A;
                A.init(term,STRING,first_letter);
                collection.push_back(A);
                string_pro = false;
            } else if(collection.size()== 0)
            {
                state.insert_name(term);
                Term A;
                A.init(term,NONE,first_letter);
                collection.push_back(A);
            } else throw "bad parsing";
            term = "";
            term_on = false;
        }
    }
    if(term_on == true)
    {
        if(integer_pro == true) 
        {
            Term A;
            if(interpoint == 1)
                A.init(term,FLOAT,first_letter);
            else
                A.init(term,INTEGER,first_letter);
            collection.push_back(A);
        }else if(state.load_value(collection,term,first_letter))
        {
        } else if(state.contains_function(term))
        {
            Term A;
            Function func;
            state.get_function(term,func);
            if(func.get_length() == 0)
            {
                std::string value;
                func.evaluate(value);
                A.init(value,INTEGER,first_letter);
                collection.push_back(A);
            }
        } else if(string_pro == true )
        {
            Term A;
            A.init(term,STRING,first_letter);
            collection.push_back(A);
        }  else throw "bad parsing";
    } 

    return collection;
}


std::vector<std::pair<int,oper_types>> get_signs(std::string str)
{
    std::vector<std::pair<int,oper_types>> sign_counter;
    for (size_t i = 0; i < str.size(); i++)
    {
        switch(str[i])
        {
        case '+':
        {
            sign_counter.push_back(std::make_pair(i,PLUS));
            break;
        }
        case '-':
        {
            sign_counter.push_back(std::make_pair(i,MINUS));
            break;
        }
        case '*':
        {
            sign_counter.push_back(std::make_pair(i,MULTI));
            break;
        }
        case '/':
        {
            sign_counter.push_back(std::make_pair(i,DIV));
            break;
        }
        case '=':
        {
            sign_counter.push_back(std::make_pair(i,ASSIGNMENT));
            break;
        }
        case ',':
        {
            sign_counter.push_back(std::make_pair(i,APOSTROPHE));
            break;
        }
        case '(':
        {
            sign_counter.push_back(std::make_pair(i,CALL));
            break;
        }
        }
    }
    return sign_counter;
}

int get_sign_priority(const std::vector<std::pair<int,oper_types>>& signs)
{
    // std::vector<int> sign_priority;
    int highest = 0;
    // sign_priority.
    for (size_t i = 0; i < signs.size(); i++)
    {
        // if(std::find(sign_priority.begin(), sign_priority.end(), signs[i].first) ==sign_priority.end())
        //     sign_priority.push_back(signs[i].first);
        if(signs[i].first > highest)  highest = signs[i].first;
    }
    return highest;
}






std::ostream& operator << (std::ostream& out,oper_types sign)
{
    switch (sign)
    {
    case PLUS:
        out << "PLUS";
        break;
    case MINUS:
        out << "MINUS";
        break;
    case MULTI:
        out << "MULTI";
        break;
    case DIV:
        out << "DIV";
        break;
    
    default:
        break;
    }
    return out;
}
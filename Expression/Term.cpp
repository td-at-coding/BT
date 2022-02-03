#include "Term.h"
#include "var_type.h"



Term::Term()
    : type(NONE), value(""),  position(-1)
{}

bool Term::negate()
{
    switch (this->type)
    {
    case NONE:
        throw "error";
        break;
    case STRING:
        throw "invalid operation";
        break;
    case INTEGER:
    {
        int value = - stoi(this->value);
        this->value = std::to_string(value);
        break;
    }
    case FLOAT:
    {
        float value = - stof(this->value);
        this->value = std::to_string(value);
        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
        break;
    }
    default:
        break;
    }
    return true;
}
bool Term::is_positive() const
{
    bool sign;
    switch (this->type)
    {
    case NONE:
        throw "error";
        break;
    case STRING:
        throw "invalid operation";
        break;
    case INTEGER:
    {
        sign = std::stoi(this->value) >= 0;
        break;
    }
    case FLOAT:
    {
        sign = std::stof(this->value) >= 0;
        break;
    }
    default:
        break;
    }
    return sign;
}

Term::operator const char*()
{
    return value.c_str();
}

Term & Term::operator=(Term && term)
{
    this->position = term.position;
    this->value = term.value;
    this->actual_value = term.actual_value;
    this->type = term.type;
    return *this;
}

// Term& Term::operator=(const Term & term)
// {
//     this->position = term.position;
//     this->value = term.value;
//     // this->actual_value = term.actual_value;
//     this->type = term.type;
//     return *this;
// }


Term::Term(const Term & term)
{
    this->position = term.position;
    this->value = term.value;
    this->actual_value = term.actual_value;
    this->type = term.type;
}


bool Term::init(const std::string value, const var_type type, const int position)
{
    this->value = value;
    this->type = type;
    this->position = position;
    return true;
}

bool Term::init(const int value, const int position)
{
    this->value = std::to_string(value);
    this->type = INTEGER;
    this->position = position;
    return true;
}
bool Term::init(const float value, const int position)
{
    this->value = std::to_string(value);
    this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
    this->type = FLOAT;
    this->position = position;
    return true;
}
bool Term::init(const std::string value, const int position)
{
    this->value = value;
    this->type = STRING;
    this->position = position;
    return true;
}


bool Term::init(const std::string actual_value, const int value, const int position)
{
    this->value = std::to_string(value);
    this->actual_value = actual_value;
    this->type = INTEGER;
    this->position = position;
    return true;
}
bool Term::init(const std::string actual_value, const float value, const int position)
{
    this->value = std::to_string(value);
    this->actual_value = actual_value;
    this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
    this->type = FLOAT;
    this->position = position;
    return true;
}
bool Term::init(const std::string actual_value, const std::string value, const int position)
{
    this->value = value;
    this->actual_value = actual_value;
    this->type = STRING;
    this->position = position;
    return true;
}






bool Term::get_position(int& position) const
{
    if(this->position == -1) return false;
    else
    {
        position = this->position;
        return true;
    }
}
bool Term::get_value(int& value) const
{
    if(this->value == "") return false;
    else
    {
        if(type == INTEGER)
        {
            value = std::stoi(this->value);
            return true;
        } else return false;
    }
}
bool Term::get_value(float& value) const
{
    if(this->value == "") return false;
    else
    {
        if(type == FLOAT)
        {
            value = std::stof(this->value);
            return true;
        } else return false;
    }
}
bool Term::get_value(std::string& value) const
{
    if(this->value == "") return false;
    else
    {
        if(type == STRING)
        {
            value = this->value;
            return true;
        } else return false;
    }
}
bool Term::get_type(var_type& type) const
{
    if(this->type == NONE) return false;
    else
    {
        type = this->type;
        return true;
    }
}


Term operator+(const Term& A, const Term& B)
{
    var_type A_type,B_type;
    Term result;
    if(A.get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING && (B_type == INTEGER || B_type == FLOAT)) throw "invalid operation";
        if(B_type == STRING && (A_type == INTEGER || A_type == FLOAT)) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value+B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value+B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value+B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value+B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case STRING:
        {
            if(B_type == STRING)
            {
                std::string A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value+B_value,position);
                    else throw "invalid position";
                }  else throw "invalid value";
            } 
            break;
        }

        }
    }
    else throw "bad value";
    return result;
}
Term operator-(const Term& A, const Term& B)
{
    var_type A_type,B_type;
    Term result;
    if(A.get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value-B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value-B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value-B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value-B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }
    }
    else throw "bad value";
    return result;
}
Term operator*(const Term& A, const Term& B)
{
    var_type A_type,B_type;
    Term result;
    if(A.get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value*B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value*B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value*B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value*B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }
    }
    else throw "bad value";
    return result;
}
Term operator/(const Term& A, const Term& B)
{
    var_type A_type, B_type;
    Term result;
    if(A.get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value/B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value/B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value/B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(A.get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(A.get_position(position))
                        result.init(A_value/B_value,position);
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }
    }
    else throw "bad value";
    return result;
}


Term& Term::operator+=(const Term& B)
{
    var_type A_type,B_type;
    if(get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING && (B_type == INTEGER || B_type == FLOAT)) throw "invalid operation";
        if(B_type == STRING && (A_type == INTEGER || A_type == FLOAT)) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                        this->value = std::to_string(A_value+B_value);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value+B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value+B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value+B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case STRING:
        {
            if(B_type == STRING)
            {
                std::string A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    A_value.erase(A_value.size()-1);
                    B_value.erase(0,1);
                    if(get_position(position))
                        this->value = A_value+B_value;
                    else throw "invalid position";
                } else throw "invalid value";
            } 
            break;
        }

        }
    }
    else throw "bad value";
    return *this;
}
Term& Term::operator-=(const Term& B)
{
    var_type A_type,B_type;
    if(get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                        this->value = std::to_string(A_value-B_value);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value-B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value-B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value-B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }

    } else throw "bad value";
    return *this;
}
Term& Term::operator*=(const Term& B)
{
    var_type A_type, B_type;
    // throw type;
    if(get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                        this->value = std::to_string(A_value*B_value);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value*B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value*B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value*B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }

    } else throw "bad value";
    return *this;
}
Term& Term::operator/=(const Term& B)
{
    var_type A_type,B_type;
    if(get_type(A_type) && B.get_type(B_type))
    {
        if(A_type == STRING || B_type == STRING) throw "invalid operation";
        switch(A_type)
        {
        case INTEGER:
        {
            if(B_type == INTEGER)
            {
                int A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                        this->value = std::to_string(A_value/B_value);
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                int A_value; float B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value/B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
            break;
        }
        case FLOAT:
        {
            if(B_type == FLOAT)
            {
                float A_value, B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value/B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            } else
            {
                float A_value; int B_value;
                if(get_value(A_value) && B.get_value(B_value))
                {
                    int position;
                    if(get_position(position))
                    {
                        this->value = std::to_string(A_value/B_value);
                        this->value.erase ( this->value.find_last_not_of('0') + 1, std::string::npos );
                    }
                    else throw "invalid position";
                } else throw "invalid value";
            }
        }
        }

    } else throw "bad value";
    return *this;
}

std::string Term::get_actual_value() const
{
    if(actual_value != "")
        return actual_value;
    else
        return value;
}
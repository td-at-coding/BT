#include "Data.h"
#include "var_type.h"
#include <iostream>


Data::Data(
    std::string value,
    var_type type
): name(""), value(value), type(type)
{}

Data::Data(
    std::string name,
    std::string value,
    var_type type
) : name(name), value(value), type(type)
{}
Data::Data(
    std::string name
) : name(name), type(NONE), value("")
{}
var_type Data::get_type() const
{
    return type;
}
std::string Data::get_name() const
{
    return name;
}
std::string Data::get_value() const
{
    return value;
}

bool Data::get_value(std::string& value) const
{
    if (type == STRING)
    {
        value = this->value;
        return true;
    } else return false;
    
}
bool Data::get_value(int& value) const
{
    if (type == INTEGER)
    {
        value = std::stof(this->value);
        return true;
    } else return false;
}
bool Data::get_value(float& value) const
{
    if (type == FLOAT)
    {
        value = std::stof(this->value);
        return true;
    } else return false;
}
bool Data::set_value(const std::string& value)
{
    if (type == STRING)
    {
        this->value = value;
        return true;
    } else return false;
}
bool Data::set_value(const float& value)
{
    if (type == FLOAT)
    {
        this->value = std::to_string(value);
        return true;
    } else return false;
}
bool Data::set_value(const int& value)
{
    if (type == INTEGER)
    {
        this->value = std::to_string(value);
        return true;
    } else return false;
}

bool Data::set_name(const std::string& name)
{
    if( name.find_first_of (
        " <>/?,.;:'\"][{}\\|/*-+`~()!@#$%^&*="
    ) == std::string::npos )
    {
        this->name = name;
        return true;
    } else return false;
}

void Data::set_type(const var_type type)
{
    if(type != this->type)
    {
        this->value = ""; 
        this->type = type;
    }
}

bool Data::set_value(const std::string& value, var_type type)
{
    this->value = value;
    this->type = type;
    return true;
}
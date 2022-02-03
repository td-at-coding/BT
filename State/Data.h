#pragma once
#include <string>

enum var_type : int;


class Data
{
private:
    var_type type;
    std::string name;
    std::string value;
public:
    Data(
        std::string name,
        std::string value,
        var_type type
    );
    Data(
        std::string value,
        var_type type
    );
    Data(
        std::string name
    );
    var_type get_type() const;
    std::string get_name() const;
    std::string get_value() const;
    bool get_value(std::string& value) const;
    bool get_value(float& value) const;
    bool get_value(int& value) const;
    bool set_value(const std::string& value);
    bool set_value(const std::string& value, var_type type);
    bool set_value(const float& value);
    bool set_value(const int& value);
    bool set_name(const std::string& name);
    void set_type(const var_type type);

};


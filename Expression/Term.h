#pragma once
#include <string>


enum var_type : int;

class Term
{
public:
    Term();
    Term(const Term & term);
    bool init(const std::string value, const var_type type, const int position);
    bool init(const int value, const int position);
    bool init(const float value, const int position);
    bool init(const std::string value, const int position);
    bool init(const std::string actual_value,const int value, const int position);
    bool init(const std::string actual_value,const float value, const int position);
    bool init(const std::string actual_value,const std::string value, const int position);
    bool get_position(int& position) const;
    std::string get_actual_value() const;
    bool get_value(int& value) const; 
    bool get_value(float& value) const;
    bool get_value(std::string& value) const;
    bool get_type(var_type& type) const;
    bool is_positive() const;
    bool negate();
    operator const char*();
    Term& operator=(Term && term);
    // Term& operator=(const Term & term);
    Term& operator+=(const Term& B);
    Term& operator-=(const Term& B);
    Term& operator*=(const Term& B);
    Term& operator/=(const Term& B);
private:
    int position;
    std::string value;
    std::string actual_value;
    var_type type;

};

Term operator+(const Term& A, const Term& B);
Term operator-(const Term& A, const Term& B);
Term operator*(const Term& A, const Term& B);
Term operator/(const Term& A, const Term& B);
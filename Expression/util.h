#pragma once
#include <string>
#include <vector>

bool is_digit(char x);
bool is_sign(char x);
bool is_sign(std::string x);
bool is_space(char x);
bool is_name(char x);
bool is_letter(char x);

std::string remove_space(std::string str);

std::vector<std::string> split_any(const std::string& str, const std::string delimiter);
std::vector<std::string> split_any(const std::string& str, const std::string delimiter, std::vector<std::string> delimiters);
std::vector<std::string> split_by(const std::string& str, const std::string delimiter);
std::vector<std::string> split_by(const std::string& str, const std::string delimiter, std::vector<std::string> delimiters);


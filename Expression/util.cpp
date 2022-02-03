#include "util.h"

bool is_digit(char x)
{
    return  
           x == '1' 
        || x == '2' 
        || x == '3' 
        || x == '4' 
        || x == '5' 
        || x == '6'
        || x == '7'
        || x == '8'
        || x == '9'
        || x == '0'
    ;
}

bool is_sign(char x)
{
    return  
           x == '+' 
        || x == '-' 
        || x == '*' 
        || x == '/'
    ;
}

bool is_sign(std::string x)
{
    if(x.size() > 1) return false;
    char letter = x[0];
    return is_sign(letter);
}

bool is_name(char x)
{
    return  
           (x >= 'a'
        && x <= 'z')
        || (x >= 'A'
        && x <= 'Z')
        || x == '$'
        || is_digit(x)
    ;

}

bool is_letter(char x)
{
    return  
           (x >= 'a'
        && x <= 'z')
        || (x >= 'A'
        && x <= 'Z')
        || x == '$'
        || x == '_'
    ;
}

// ( \t\n\r\f\v{})
bool is_space(char x)
{
    return  
           x == ' ' 
        || x == '\t' 
        || x == '\n' 
        || x == '\r' 
        || x == '\f' 
        || x == '\v'
    ;
}

std::string remove_space(std::string str)
{
    std::string copy = "";
    bool in_quotes = false;


    for (size_t i = 0; i < str.size(); i++)
    {
        const char& character = str[i];
        if(character == '\"' && in_quotes == true) in_quotes = false;
        else if(character == '\"') in_quotes = true;
        if(is_space(character) == false || in_quotes == true)
        {
            copy += character;
        }
    }
    return copy;
    
}

std::vector<std::string> split_any(const std::string& str, const std::string delimiter)
{
    std::vector<std::string> collection;
    std::string term = "";
    bool term_on = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool any = false;
        for (size_t j = 0; j < delimiter.size(); j++)
        {
            if(character == delimiter[j])
                any = true;
        }
        if(any == false && term_on == false)
        {
            term+= character;
            term_on = true;
        } else if(any == true && term_on == true)
        {
            collection.push_back(term);
            term = "";
            term_on = false;
        } else if(any == false && term_on == true)
        {
            term+= character;
        }
    }
    if(term_on == true) collection.push_back(term);

    return collection;
    
}

std::vector<std::string> split_any(const std::string& str, const std::string delimiter, std::vector<std::string> delimiters)
{
    std::vector<std::string> collection;
    std::string term = "";
    bool term_on = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool any = false;
        for (size_t j = 0; j < delimiter.size(); j++)
        {
            if(character == delimiter[j])
                any = true;
        }
        if(any == false && term_on == false)
        {
            term+= character;
            term_on = true;
        } else if(any == true && term_on == true)
        {
            bool match = false;
            for (size_t i = 0; i < delimiters.size(); i++)
            {
                if(delimiters[i] == term)
                    match = true;
            }
            if( match == false)
                collection.push_back(term);
            term = "";
            term_on = false;
        } else if(any == false && term_on == true)
        {
            term+= character;
        }
    }
    if(term_on == true) collection.push_back(term);

    return collection;
    
}

std::vector<std::string> split_by(const std::string& str, const std::string delimiter)
{
    std::vector<std::string> collection;
    std::string term = "";
    bool term_on = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool any = false;
        for (size_t j = 0; j < delimiter.size(); j++)
        {
            if(character == delimiter[j])
                any = true;
        }
        if(any == true && term_on == false)
        {
            term+= character;
            term_on = true;
        } else if(any == true && term_on == true)
        {
            term+= character;
        } else if(any == false && term_on == true)
        {
            collection.push_back(term);
            term = "";
            term_on = false;
        }
    }
    if(term != "") collection.push_back(term);

    return collection;
    
}

std::vector<std::string> split_by(const std::string& str, const std::string delimiter, std::vector<std::string> delimiters)
{
    std::vector<std::string> collection;
    std::vector<std::string> keywords;
    std::vector<int> counters;
    for (size_t i = 0; i < delimiters.size(); i++)
    {
        counters.push_back(0);
        keywords.push_back("");
    }
    
    std::string term = "";

    bool term_on = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        char character = str[i];
        bool any = false;
        for (size_t j = 0; j < delimiter.size(); j++)
        {
            if(character == delimiter[j])
                any = true;
        }

        for (size_t i = 0; i < counters.size(); i++)
        {
            int& count = counters[i];
            std::string& keyword = keywords[i];
            if(character == delimiters[i][count])
            {
                count++;
                keyword+= character;
                if(count == delimiters[i].size())
                {
                    collection.push_back(keyword);
                    count = 0;
                    keyword = "";
                } 
            } else
            {
                count = 0;
                keyword = "";
            }
        }
        if(any == true && term_on == false)
        {
            term+= character;
            term_on = true;
        } else if(any == true && term_on == true)
        {
            term+= character;
        } else if(any == false && term_on == true)
        {
            collection.push_back(term);
            term = "";
            term_on = false;
        }
    }
    if(term != "") collection.push_back(term);

    return collection;
    
}
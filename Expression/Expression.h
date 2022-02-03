#include "Operation.h"
#include <utility>
#include "Term.h"
#include "State.h"

class Expression
{
public:
    bool eval(std::string str, std::string& value);
    bool eval(std::string str, std::string& value, State& state);
    bool different_priority() const;
    bool get_by_id(int id, Operation& op);
private:
    std::vector<Operation> parameters;
};

std::pair<std::vector<int>,std::vector<int>> get_scopes(std::string str);

std::vector<Term> get_terms(std::string str);

std::vector<Term> get_terms(std::string str, State& state);

std::vector<Term> get_terms(std::string str, const State& state, std::vector<Data>& arguments, std::vector<Data>& statements);

std::vector<std::pair<int,oper_types>> get_signs(std::string str);

std::ostream& operator << (std::ostream&,oper_types);


std::vector<std::pair<int,oper_types>> get_priority(
    std::pair<std::vector<int>,std::vector<int>> scopes, 
    const std::vector<std::pair<int,oper_types>>& signs
);


int get_sign_priority(const std::vector<std::pair<int,oper_types>>& signs);
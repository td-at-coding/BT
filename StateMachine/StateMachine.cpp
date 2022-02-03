#include "StateMachine.h"
#include <vector>
#include <functional>

struct StateMachine
{
    std::vector<std::reference_wrapper<Node>> nodes;
};

StateMachine& create_statemachine()
{
    StateMachine* statemachine = new StateMachine;
    return *statemachine;
}


void delete_statemachine(StateMachine& statemachine)
{
    delete &statemachine;
}

unsigned get_size(const StateMachine& statemachine)
{
    return statemachine.nodes.size();
}

bool insert(StateMachine& statemachine, int begin, int end)
{
    statemachine.nodes.push_back(create_node(begin,end));
    return true;
}
bool insert(StateMachine& statemachine, Node& node)
{
    statemachine.nodes.push_back(node);
    return true;
}

StateMachine& get_begin(StateMachine& statemachine, int begin)
{
    StateMachine* new_statemachine = new StateMachine;
    for (size_t i = 0; i < statemachine.nodes.size(); i++)
    {
        if(get_begin(statemachine.nodes[i]) == begin)
            new_statemachine->nodes.push_back(statemachine.nodes[i]);
    }
    return *new_statemachine;
    
}
StateMachine& get_end(StateMachine& statemachine, int end)
{
    StateMachine* new_statemachine = new StateMachine;
    for (size_t i = 0; i < statemachine.nodes.size(); i++)
    {
        if(get_end(statemachine.nodes[i]) == end)
            new_statemachine->nodes.push_back(statemachine.nodes[i]);
    }
    return *new_statemachine;
}

Node& get_node(StateMachine& statemachine, int index)
{
    return statemachine.nodes[index];
}

std::ostream& operator<<(std::ostream& out, StateMachine& statemachine)
{
    out << "digraph {" << std::endl;
    for (size_t i = 0; i < statemachine.nodes.size(); i++)
        out << "\t" << statemachine.nodes[i] << std::endl;
    out << "}";
    return out;
}
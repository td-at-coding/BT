#include "Node.h"

struct StateMachine;

StateMachine& create_statemachine();
void delete_statemachine(StateMachine& statemachine);

unsigned get_size(const StateMachine& statemachine);

// inserts 
bool insert(StateMachine& statemachine, int begin, int end);
bool insert(StateMachine& statemachine, Node& node);

StateMachine& get_begin(StateMachine& statemachine, int begin);
StateMachine& get_end(StateMachine& statemachine, int end);

Node& get_node(StateMachine& statemachine, int index);


std::ostream& operator<<(std::ostream& out, StateMachine& statemachine);
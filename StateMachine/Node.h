#include <ostream>

struct Node;

Node& create_node( int begin, int end);
void delete_node(Node& node);
int get_begin(Node& node);
int get_end(Node& node);

std::ostream& operator << (std::ostream& out, const Node& node);
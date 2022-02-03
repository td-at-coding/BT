#include "Node.h"

struct Node
{
    int begin;
    int end;
};

Node& create_node( int begin, int end)
{
    Node* node = new Node{begin,end};
    return *node;
}
void delete_node(Node& node)
{
    delete &node;
}


int get_begin(Node& node)
{
    return node.begin;
}
int get_end(Node& node)
{
    return node.end;
}

std::ostream& operator << (std::ostream& out, const Node& node)
{
    out << node.begin << "->" << node.end;
    return out;
}

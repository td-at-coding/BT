#include "Tree.h"
#include "cstate_impl.h"


struct Leaf
{
    std::string value;
    cstate::cstate type;
    size_t scope;
};

struct Tree
{
    std::vector<Leaf> list;
};

bool push(Tree& tree, std::string value, cstate::cstate type, size_t scope)
{
    tree.list.push_back({value,type,scope});
    return true;
}

bool set(Leaf& leaf, std::string value, cstate::cstate type, size_t scope)
{
    leaf.value = value;
    leaf.type = type;
    leaf.scope = scope;
    return true;
}

std::string get_value(Leaf& leaf)
{
    return leaf.value;
}
cstate::cstate get_type(Leaf& leaf)
{
    return leaf.type;
}
size_t get_scope(Leaf& leaf)
{
    return leaf.scope;
}

Tree& get_scope(Tree& tree, size_t scope)
{
    Tree * new_tree_ptr = new Tree;
    Tree & new_tree = *new_tree_ptr;
    for (size_t i = tree.list.size()-1; i >= 0; i++)
    {
        if(tree.list[i].scope == scope)
            new_tree.list.push_back(tree.list[i]);
    }
    return new_tree;
}

Tree& create_tree()
{
    Tree* new_tree_ptr = new Tree;
    return * new_tree_ptr;
}

Leaf& create_leaf()
{
    Leaf* new_leaf_ptr = new Leaf;
    return * new_leaf_ptr;
}



void clear(Tree& tree)
{
    tree.list.clear();
}

size_t get_size(Tree& tree)
{
    return tree.list.size();
}

Leaf& get_element(Tree& tree, int index)
{
    return tree.list[index];
}


void delete_tree(Tree& tree)
{
    delete &tree;
}

void delete_leaf(Leaf& leaf)
{
    delete &leaf;
}




bool add(Leaf& lleaf, Leaf& rleaf)
{
    switch (lleaf.type)
    {
    case cstate::INTEGER:
    {
        switch (rleaf.type)
        {
        case cstate::INTEGER:
        {
            int value1 = std::stoi(lleaf.value),
                value2 = std::stoi(rleaf.value);
            lleaf.value= std::to_string(value1+value2);
            
            break;
        }
        case cstate::FLOAT:
        {
            int value1 = std::stoi(lleaf.value);
            float value2 = std::stof(rleaf.value);
            lleaf.value= std::to_string(value1+value2);
            lleaf.type = cstate::FLOAT;
            break;
        }
        
        default:
            break;
        }
        break;
    }
    case cstate::FLOAT:
    {
        switch (rleaf.type)
        {
        case cstate::INTEGER:
        {
            float value1 = std::stof(lleaf.value);
            int value2 = std::stoi(rleaf.value);
            lleaf.value= std::to_string(value1+value2);
            
            break;
        }
        case cstate::FLOAT:
        {
            float value1 = std::stof(lleaf.value); 
            float value2 = std::stof(rleaf.value);
            lleaf.value= std::to_string(value1+value2);
            
            break;
        }
        
        default:
            break;
        }
        break;
    }
    
    default:
        break;
    }
    
    return true;
}





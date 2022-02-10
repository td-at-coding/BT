#pragma once
#include <string>
#include "cstate.h"
#include <vector>
struct Tree;
struct Leaf;

bool push(Tree& tree, std::string value, cstate::cstate type, size_t scope);

bool set(Leaf& leaf, std::string value, cstate::cstate type, size_t scope);


std::string get_value(Leaf& leaf);
cstate::cstate get_type(Leaf& leaf);
size_t get_scope(Leaf& leaf);

Tree& get_scope(Tree& tree, size_t scope);

Tree& create_tree();
Leaf& create_leaf();


void clear(Tree& tree);

size_t get_size(Tree& tree);

Leaf& get_element(Tree& tree, int index);

void delete_tree(Tree& tree);

void delete_leaf(Leaf& leaf);

bool add(Leaf& lleaf, Leaf& rleaf);

bool sub(Leaf& lleaf, Leaf& rleaf);

bool mul(Leaf& lleaf, Leaf& rleaf);

bool div(Leaf& lleaf, Leaf& rleaf);

bool negate(Leaf& leaf);

bool inc(Leaf& leaf);

bool dec(Leaf& leaf);

bool set_equal(Leaf& lleaf, Leaf& rleaf);

bool move(Leaf& lleaf, Leaf& rleaf);
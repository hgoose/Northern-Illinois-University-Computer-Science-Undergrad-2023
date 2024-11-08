#ifndef NIU_CSCI340_XML_TESTING_H
#define NIU_CSCI340_XML_TESTING_H

#include "nodes.h"
#include "bintree.h"
#include <iostream>
#include <string>

template <int unused=0> // templated to prevent compiler from complaining it's in a header
void print_example_tree(std::ostream &ost=std::cout) {
  ost << "             Non-Binary Tree           Binary Version   \n";
  ost << "\n";
  ost << "        .--------.--[a]--.------.           [a]         \n";
  ost << "        |        |       |      |          /            \n";
  ost << "  .----[b]----. [c]     [d]    [e]      [b]             \n";
  ost << "  |     |     |                        /   \\            \n";
  ost << " [f] .-[g]-. [h]                    [f]     [c]         \n";
  ost << "     |     |                           \\       \\        \n";
  ost << "    [i]   [j]                           [g]     [d]     \n";
  ost << "                                       /   \\       \\    \n";
  ost << "                                    [i]     [h]     [e] \n";
  ost << "                                       \\                \n";
  ost << "                                        [j]             \n";
  ost << "\n";
}

// constructs the tree found in the readme
template <int unused=0> // templated to prevent compiler from complaining it's in a header
NodeLRP <std::string> * build_example_tree() {
  typedef NodeLRP <std::string> NODE;

  NODE * a = new NODE("a");
  NODE * b = new NODE("b");
  NODE * c = new NODE("c");
  NODE * d = new NODE("d");
  NODE * e = new NODE("e");
  NODE * f = new NODE("f");
  NODE * g = new NODE("g");
  NODE * h = new NODE("h");
  NODE * i = new NODE("i");
  NODE * j = new NODE("j");

  a->left = b;
  b->parent = a;

  b->left = f;
  f->parent = b;
  b->right = c;
  c->parent = b;

  f->right= g;
  g->parent = f;
 
  g->left = i;
  i->parent = g;
  g->right = h;
  h->parent = g;

  i->right = j;
  j->parent = i;

  c->right = d;
  d->parent = c;

  d->right = e;
  e->parent = d;

  return a;
}

#endif


/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include "testing.h"
#include <algorithm>
  
auto print = [](auto x){ std::cout << x->data << " "; };

// Test the tilted_find_parent function and compare result to expected value
template <typename NODE>
void test_find_parent(NODE * x, std::string expect_p, std::string expect_tp) {
  if(x == nullptr) return; // do nothing if invalid pointer

  auto p  = x->parent;
  auto tp = tilted_find_parent(x);
 
  std::cout << "  Node=\"" << x->data << "\", normal parent=\"" << 
    (p != nullptr ? p->data : "nullptr") << "\" (" << expect_p << "), tilted parent=\"" <<
    (tp != nullptr ? tp->data : "nullptr") << "\" (" << expect_tp << ")";

  if(tp && tp->data == expect_tp) {
    std::cout << " GOOD\n";
  }
  else if(!tp && expect_tp == "nullptr") {
    std::cout << " GOOD\n";
  }
  else {
    std::cout << " WRONG\n";
  }
}

// test tilted_get_children for the given node, comparing results to expected
template <typename NODE>
void test_get_children(NODE *node, const std::vector<NODE*> &expected) {
  auto result = tilted_get_children(node);

  std::cout << "  Children of node \"" << node->data << "\"; expect: { ";
  std::for_each(expected.begin(), expected.end(), print);
  std::cout << "}\n";
  std::cout << "                           got: { ";
  //std::cout << "      got:    { ";
  std::for_each(result.begin(), result.end(), print);
  std::cout << "}"; 

  if(result == expected) {
    std::cout << " GOOD\n"; }
  else {
    std::cout << " WRONG\n"; }

  std::cout << "\n";

}

int main() {
  std::cout << "********************************************************************************\n";
  std::cout << "* test1 - Test your algorithms on a known tree\n";
  std::cout << "*\n";
  std::cout << "*   If your traversals work, they should generate the same output you see in\n";
  std::cout << "* the \"expect\" lines. \n";
  std::cout << "*\n";
  std::cout << "*   If delete_tree works, then there should be nothing left allocated on the\n";
  std::cout << "* heap at the end of your program. This will be checked with a tool called\n";
  std::cout << "* valgrind, which you can run with: \n";
  std::cout << "*    valgrind ./test1\n";
  std::cout << "********************************************************************************\n";

  std::cout << "\n";
  std::cout << "********************************************************************************\n";
  std::cout << "* PRICELESS ASCII ART\n";
  std::cout << "********************************************************************************\n";

  print_example_tree<0>();

  auto tree = build_example_tree();

  std::cout << "********************************************************************************\n";
  std::cout << "* TESTING YOUR TRAVERSAL ALGORITHMS\n";
  std::cout << "********************************************************************************\n";
  std::cout << "         preorder: "; preorder(tree, print);
  std::cout << "\n";
  std::cout << "           expect: a b f g i j h c d e\n\n";

  std::cout << "          inorder: "; inorder(tree, print);
  std::cout << "\n";
  std::cout << "           expect: f i j g h b c d e a\n\n";

  std::cout << "        postorder: "; postorder(tree, print);
  std::cout << "\n";
  std::cout << "           expect: j i h g f e d c b a\n\n";

  std::cout << "       levelorder: "; levelorder(tree, print);
  std::cout << "\n";
  std::cout << "           expect: a b f c g d i h e j\n\n";
  
  std::cout << "tilted_levelorder: "; tilted_levelorder(tree, print);
  std::cout << "\n";
  std::cout << "           expect: a b c d e f g h i j\n\n";

  std::cout << "********************************************************************************\n";
  std::cout << "* TESTING YOUR tilted_find_parent FUNCTION\n";
  std::cout << "********************************************************************************\n";

  // these are correct based on the known tree
  auto a = tree;
  auto b = tree->left;
  auto c = b->right;
  auto d = c->right;
  auto e = d->right;
  auto f = b->left;
  auto g = f->right;
  auto h = g->right;
  auto i = g->left;
  auto j = i->right;
  test_find_parent(a, "nullptr", "nullptr");
  test_find_parent(b, "a"      , "a"      );
  test_find_parent(c, "b"      , "a"      );
  test_find_parent(d, "c"      , "a"      );
  test_find_parent(e, "d"      , "a"      );
  test_find_parent(f, "b"      , "b"      );
  test_find_parent(g, "f"      , "b"      );
  test_find_parent(h, "g"      , "b"      );
  test_find_parent(i, "g"      , "g"      );
  test_find_parent(j, "i"      , "g"      );
  
  std::cout << "\n";
  std::cout << "********************************************************************************\n";
  std::cout << "* TESTING YOUR tilted_get_children FUNCTION\n";
  std::cout << "********************************************************************************\n";
 
  test_get_children(a, {b,c,d,e});
  test_get_children(b, {f,g,h}); 
  test_get_children(c, {}); 
  test_get_children(d, {}); 
  test_get_children(e, {}); 
  test_get_children(f, {}); 
  test_get_children(g, {i,j}); 
  test_get_children(h, {}); 
  test_get_children(i, {}); 
  test_get_children(j, {}); 

  delete_tree(tree); // clean up
}

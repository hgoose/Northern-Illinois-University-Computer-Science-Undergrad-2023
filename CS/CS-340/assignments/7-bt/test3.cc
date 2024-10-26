
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include "xml.h"
#include <iostream>

static const std::string expected_xml = "<a><b f=\"u\">x</b><c n=\"5\">y</c><d>z<e></e></d>q</a>";

void print_xml_example_tree() {
  using namespace std;
  cout << "  Tree diagram for " << expected_xml << "\n";
  cout << "         <a>          \n"; 
  cout << "        /             \n"; 
  cout << "      <b>             \n"; 
  cout << "     /   \\           \n"; 
  cout << "   'x'    <c>         \n"; 
  cout << "         /   \\       \n"; 
  cout << "       'y'    <d>     \n"; 
  cout << "             /   \\   \n"; 
  cout << "           'z'   'q'  \n"; 
  cout << "             \\       \n"; 
  cout << "              <e>     \n"; 
  cout << "\n";
}

XMLNODE *build_xml_tree(XMLNODE arr[]) {
  using namespace std;
  // xml_element - type, name, fulltext, attrs, closed
  xml_element ele_a(tag,   "a", "",  {} );
  xml_element ele_b(tag,   "b", "",  {make_pair("f", "u")} );
  xml_element ele_c(tag,   "c", "",  {make_pair("n", "5")} );
  xml_element ele_d(tag,   "d", "",  {} );
  xml_element ele_e(tag,   "e", "",  {} );
  xml_element ele_x(plain, "",  "x", {} );
  xml_element ele_y(plain, "",  "y", {} );
  xml_element ele_z(plain, "",  "z", {} );
  xml_element ele_q(plain, "",  "q", {} );

  // fill the nodes with their elements
  XMLNODE *a = arr + 0; a->data = ele_a; 
  XMLNODE *b = arr + 1; b->data = ele_b;
  XMLNODE *c = arr + 2; c->data = ele_c;
  XMLNODE *d = arr + 3; d->data = ele_d;
  XMLNODE *e = arr + 4; e->data = ele_e;
  XMLNODE *x = arr + 5; x->data = ele_x;
  XMLNODE *y = arr + 6; y->data = ele_y;
  XMLNODE *z = arr + 7; z->data = ele_z;
  XMLNODE *q = arr + 8; q->data = ele_q;

  // set up edges
  a->left = b;
  b->parent = a;

  b->left = x;
  x->parent = b;
  b->right = c;
  c->parent = b;
 
  c->left = y;
  y->parent = c;
  c->right = d;
  d->parent = c;

  d->left = z;
  z->parent = d;

  d->right = q;
  q->parent = d;

  z->right = e;
  e->parent = z;


  return a;
}

void test_print_subtree(XMLNODE *root, const std::string &label, const std::string &expected) {
  std::cout << "  Printing " << label << ":\n";
  std::cout << "    expect: " << expected << "\n";
  std::cout << "       got: ";
  xml_print_subtree(root, std::cout);
  std::cout << "\n";
  std::cout << "\n";
}

int main() {
  using namespace std;
  cout << "********************************************************************************\n";
  cout << "* test3 - Test xml_print_subtree with a known tree.\n";
  cout << "*  \n";
  cout << "*   Your output from xml_print_subtree should match the expected output for all\n";
  cout << "* of the tests below. This test allows you to make sure your tree to XML       \n";
  cout << "* conversion is working properly.                                              \n";
  cout << "********************************************************************************\n";
  cout << "\n";
  cout << "********************************************************************************\n";
  cout << "* PRICELESS ASCII ART - < > IS TAG, ' ' IS PLAIN TEXT\n";
  cout << "********************************************************************************\n";
  print_xml_example_tree();  

  XMLNODE nodes[9]; // allocate our nodes on the stack instead of with new
  XMLNODE *root = build_xml_tree(nodes);


  test_print_subtree(root,    "Whole tree from root, a", expected_xml);
  test_print_subtree(nodes+1, "Subtree with b as root", "<b f=\"u\">x</b>");
  test_print_subtree(nodes+2, "Subtree with c as root", "<c n=\"5\">y</c>");
  test_print_subtree(nodes+3, "Subtree with d as root", "<d>z<e></e></d>");
  test_print_subtree(nodes+4, "Subtree with e as root", "<e></e>");
  test_print_subtree(nodes+5, "Subtree with x as root", "x");
  test_print_subtree(nodes+6, "Subtree with y as root", "y");
  test_print_subtree(nodes+7, "Subtree with z as root", "z");
  test_print_subtree(nodes+8, "Subtree with q as root", "q");

}

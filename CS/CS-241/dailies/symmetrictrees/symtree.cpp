#include <iostream>
#include "node.h"

using namespace std;

const int MAX_NODES = 10;

enum node_type{ROOT, LEFT, RIGHT};

static void init(node* v)
{
    for (int i = 0; i < MAX_NODES; i++)
        v[i].left = v[i].right = nullptr;
}

static void print_tree(node* t, node_type type, int lvl)
{
    int i;

    cout << boolalpha;

    if (t)
    {
	    for (i = 0; i < lvl; i ++)
            cout << (type == LEFT ? 'l' : 'r');
        
        cout << "x" << endl;
	    print_tree(t->left, LEFT,  lvl+1);
	    print_tree(t->right, RIGHT, lvl+1);
    }
}

bool symmetric(node* t1, node* t2);

int main()
{
    node t1[MAX_NODES], t2[MAX_NODES];

    /*
    //   t1 x    t2 x
    //     /         \
    //    x           x
    // true
    */
    init(t1);
    init(t2);
    t1[0].left = t1+1;
    t2[0].right = t2+1;
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //   t1 x    t2 x
    //     /         \
    //    x           x
    //               /
    //              x
    // false
    */
    init(t1);
    init(t2);
    t1[0].left = t1+1;
    t2[0].right = t2+1;

    t2[1].left = t2+2;
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //   t1  x    t2 x
    //      /         \
    //     /           \
    //    x             x
    //     \           /
    //      x         x
    // true
    */
    init(t1);
    init(t2);
    
    t1[0].left = t1+1;
    t2[0].right = t2+1;

    t1[1].right = t1+2;
    t2[1].left = t2+2;
    
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //    t1 x    t2 x
    //      /         \
    //     /           \
    //    x             x
    //     \             \
    //      x             x
    // false
    */
    init(t1);
    init(t2);
    
    t1[0].left = t1+1;
    t2[0].right = t2+1;

    t1[1].right = t1+2;
    t2[1].right = t2+2;
    
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //    t1 x    t2 x
    //      /         \
    //     /           \
    //    x             x
    //   / \           /
    //  x   x         x
    // false
    */
    init(t1);
    init(t2);
    
    t1[0].left = t1+1;
    t2[0].right = t2+1;

    t1[1].right = t1+2;
    t2[1].left = t2+2;
    t1[1].left = t1+3;
    
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //    t1 x    t2 x
    //      /         \
    //     /           \
    //    x             x
    //   /             /
    //  x             x
    // false
    */
    init(t1);
    init(t2);
    
    t1[0].left = t1+1;
    t2[0].right = t2+1;

    t1[1].left = t1+2;
    t2[1].left = t2+2;
    
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //   t1 x    t2 x
    // true
    */
    init(t1);
    init(t2);
    
    print_tree(t1, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, t2) << endl << endl;

    /*
    //   t1      t2 
    // true
    */
    print_tree(nullptr, ROOT, 0);
    cout << "---------" << endl;
    print_tree(nullptr, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(nullptr, nullptr) << endl << endl;

    /*
    //   t1      t2 x
    // false
    */
    print_tree(nullptr, ROOT, 0);
    cout << "---------" << endl;
    print_tree(t2,      ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(nullptr, t2) << endl << endl;

    /*
    //   t1 x    t2 
    // false
    */
    print_tree(t1,      ROOT, 0);
    cout << "---------" << endl;
    print_tree(nullptr, ROOT, 0);
    cout << "---------" << endl;
    cout << symmetric(t1, nullptr) << endl << endl;

    return 0;
}

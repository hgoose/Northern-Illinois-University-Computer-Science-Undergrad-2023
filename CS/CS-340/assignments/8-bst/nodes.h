#ifndef NIU_CSCI_340_NODES_H
#define NIU_CSCI_340_NODES_H

////////////////////////////////////////////////////////////////////////////////
// DO NOT MAKE CHANGES TO THIS FILE
//   This file is provided to students so they can plan their assignments, but
// an unchanged version will be used when grading. Any changes you make to this
// file will be ignored, so write your program accordingly.
////////////////////////////////////////////////////////////////////////////////

/*! @brief A binary tree node consisting of a data element, and pointers to the left and right subtrees.
 *  @tparam T The type of the data element contained.
 ***/
template <typename T>
class NodeLR {
  public:
    T data; ///< The data element, of type `T`
    NodeLR <T> * left;  ///< A pointer to the root of the left subtree, or `nullptr` if none exists.
    NodeLR <T> * right; ///< A pointer to the root of the right subtree, or `nullptr` if none exists.
    NodeLR(const T &data, NodeLR *left=nullptr, NodeLR *right=nullptr)
       : data(data), left(left), right(right) { } };

/*! @brief A binary tree node consisting of a data element, and pointers to the left and right subtrees, as well as a parent pointer.
 *  @tparam T The type of the data element contained.
 ***/
template <typename T>
class NodeLRP {
  public:
    T data; ///< The data element, of type `T`
    NodeLRP <T> * left;  ///< A pointer to the root of the left subtree, or `nullptr` if none exists.
    NodeLRP <T> * right; ///< A pointer to the root of the right subtree, or `nullptr` if none exists.
    NodeLRP <T> * parent; ///< A pointer to this node's parent, or `nullptr` if it is root or orphaned.
    NodeLRP(const T &data, NodeLRP *left=nullptr, NodeLRP *right=nullptr, NodeLRP *parent=nullptr)
      : data(data), left(left), right(right), parent(parent) { } };


#endif /* NIU_CSCI_340_NODES_H */

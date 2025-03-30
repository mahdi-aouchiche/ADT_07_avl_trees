#ifndef __AVL_TREE_HPP_
#define __AVL_TREE_HPP_

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include "node.hpp"
using namespace std; 

class AVLTree 
{ 
  private:
  /*
    Holds a unique id of each created node.
  */
  int node_ID;
    
  /* 
    Root of the tree 
  */
  Node* tree_root; 

  public:
  /* 
    Constructor 
  */
  AVLTree();

  /* 
    Insert a key to the AVL tree 
    and perform rotations if necessary.
    Doesn't accept duplicates
  */
  void insert(const string &);

  /* 
    Remove a key from the binary search tree 
    and keep the AVL tree balance
  */
  void remove(const string &);

  /*
    Search function without a recursive call.
    Find if a key is present in the tree
    Returns true if the key exists, false otherwise 
  */
  bool search(const string &);
   
  /* 
    Traverse and print the AVL tree in inorder notation.
    Print the key followed by its balance factor
    in parentheses followed by a space.
  */
  void print_balance_factors();

  /* 
    Generate dotty file and visualize the tree using graphiz program.
    This function is called before and after rotation.
  */
  void visualize_tree(const string &outputFilename);

  /*
    Delete the tree
  */
  void delete_tree();

  private:
  /*
    Helper function to the remove function
  */
  bool remove_node(Node*);

  /* 
    Find and return the closest unbalanced node 
    to the inserted node.
  */
  Node* find_unbalanced_node(Node*);

  /* 
    Implement four possible imbalance cases 
    and update the parent of the given node.
  */
  void rotate(Node*);

  /* 
    Rotate the subtree to left at the given node
    and returns the new subroot. 
  */ 
  Node* rotate_left(Node*);

  /* 
    Rotate the subtree to right at the given node
    and returns the new subroot.
  */
  Node* rotate_right(Node*);

  /* 
    Return the balance factor of a given node 
  */
  int balance_factor(Node*) const;

  /* 
    Returns a node's height 
  */
  int node_height(Node*) const;

  /* 
    Print the balanceFactor of a node 
  */ 
  void print_balance_factors(Node*);

  /* 
    Helper function to visualize the avl tree 
  */
  void visualize_tree(ofstream &, Node*);

  /* 
    Helper function to display a node's string and balance.
    node_id [color = red, peripheries=2, style = filled, label=" data & balance"]
  */
  void visualize_nodes(ofstream &, Node*);

  /*
    Recursive implementation of search.
    Returns a pointer to the node if it exists, 
    otherwise nullptr
  */
  Node* search(Node*, const string &);

  /*
    Trickle up the tree from the given node 
    and balance the tree. 
  */
  void trickle_up_and_balance_tree(Node*);

  /*
    Delete a node
    Helper function to delete the tree
  */
  void delete_node(Node* node);
};

#endif  // __AVL_TREE_HPP_
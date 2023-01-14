#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <string>
using namespace std;

class Node 
{
  private:
  Node* parent ;    // node's parent pointer 
  Node* l_child;    // node's left child pointer 
  Node* r_child;    // node's right child pointer 
  string str   ;    // holds the string or the data
  int node_ID  ;    // holds a unique id of a node
  
  public:
  /*
    Constructor
  */ 
  Node();

  /* setters  */
  /*
    set the node's string
  */ 
  void set_str(string );

  /*
    set the node's ID
  */
  void set_node_ID(int );

  /*
    set the node's parent
  */ 
  void set_parent(Node* );

  /*
    set the node's left child
  */
  void set_l_child(Node* );

  /*
    set the node's right child
  */
  void set_r_child(Node* );

  /* getters */
  /*
    returns the node's string
  */ 
  string get_str() const;

  /*
    returns the node's ID
  */
  int get_node_ID() const;

  /*
    returns the node's parent
  */ 
  Node* get_parent() const; 

  /*
    returns the node's left child
  */
  Node* get_l_child() const;

  /*
    returns the node's right child  
  */
  Node* get_r_child() const;
};

#endif // __NODE_HPP__
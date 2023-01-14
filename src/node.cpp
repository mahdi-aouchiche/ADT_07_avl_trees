#include "../header/node.hpp"

Node::Node() {
  parent  = nullptr; 
  l_child = nullptr;
  r_child = nullptr; 
  str     = "";
  node_ID = 0;
};

void Node::set_str(string str) {
  this->str = str;
}
 
void Node::set_node_ID(int id) {
  this->node_ID = id; 
}

void Node::set_parent(Node * parent_node) {
  this->parent = parent_node; 
}

void Node::set_l_child(Node* leftNode) {
  this->l_child = leftNode; 
}

void Node::set_r_child(Node * rightNode) {
  this->r_child = rightNode;
}

string Node::get_str() const {
  return this->str;
}

int Node::get_node_ID() const {
  return this->node_ID;
}

Node* Node::get_parent() const {
  return this->parent;
}

Node* Node::get_l_child() const {
  return this->l_child;
}

Node* Node::get_r_child() const {
  return this->r_child; 
}
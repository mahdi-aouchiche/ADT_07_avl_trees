#include "../header/avl_tree.hpp"

AVLTree::AVLTree() {
  this->node_ID = 0;
  this->tree_root = nullptr;
}

void AVLTree::insert(const string &str) {
  /* Invalid input */
  if(str == "") { 
    cout << "Nothing to insert." << endl;
    return; 
  } 

  /* Insert the new node as a leaf using BST insertion */
  Node* curr = nullptr;
  
  /* Create a new node */
  Node* new_node = new Node();
  new_node->set_node_ID(this->node_ID++);
  new_node->set_str(str);  
  
  if(!this->tree_root) { /* Insert to an empty tree */
    this->tree_root = new_node;

  } else {               /* Insert to a non empty tree */
    curr = this->tree_root;
    while(curr) {
      /* Do not insert duplicates */
      if( new_node->get_str() == curr->get_str() ) {
        new_node->set_node_ID(this->node_ID--);
        delete new_node;
        cout << "\'" << str << "\' already exists." << endl;
        return;             /* Done with insertion */

      } else if (new_node->get_str() < curr->get_str()) {
        if(!curr->get_l_child()) {
          curr->set_l_child(new_node);
          new_node->set_parent(curr);
          curr = nullptr;   /* Done with insertion */

        } else {
          curr = curr->get_l_child();
        }

      } else {
        if(!curr->get_r_child()) {
          curr->set_r_child(new_node);
          new_node->set_parent(curr);
          curr = nullptr;   /* Done with insertion */
          
        } else {
          curr = curr->get_r_child();
        }
      }
    } 
    this->trickle_up_and_balance_tree(new_node);
  }
  cout << "Insertion successful." << endl; 
}

void AVLTree::remove(const string &str) {
  Node* node_to_remove = this->search(this->tree_root, str);  

  if(!node_to_remove) {
    cout << "\'" << str << "\' does not exist in the avl tree." << endl;
    return;
  }
  if(this->remove_node(node_to_remove)) {
    cout << "\'" << str << "\' removed successful." << endl;
  } else {
    cout << "\'" << str << "\' removal unsuccessful." << endl;
  }
}

bool AVLTree::search(const string &str) {
  if(str != "") {
    Node* curr = this->tree_root;
    while (curr) {
      if( str == curr->get_str() ) {
        return true;
      } else if (str < curr->get_str() ) {
        curr = curr->get_l_child();
      } else {
        curr = curr->get_r_child();
      }
    }
  }
  return false;    
}
   
void AVLTree::print_balance_factors() {
  if(!this->tree_root) {
    cout << "AVL tree is empty." << endl;
    return;
  } 
  this->print_balance_factors(this->tree_root);  
  cout << endl;
}

void AVLTree::visualize_tree(const string &outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if(!outFS.is_open()){
    cout << "Error opening "<< outputFilename << endl;
    return;
  }

  outFS << "/* If you do not have graphviz program installed: " << endl; 
  outFS << " Use webgraphviz.com to display the visualizeTree." << endl; 
  outFS << " Copy the content of the .dot files generated, "    << endl;
  outFS << " and paste the digraph function to see the graph."  << endl;
  outFS << "*/ " << endl << endl;
  
  outFS << "digraph G {" << endl;
  // output the nodes 
  outFS << "// nodes:" << endl;
  if(this->tree_root != nullptr) {
    this->visualize_nodes(outFS,this->tree_root);
  }
  // output the edges 
  outFS << "// edges:" << endl;
  if(this->tree_root != nullptr) {
    this->visualize_tree(outFS,this->tree_root);
  }  
  outFS << "}";

  outFS.close();

  try
  {
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    cout << "The \"sh: 1: dot not found\" exception results from missing graphviz program which displays the AVL tree graphs." << endl; 
    cout << "Try installing graphviz using the command: sudo apt-get install graphviz" <<endl;
  }
}

bool AVLTree::remove_node(Node* node) {
  Node* parent = node->get_parent();
  Node* node_to_balance = parent;
  
  /* Case 1: delete a leaf node */
  if(!node->get_l_child() && !node->get_r_child()) {
    if(node == this->tree_root) {
      this->tree_root = nullptr;
    } else if(node == parent->get_l_child()){
      parent->set_l_child(nullptr);
    } else {
      parent->set_r_child(nullptr);
    }
  }
  
  /* Case 2: delete a node with 2 children */
  else if(node->get_l_child() && node->get_r_child()){
    /* Find a successor */
    Node* succesor_node = node->get_r_child();
    while(succesor_node->get_l_child()) {
      succesor_node = succesor_node->get_l_child();
    }
    
    /* Update the root if the root is to be removed */
    if(node == this->tree_root) {
      this->tree_root = succesor_node;
    } else {
      /* Update the successor as a child */
      if(parent->get_l_child() == node) {
        parent->set_l_child(succesor_node);
      } else {
        parent->set_r_child(succesor_node);
      }
    }
    
    /* update the successor's children */
    if(succesor_node == node->get_r_child()) {
      succesor_node->set_l_child(node->get_l_child());
      node->get_l_child()->set_parent(succesor_node);
      node_to_balance = succesor_node;
    } else {
      succesor_node->get_parent()->set_l_child(succesor_node->get_r_child());
      if(succesor_node->get_r_child()) {
        succesor_node->get_r_child()->set_parent(succesor_node->get_parent());
      }
      succesor_node->set_l_child(node->get_l_child());
      node->get_l_child()->set_parent(succesor_node);
      succesor_node->set_r_child(node->get_r_child());
      node->get_r_child()->set_parent(succesor_node);
      /* Start balancing the tree from the succesor's parent */
      node_to_balance = succesor_node->get_parent();
    }
    /* Update the successor parent */
    succesor_node->set_parent(parent);
  }
      
  /* Case 3: delete a node with 1 child */
  else {
    if(node->get_l_child()) {
      node->get_l_child()->set_parent(parent);

      if(node == this->tree_root) {
        this->tree_root = node->get_l_child();
      } else {
        if(parent->get_l_child() == node) {
          parent->set_l_child(node->get_l_child());
        } else {
          parent->set_r_child(node->get_l_child());
        }
      }
      
    } else {
      node->get_r_child()->set_parent(parent);

      if(node == this->tree_root) {
        this->tree_root = node->get_r_child();
      } else {
        if(parent->get_l_child() == node) {
          parent->set_l_child(node->get_r_child());
        } else {
          parent->set_r_child(node->get_r_child());
        }
      }
    }
  }

  /* Delete the node */
  delete node;
  /* Propagate up the tree and balance the tree */ 
  this->trickle_up_and_balance_tree(node_to_balance);
  
  return true;
}

Node* AVLTree::find_unbalanced_node(Node* node) {
  if(node) {
    int balance_factor;
    Node* curr = node;
    do {
      balance_factor = this->balance_factor(curr);
      if( balance_factor >= 2 || balance_factor <= -2 ) {
        return curr;
      } else {
        curr = curr->get_parent();
      }
    } while (curr);
  }
  return nullptr;
}

void AVLTree::rotate(Node* node) {
  if(!node) return;
    
  Node* parent = node->get_parent();
  Node* subroot = nullptr;
  int balance_factor = this->balance_factor(node);

  if(balance_factor >= 2) {
    /* Rotate left at the node's left child*/
    if(node->get_l_child() && (this->balance_factor(node->get_l_child()) <= -1)) {
      subroot = this->rotate_left(node->get_l_child());
      subroot->set_parent(node);
      node->set_l_child(subroot);
    }
    /* Rotate right at the given node */
    subroot = this->rotate_right(node);
       
  } else if (balance_factor <= -2) {
    /* Rotate right at the node's right child */
    if(node->get_r_child() && (this->balance_factor(node->get_r_child()) >= 1)) {
      subroot = this->rotate_right(node->get_r_child());
      subroot->set_parent(node);
      node->set_r_child(subroot);
    }
    /* Rotate left at the given node */
    subroot = this->rotate_left(node);
  }

  /* Update the subroot parent */
  subroot->set_parent(parent);

  /* Update the child of the parent */
  if(!parent) {
    this->tree_root = subroot;
    return;
  } 

  if (subroot->get_str() < parent->get_str()) {
    parent->set_l_child(subroot);
  } else {
    parent->set_r_child(subroot);
  }
}

Node* AVLTree::rotate_left(Node* node) {
  Node* r_child = node->get_r_child();
  if(r_child->get_l_child()) {
    r_child->get_l_child()->set_parent(node);
  }
  node->set_r_child(r_child->get_l_child());
  node->set_parent(r_child); 
  r_child->set_l_child(node);

  return r_child;
}

Node* AVLTree::rotate_right(Node* node) {
  Node* l_child = node->get_l_child();
  if(l_child->get_r_child()) {
    l_child->get_r_child()->set_parent(node);
  }
  node->set_l_child(l_child->get_r_child());
  node->set_parent(l_child);
  l_child->set_r_child(node);

  return l_child; 
}

int AVLTree::balance_factor(Node* node) const {
  if(!node) {
    return -1;
  } 
  int l_height = this->node_height(node->get_l_child());
  int r_height = this->node_height(node->get_r_child());
  return (l_height - r_height);
}

int AVLTree::node_height(Node* node) const {
  if(!node) {
    return -1;
  }
  int l_height = this->node_height(node->get_l_child());
  int r_height = this->node_height(node->get_r_child());
  return ( max(l_height, r_height) + 1);
}

void AVLTree::print_balance_factors(Node* node) {
  if(!node) {
    return;
  }
  print_balance_factors(node->get_l_child());
  cout << node->get_str() << "(" << this->balance_factor(node) << ") ";
  print_balance_factors(node->get_r_child());
}

void AVLTree::visualize_tree(ofstream &outFS, Node* node) {
  if(!node) {
    return;
  }

  if(node->get_l_child()) {
    visualize_tree( outFS, node->get_l_child() );
    outFS 
      << node->get_node_ID() << " -> " 
      << node->get_l_child()->get_node_ID() 
      << ";" << endl
    ;    
  }

  if(node->get_r_child()) {
    visualize_tree( outFS, node->get_r_child() );
    outFS 
      << node->get_node_ID() << " -> " 
      << node->get_r_child()->get_node_ID() 
      << ";" << endl
    ;    
  }
}

void AVLTree::visualize_nodes(ofstream &outputfile, Node* node) {
  if(!node) { 
    return; 
  } 
  /* Write the nodes in postfix */
  visualize_nodes(outputfile, node->get_l_child());
  visualize_nodes(outputfile, node->get_r_child());
  
  outputfile << node->get_node_ID();  
  outputfile << " [shape=circle, color=lightblue, peripheries=2, style=filled, label=\""; 
  outputfile << node->get_str() << "\n(" << this->balance_factor(node) << ")\"]" << endl; 
}

Node* AVLTree::search(Node* node, const string &str) {
  if(!node || str == ""){
    return nullptr;
  } else if(str == node->get_str()) {
    return node;
  } else if(str < node->get_str()) {
    return this->search(node->get_l_child(), str);
  } else {
    return this->search(node->get_r_child(), str);
  }
}

void AVLTree::trickle_up_and_balance_tree(Node* node) {
  Node* unbalanced_node = this->find_unbalanced_node(node);
  if(unbalanced_node) {
    /* Output a file before rotation */
    this->visualize_tree("./output_files/tree_before_rotation.dot");
    Node* curr = node;
    while (unbalanced_node) {
      curr = unbalanced_node->get_parent();
      this->rotate(unbalanced_node); 
      unbalanced_node = this->find_unbalanced_node(curr);
    }
    /* Output a file after rotation */   
    this->visualize_tree("./output_files/tree_after_rotation.dot");       
  }
}
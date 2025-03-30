# Abstact Data Types : AVL Trees

Author: Mahdi Aouchiche (<https://github.com/mahdi-aouchiche/ADT_07_avl_trees>)

* Build an AVL tree which balances itself.
* User interface allows to insert, delete, search, inorder tree output, and display the AVL tree.
* The AVL tree is created using a Node class. Each node has 3 pointers (parent, left child, and right child), a unique ID, and a string key.
* The visualize tree function writes the AVL tree to a ".dot" file as a graph in output files folder. Graphviz program uses the the generated ".dot" file to display the AVL tree.
  * If the graphviz program is not installed or not installed correctly you can use an alternative to copy the ".dot" file and paste it on [webgraphviz][graphviz] to see the AVL tree visualization.
* If a rotation is performed after an insertion or a deletion, two ".dot" files (tree_before_rotation & tree_after_rotation) and the visualization images of the AVL tree (before and after) the rotation are written to the output_files folder.

## To run the project nicely run the following commands

```c++
cmake -S . -B build
cmake --build build/ 
```

## 1 executable is created, use the following command to run an executable

```c++
// run the code
./build/avl_tree
```

OR

```c++
// run with valgrind to check for memory leaks
valgrind --leak-check=full ./build/avl_tree
```

[graphviz]: http://www.webgraphviz.com/

#include <iostream>
#include "node.cpp"
#include "avl_tree.cpp"
#include <chrono>
#include <ctime>
using namespace std;

int selection_menu();

int main( ) {
  /* Create an output file */
  const char* remove_existing_directory = "rm -rf output_files";
  const char* create_directory = "mkdir output_files"; 
  system(remove_existing_directory);
  system(create_directory);
  
  /* Create and build an AVL tree */
  AVLTree tree;
  string entry;
  bool exit = false;

  do {
    switch (selection_menu())
    {
      case 1:   /* Insert */
      { 
        cout << "Enter a string to insert: ";
        getline(cin, entry);
        tree.insert(entry);      
        break;
      }

      case 2:   /* Romove a node by a given key */
      {
        cout << "Enter the key to remove: ";
        getline(cin, entry);
        tree.remove(entry);
        break;
      }
    
      case 3:   /* Find if a key exists */
      {
        cout << "Enter the key to search: ";
        getline(cin,entry);
        
        if(tree.search(entry)){
          cout << entry << " exists in the tree." << endl;
        } else {
          cout << entry << " does not exist in the tree." << endl;
        }    
        break;
      }
      
      case 4:   /* Print balance factors */
      {
        tree.print_balance_factors();
        break;
      }
    
      case 5:   /* Display the tree */
      {
        tree.visualize_tree("./output_files/my_tree.dot"); 
        system("code ./output_files/my_tree.jpg");
        break;
      }

      case 6:   /* Test for elapsed time to build the tree */
      {
        int num_nodes = 0;
        int max_num_nodes = 200;

        int minutes = 0;
        double seconds = 0;
        double total_time = 0;

        cout << "Enter the total number (0 to ";
        cout << max_num_nodes;
        cout << ") of nodes to insert to the AVL tree:  ";
        cin >> num_nodes;
        cin.clear();
        cin.ignore(256, '\n');

        if(num_nodes > max_num_nodes ) {
          num_nodes = max_num_nodes;
          cout << "Inserting " << num_nodes << " nodes: " << endl;
        }

        auto start = chrono::system_clock::now();
        for(int i = 1; i <= num_nodes ; i++) {
          cout << i << " ";
          tree.insert(to_string(i));
        } 
        auto end = chrono::system_clock::now();
          
        chrono::duration<double> elapsed_seconds = end-start;

        total_time = elapsed_seconds.count();
        minutes = total_time / 60;
        seconds = total_time - minutes; 

        cout 
          << "Elapsed time to build an AVL tree with " 
          << num_nodes << " nodes = "
          << minutes << " minutes and " 
          << seconds << " seconds." << endl
        ;
        break;
      } 

      case 7:   /* Quit */
      {
        tree.delete_tree();
        system(remove_existing_directory);

        cout << "Exit!";        
        exit = true;
        break;
      }
  
      default:
      {
        cout << "Invalid selection." << endl; 
        break;
      }
    }
    cout << endl;
  } while (!exit);
  return 0;
}

/// @brief displays AVL tree user interface and prompt the user for input
/// @return user's input
int selection_menu() {
  int choice = 0;
  cout 
    << "Menu: "                             << endl
    << "1. Insert a key (string)."          << endl
    << "2. Remove a key from the AVL tree." << endl
    << "3. Search for a key (string)."      << endl
    << "4. Print the AVL tree."             << endl
    << "5. Visualize the AVL tree."         << endl
    << "6. Test for elapsed time."          << endl
    << "7. Quit!"                           << endl
    << "Enter a choice from menu: "
  ;
  cin >> choice;

  // Fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}
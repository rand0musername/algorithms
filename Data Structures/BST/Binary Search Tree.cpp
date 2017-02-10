// RandomUsername (Nikola Jovanovic)
// Binary Search Tree

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

template <typename T>
class BinarySearchTree {
 public:
  BinarySearchTree() {
    root = NULL;
    size = 0;
  }

  // Traverses the tree and finds data associated with a given key.
  bool Find(int key, T* data) {
    Node* curr = root;
    while (curr != NULL) {
      if (key < curr -> key) {
        curr = curr -> left;
      } else if (key > curr -> key) {
        curr = curr -> right;
      } else {
        *data = curr -> data;
        return true;
      }
    }
    return false;
  }

  // Inserts a given (key, data) pair into the tree.
  bool Insert(std::pair<int, T> kv) {
    if (root == NULL) {
      root = new Node(kv);
      size++;
      return true;
    }
    Node* curr = root;
    while (kv.first != curr -> key) {
      if (kv.first < curr -> key) {
        if (curr -> left == NULL) {
          curr -> left = new Node(kv);
          size++;
          return true;
        }
        curr = curr -> left;
      } else {
        if (curr -> right == NULL) {
          curr -> right = new Node(kv);
          size++;
          return true;
        }
        curr = curr -> right;
      }
    }
    return false;
  }

  // Deletes the node with a given key, if such node exists.
  bool Delete(int key) {
    Node* parent = NULL;
    Node* curr = root;
    // Finds the node to be deleted.
    while (curr != NULL && key != curr -> key) {
      parent = curr;
      if (key < curr -> key) {
        curr = curr -> left;
      } else {
        curr = curr -> right;
      }
    }
    if (curr == NULL) {
      return false;
    }
    Node** child_ptr;
    if (curr == root) {
      child_ptr = &root;
    } else if (parent -> left == curr) {
      child_ptr = &(parent -> left);
    } else {
      child_ptr = &(parent -> right);
    }
    // Removes the node from the tree.
    if (curr -> left == NULL && curr -> right == NULL) {
      *child_ptr = NULL;
      delete curr;
      size--;
    } else if (curr -> left == NULL) {
      *child_ptr = curr -> right;
      delete curr;
      size--;
    } else if (curr -> right == NULL) {
      *child_ptr = curr -> left;
      delete curr;
      size--;
    } else {
      // The node has both children, swaps curr with its predecessor.
      Node* pred = curr -> left;
      while (pred -> right != NULL) {
        pred = pred -> right;
      }
      int pred_key = pred -> key;
      T pred_data = pred -> data;
      Delete(pred_key);
      curr -> key = pred_key;
      curr -> data = pred_data;
    }
    return true;
  }

  // Creates a DOT file with tree representation
  // and visualizes the tree using GraphViz.
  void Draw(std::string name) {
    std::ofstream dot_file;
    dot_file.open(name + ".dot");
    dot_file << "digraph{\n";
    PrintTree(root, dot_file);
    dot_file << "}\n";
    dot_file.close();
    std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
    system(command.c_str());
  }

  int GetSize() {
    return size;
  }

 private:
    class Node {
     public:
      explicit Node(std::pair<int, T> kv) {
        key = kv.first;
        data = kv.second;
        right = left = NULL;
      }

      int key;
      T data;
      Node* right;
      Node* left;
    };

    // Does a postorder traversal and prints tree data in DOT format.
    void PrintTree(Node* curr, std::ofstream &dot_file) {
      if (curr == NULL) {
        return;
      }
      dot_file << curr -> key << "[label=\"" << curr -> key << "\"];\n";
      if (curr -> left != NULL) {
        dot_file << curr -> key << " -> " << curr -> left -> key << "\n";
        PrintTree(curr -> left, dot_file);
      } else {
        dot_file << "null_l_" << curr -> key << "[shape=point];\n";
        dot_file << curr -> key << " -> " << "null_l_" << curr -> key << "\n";
      }
      if (curr -> right != NULL) {
        dot_file << curr -> key << " -> " << curr -> right -> key << "\n";
        PrintTree(curr -> right, dot_file);
      } else {
        dot_file << "null_r_" << curr -> key << "[shape=point];\n";
        dot_file << curr -> key << " -> " << "null_r_" << curr -> key << "\n";
      }
    }

    Node* root;
    int size;
};

int main() {
  // Test based on: https://en.wikipedia.org/wiki/Binary_search_tree
  BinarySearchTree<std::string>* tree = new BinarySearchTree<std::string>();
  tree -> Insert({8, "Eight"});
  tree -> Insert({3, "Three"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({14, "Fourteen"});
  tree -> Insert({13, "Thirteen"});
  tree -> Insert({1, "One"});
  tree -> Insert({6, "Six"});
  tree -> Insert({7, "Seven"});
  tree -> Insert({4, "Four"});
  tree -> Draw("tree_full");
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  std::string data;
  tree -> Find(4, &data);
  std::cout << "Data with key 4: " << data << std::endl;
  std::cout << "Failed insertion: " << tree -> Insert({1, "One"}) << std::endl;
  std::cout << "Trivial deletion: " << tree -> Delete(13) << std::endl;
  std::cout << "One-kid deletion: " << tree -> Delete(10) << std::endl;
  std::cout << "Two-kid deletion: " << tree -> Delete(3) << std::endl;
  std::cout << "Root deletion: " << tree -> Delete(8) << std::endl;
  tree -> Draw("tree_final");
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  return 0;
}

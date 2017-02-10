// RandomUsername (Nikola Jovanovic)
// AVL Tree

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

template <typename T>
class AvlTree {
 public:
  AvlTree() {
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
      root = new Node(kv, NULL);
      size++;
      return true;
    }
    Node* curr = root;
    while (kv.first != curr -> key) {
      if (kv.first < curr -> key) {
        if (curr -> left == NULL) {
          curr -> left = new Node(kv, curr);
          size++;
          Balance(curr);
          return true;
        }
        curr = curr -> left;
      } else {
        if (curr -> right == NULL) {
          curr -> right = new Node(kv, curr);
          size++;
          Balance(curr);
          return true;
        }
        curr = curr -> right;
      }
    }
    return false;
  }

  // Deletes the node with a given key, if such node exists.
  bool Delete(int key) {
    Node* curr = root;
    // Finds the node to be deleted.
    while (curr != NULL && key != curr -> key) {
      if (key < curr -> key) {
        curr = curr -> left;
      } else {
        curr = curr -> right;
      }
    }
    if (curr == NULL) {
      return false;
    }
    Node* parent = curr -> parent;
    Node** child_ptr;
    if (curr == root) {
      child_ptr = &root;
    } else if (parent -> left == curr) {
      child_ptr = &(parent -> left);
    } else {
      child_ptr = &(parent -> right);
    }
    // Removes the node from the tree.
    if (curr -> left == NULL || curr -> right == NULL) {
      if (curr -> left == NULL && curr -> right == NULL) {
        *child_ptr = NULL;
      } else if (curr -> left == NULL) {
        *child_ptr = curr -> right;
        curr -> right -> parent = parent;
      } else if (curr -> right == NULL) {
        *child_ptr = curr -> left;
        curr -> left -> parent = parent;
      }
      delete curr;
      size--;
      Balance(parent);
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
      explicit Node(std::pair<int, T> kv, Node* parent) {
        key = kv.first;
        data = kv.second;
        right = left = NULL;
        this -> parent = parent;
        height = 1;
      }

      int key;
      T data;
      Node* right;
      Node* left;
      Node* parent;
      int height;
    };

    // Does a postorder traversal and prints tree data in DOT format.
    void PrintTree(Node* curr, std::ofstream &dot_file) {
      if (curr == NULL) {
        return;
      }
      dot_file << curr -> key << "[label=\"" << curr -> key;
      dot_file << " (" << curr -> height << ", ";
      dot_file << std::showpos << GetBalanceFactor(curr);
      dot_file << std::noshowpos << ")\"];\n";
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

    // Balances the tree starting from curr, going upward.
    void Balance(Node* curr) {
      while (curr != NULL) {
        // Keeps height information up to date.
        curr -> height = std::max(GetHeight(curr -> left),
                                  GetHeight(curr -> right)) + 1;
        if (GetBalanceFactor(curr) == -2) {
          if (GetHeight(curr -> left -> right) >
              GetHeight(curr -> left -> left)) {
            LeftRotation(curr -> left);
          }
          RightRotation(curr);
        } else if (GetBalanceFactor(curr) == 2) {
          if (GetHeight(curr -> right -> left) >
              GetHeight(curr -> right -> right)) {
            RightRotation(curr -> right);
          }
          LeftRotation(curr);
        }
        curr = curr -> parent;
      }
    }

    // Performs a left rotation on the tree.
    void LeftRotation(Node* curr) {
      Node* pivot = curr -> right;
      Node* parent = curr -> parent;
      curr -> right = pivot -> left;
      if (curr -> right != NULL) {
        curr -> right -> parent = curr;
      }
      pivot -> left = curr;
      curr -> parent = pivot;
      if (parent != NULL) {
        if (parent -> left == curr) {
          parent -> left = pivot;
        } else {
          parent -> right = pivot;
        }
      }
      pivot -> parent = parent;
      if (root == curr) {
        root = pivot;
      }
      curr -> height = std::max(GetHeight(curr -> left),
                                GetHeight(curr -> right)) + 1;
      pivot -> height = std::max(GetHeight(pivot -> left),
                                 GetHeight(pivot -> right)) + 1;
    }

    // Performs a right rotation on the tree.
    void RightRotation(Node* curr) {
      Node* pivot = curr -> left;
      Node* parent = curr -> parent;
      curr -> left = pivot -> right;
      if (curr -> left != NULL) {
        curr -> left -> parent = curr;
      }
      pivot -> right = curr;
      curr -> parent = pivot;
      if (parent != NULL) {
        if (parent -> right == curr) {
          parent -> right = pivot;
        } else {
          parent -> left = pivot;
        }
      }
      pivot -> parent = parent;
      if (root == curr) {
        root = pivot;
      }
      curr -> height = std::max(GetHeight(curr -> right),
                                GetHeight(curr -> left)) + 1;
      pivot -> height = std::max(GetHeight(pivot -> right),
                                 GetHeight(pivot -> left)) + 1;
    }

    int GetBalanceFactor(Node* curr) {
      return GetHeight(curr -> right) - GetHeight(curr -> left);
    }

    int GetHeight(Node* curr) {
      if (curr == NULL) {
        return 0;
      } else {
        return curr -> height;
      }
    }

    Node* root;
    int size;
};

int main() {
  // Tests insertions.
  AvlTree<std::string>* tree = new AvlTree<std::string>();
  tree -> Insert({10, ""});
  tree -> Insert({20, ""});
  tree -> Insert({30, ""});  // LROT
  tree -> Draw("tree_rot1");
  tree -> Insert({25, ""});
  tree -> Insert({35, ""});
  tree -> Insert({36, ""});
  tree -> Insert({2, ""});
  tree -> Insert({11, ""});
  tree -> Insert({1, ""});
  tree -> Insert({27, ""});
  tree -> Insert({22, ""});
  tree -> Insert({21, ""});
  tree -> Insert({23, ""});
  tree -> Insert({24, ""});  // RROT + LROT
  tree -> Draw("tree_rot2");
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  std::string data;
  tree -> Find(4, &data);

  // Tests deletions.
  // Based on https://webdocs.cs.ualberta.ca/~holte/T26/tree-deletion.html
  AvlTree<std::string>* tree2 = new AvlTree<std::string>();
  tree2 -> Insert({30, ""});
  tree2 -> Insert({50, ""});
  tree2 -> Insert({20, ""});
  tree2 -> Insert({8, ""});
  tree2 -> Insert({23, ""});
  tree2 -> Insert({70, ""});
  tree2 -> Insert({40, ""});
  tree2 -> Insert({6, ""});
  tree2 -> Insert({45, ""});
  tree2 -> Insert({75, ""});
  tree2 -> Insert({68, ""});
  tree2 -> Insert({77, ""});
  tree2 -> Insert({10, ""});
  tree2 -> Insert({24, ""});
  tree2 -> Insert({22, ""});
  tree2 -> Insert({21, ""});
  tree2 -> Insert({7, ""});
  tree2 -> Insert({9, ""});
  tree2 -> Insert({11, ""});
  tree2 -> Insert({12, ""});
  tree2 -> Draw("tree2_before_deletion");
  tree2 -> Delete(24);  // RROT, LROT + RROT
  tree2 -> Draw("tree2_after_deletion");
  std::cout << "Tree size: " << tree2 -> GetSize() << std::endl;
  return 0;
}

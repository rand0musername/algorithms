// RandomUsername (Nikola Jovanovic)
// Naive Binary Search Tree

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

template <typename T>
class NaiveBst {
 public:
  NaiveBst();
  bool Find(int key, T* data);
  bool Insert(std::pair<int, T> kv);
  bool Delete(int key);
  int GetSize();
  void Draw(std::string name);
 private:
  struct Node {
    int key;
    T data;
    Node* left;
    Node* right;
    explicit Node(std::pair<int, T> kv) {
      key = kv.first;
      data = kv.second;
      right = left = NULL;
    }
  };
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
};

template <typename T>
NaiveBst<T>::NaiveBst() {
  root = NULL;
  size = 0;
}

template <typename T>
bool NaiveBst<T>::Find(int key, T* data) {
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

template <typename T>
bool NaiveBst<T>::Insert(std::pair<int, T> kv) {
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

template <typename T>
bool NaiveBst<T>::Delete(int key) {
  Node* parent = NULL;
  Node* curr = root;
  // Find the node to be deleted
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
  // Remove the node from the tree
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
    // The node has both children, swap curr with its predecessor
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

template <typename T>
int NaiveBst<T>::GetSize() {
  return size;
}

// Visualizes the tree using GraphViz.
template <typename T>
void NaiveBst<T>::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  PrintToDot(root, dot_file);
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

template <typename T>
void NaiveBst<T>::PrintToDot(Node* curr, std::ofstream& dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << curr -> key << "[label=\"" << curr -> key << "\"];\n";
  if (curr -> left != NULL) {
    dot_file << curr -> key << " -> " << curr -> left -> key << "\n";
    PrintToDot(curr -> left, dot_file);
  } else {
    dot_file << "null_l_" << curr -> key << "[shape=point];\n";
    dot_file << curr -> key << " -> " << "null_l_" << curr -> key << "\n";
  }
  if (curr -> right != NULL) {
    dot_file << curr -> key << " -> " << curr -> right -> key << "\n";
    PrintToDot(curr -> right, dot_file);
  } else {
    dot_file << "null_r_" << curr -> key << "[shape=point];\n";
    dot_file << curr -> key << " -> " << "null_r_" << curr -> key << "\n";
  }
}

int main() {
  // Test based on: https://en.wikipedia.org/wiki/Binary_search_tree
  NaiveBst<std::string>* tree = new NaiveBst<std::string>();
  tree -> Insert({8, "Eight"});
  tree -> Insert({3, "Three"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({14, "Fourteen"});
  tree -> Insert({13, "Thirteen"});
  tree -> Insert({1, "One"});
  tree -> Insert({6, "Six"});
  tree -> Insert({7, "Seven"});
  tree -> Insert({4, "Four"});
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  tree -> Draw("nbst_full");
  std::string data;
  tree -> Find(4, &data);
  std::cout << "Data with key 4: " << data << std::endl;
  std::cout << "Failed insertion: " << tree -> Insert({1, "One"}) << std::endl;
  std::cout << "Trivial deletion: " << tree -> Delete(13) << std::endl;
  std::cout << "One-kid deletion: " << tree -> Delete(10) << std::endl;
  std::cout << "Two-kid deletion: " << tree -> Delete(3) << std::endl;
  std::cout << "Root deletion: " << tree -> Delete(8) << std::endl;
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  tree -> Draw("nbst_final");
  return 0;
}

// RandomUsername (Nikola Jovanovic)
// AVL Tree

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

template <typename T>
class AvlTree {
 public:
  AvlTree();
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
    Node* parent;
    int height;
    explicit Node(std::pair<int, T> kv, Node* parent) {
      key = kv.first;
      data = kv.second;
      right = left = NULL;
      this -> parent = parent;
      height = 1;
    }
  };
  void Balance(Node* curr);
  void RotateLeft(Node* curr);
  void RotateRight(Node* curr);
  int GetBalanceFactor(Node* curr);
  int GetHeight(Node* curr);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
};

template <typename T>
AvlTree<T>::AvlTree() {
  root = NULL;
  size = 0;
}

template <typename T>
bool AvlTree<T>::Find(int key, T* data) {
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
bool AvlTree<T>::Insert(std::pair<int, T> kv) {
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

template <typename T>
bool AvlTree<T>::Delete(int key) {
  Node* curr = root;
  // Find the node to be deleted
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
  // Remove the node from the tree
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
int AvlTree<T>::GetSize() {
  return size;
}

// Visualizes the tree using GraphViz.
template <typename T>
void AvlTree<T>::Draw(std::string name) {
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
void AvlTree<T>::Balance(Node* curr) {
  while (curr != NULL) {
    // Keeps height information up to date.
    curr -> height = std::max(GetHeight(curr -> left),
                              GetHeight(curr -> right)) + 1;
    if (GetBalanceFactor(curr) == -2) {
      if (GetHeight(curr -> left -> right) >
          GetHeight(curr -> left -> left)) {
        RotateLeft(curr -> left);
      }
      RotateRight(curr);
    } else if (GetBalanceFactor(curr) == 2) {
      if (GetHeight(curr -> right -> left) >
          GetHeight(curr -> right -> right)) {
        RotateRight(curr -> right);
      }
      RotateLeft(curr);
    }
    curr = curr -> parent;
  }
}

template <typename T>
void AvlTree<T>::RotateLeft(Node* curr) {
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

template <typename T>
void AvlTree<T>::RotateRight(Node* curr) {
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

template <typename T>
int AvlTree<T>::GetBalanceFactor(Node* curr) {
  return GetHeight(curr -> right) - GetHeight(curr -> left);
}

template <typename T>
int AvlTree<T>::GetHeight(Node* curr) {
  if (curr == NULL) {
    return 0;
  } else {
    return curr -> height;
  }
}

template <typename T>
void AvlTree<T>::PrintToDot(Node* curr, std::ofstream& dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << curr -> key << "[label=\"" << curr -> key;
  dot_file << " (" << curr -> height << ", ";
  dot_file << std::showpos << GetBalanceFactor(curr);
  dot_file << std::noshowpos << ")\"];\n";
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
  // Tests insertions.
  AvlTree<std::string>* tree = new AvlTree<std::string>();
  tree -> Insert({10, ""});
  tree -> Insert({20, ""});
  tree -> Insert({30, ""});  // LROT
  tree -> Draw("avl_rot1");
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
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  std::string data;
  tree -> Find(4, &data);
  tree -> Draw("avl_rot2");

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
  tree2 -> Draw("avl2_before_deletion");
  tree2 -> Delete(24);  // RROT, LROT + RROT
  std::cout << "Tree size: " << tree2 -> GetSize() << std::endl;
  tree2 -> Draw("avl2_after_deletion");
  return 0;
}

// RandomUsername (Nikola Jovanovic)
// Treap
// Source: https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-1/

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

/*
  This implementation considers Split and Merge basic operations and derives
  Insert and Delete from them. It is possible to do it the other way around:
  Insert = Naive BST Insert + Binary Heap SiftUp using BST Tree Rotations
  Delete = Binary Heap SitfDown using BST Tree Rotations + trivial Delete
  Split = Insert a high priority node with a given key; take two subtrees
  Merge = Create a low priority node with a given key as root + SiftDown
*/

template <typename T>
class Treap {
 public:
  Treap();
  bool Find(int key, T* data);
  bool Insert(std::pair<int, T> kv);
  bool Delete(int key);
  int GetSize();
  void Draw(std::string name);
 private:
  struct Node {
    int key;
    double priority;
    T data;
    Node* left;
    Node* right;
    int subtree_size;
    explicit Node(std::pair<int, T> kv, double priority) {
      key = kv.first;
      data = kv.second;
      right = left = NULL;
      this -> priority = priority;
      subtree_size = 1;
    }
  };
  void Merge(Node** root, Node* left, Node* right);
  void Split(Node* root, Node** left, Node** right, int key);
  void UpdateSize(Node* curr);
  bool TreapInsert(Node** curr_ptr, Node* new_node);
  void TreapDelete(Node** curr_ptr, int key);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  std::mt19937 engine;
  std::uniform_real_distribution<> distribution;
};

template <typename T>
Treap<T>::Treap() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  engine = std::mt19937(seed);
  distribution = std::uniform_real_distribution<>(0, 1);
  root = NULL;
}

template <typename T>
bool Treap<T>::Find(int key, T* data) {
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
bool Treap<T>::Insert(std::pair<int, T> kv) {
  if (Find(kv.first, &kv.second)) {
    return false;
  }
  Node* new_node = new Node(kv, distribution(engine));
  if (root == NULL) {
    root = new_node;
    return true;
  }
  TreapInsert(&root, new_node);
  return true;
}

template <typename T>
bool Treap<T>::Delete(int key) {
  if (!Find(key, new T())) {
    return false;
  }
  TreapDelete(&root, key);
  return true;
}

template <typename T>
int Treap<T>::GetSize() {
  return root -> subtree_size;
}

// Visualizes the tree using GraphViz.
template <typename T>
void Treap<T>::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  PrintToDot(root, dot_file);
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

// Merges two treaps into a treap pointed at by root.
// All keys in the left treap need to be smaller than keys in the right treap.
template <typename T>
void Treap<T>::Merge(Node** root, Node* left, Node* right) {
  if (left == NULL) {
    *root = right;
  } else if (right == NULL) {
    *root = left;
  } else if (left -> priority > right -> priority) {
    Merge(&(left -> right), left -> right, right);
    *root = left;
  } else {
    Merge(&(right -> left), left, right -> left);
    *root = right;
  }
  UpdateSize(*root);
}

// Splits the treap rooted in root; left(right) should point to the root of
// the valid treap of nodes with keys smaller(larger) than key.
template <typename T>
void Treap<T>::Split(Node* root, Node** left, Node** right, int key) {
  if (root == NULL) {
    *left = *right = NULL;
    return;
  }
  if (key >= root -> key) {
    *left = root;
    Split(root -> right, &((*left) -> right), right, key);
  } else {
    *right = root;
    Split(root -> left, left, &((*right) -> left), key);
  }
  UpdateSize(root);
}

template <typename T>
void Treap<T>::UpdateSize(Node* curr) {
  if (curr != NULL) {
    int left_sz = (curr -> left) ? curr -> left -> subtree_size : 0;
    int right_sz = (curr -> right) ? curr -> right -> subtree_size : 0;
    curr -> subtree_size = left_sz + right_sz + 1;
  }
}

template <typename T>
bool Treap<T>::TreapInsert(Node** curr_ptr, Node* new_node) {
  if (*curr_ptr == NULL) {
    *curr_ptr = new_node;
  } else {
    Node* curr = *curr_ptr;
    if (curr -> priority < new_node -> priority) {
      Split(curr, &(new_node -> left), &(new_node -> right), new_node -> key);
      *curr_ptr = new_node;
    } else if (new_node -> key < curr -> key) {
      TreapInsert(&(curr -> left), new_node);
    } else {
      TreapInsert(&(curr -> right), new_node);
    }
  }
  UpdateSize(*curr_ptr);
}

template <typename T>
void Treap<T>::TreapDelete(Node** curr_ptr, int key) {
  if (*curr_ptr == NULL) {
    return;
  } else {
    Node* curr = *curr_ptr;
    if (curr -> key == key) {
      Merge(curr_ptr, curr -> left, curr -> right);
      delete(curr);
    } else if (key < curr -> key) {
      TreapDelete(&(curr -> left), key);
    } else {
      TreapDelete(&(curr -> right), key);
    }
  }
  UpdateSize(*curr_ptr);
}

template <typename T>
void Treap<T>::PrintToDot(Node* curr, std::ofstream &dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << std::fixed << std::setprecision(2);
  dot_file << curr -> key << "[label=\"" << curr -> data;
  dot_file << " (" << curr -> priority << ")\"];\n";
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
  Treap<std::string>* tree = new Treap<std::string>();
  tree -> Insert({8, "Eight"});
  tree -> Insert({3, "Three"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({14, "Fourteen"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({2, "Two"});
  tree -> Insert({11, "Eleven"});
  std::string data;
  tree -> Find(2, &data);
  std::cout << "Data with key 2: " << data << std::endl;
  tree -> Draw("treap_full");
  tree -> Delete(11);
  tree -> Delete(3);
  tree -> Delete(2);
  tree -> Delete(8);
  tree -> Draw("treap_del8");
  tree -> Delete(10);
  tree -> Delete(14);
  tree -> Delete(14);
  tree -> Draw("treap_empty");
  return 0;
}

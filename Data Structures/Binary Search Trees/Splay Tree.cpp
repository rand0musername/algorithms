// RandomUsername (Nikola Jovanovic)
// Splay Tree
// Source: http://digital.cs.usu.edu/~allan/DS/Notes/Ch22.pdf
//         http://cs.stackexchange.com/questions/1229/why-does-the-splay-tree-rotation-algorithm-take-into-account-both-the-parent-and

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

template <typename T>
class SplayTree {
 public:
  SplayTree();
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
    explicit Node(std::pair<int, T> kv, Node* parent) {
      key = kv.first;
      data = kv.second;
      right = left = NULL;
      this -> parent = parent;
    }
  };
  void RotateLeft(Node* curr);
  void RotateRight(Node* curr);
  void RotateOnParent(Node* pivot);
  void Zig(Node* curr);
  void ZigZig(Node* curr);
  void ZigZag(Node* curr);
  void Splay(Node* curr);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
};

template <typename T>
SplayTree<T>::SplayTree() {
  root = NULL;
  size = 0;
}

template <typename T>
bool SplayTree<T>::Find(int key, T* data) {
  if (root == NULL) {
    return false;
  }
  Node* curr = root;
  while (curr != NULL) {
    if (key < curr -> key) {
      curr = curr -> left;
    } else if (key > curr -> key) {
      curr = curr -> right;
    } else {
      *data = curr -> data;
      Splay(curr);
      return true;
    }
  }
  Splay(curr -> parent);
  return false;
}

template <typename T>
bool SplayTree<T>::Insert(std::pair<int, T> kv) {
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
        Splay(curr -> left);
        return true;
      }
      curr = curr -> left;
    } else {
      if (curr -> right == NULL) {
        curr -> right = new Node(kv, curr);
        size++;
        Splay(curr -> right);
        return true;
      }
      curr = curr -> right;
    }
  }
  Splay(curr);
  return false;
}

template <typename T>
bool SplayTree<T>::Delete(int key) {
  if (!Find({key, new T()})) {
    return false;
  }
  // We now want to delete the root.
  Node* to_del = root;
  if (root -> left == NULL && root -> right == NULL) {
    root = NULL;
  } else if (root -> right == NULL) {
    Node* pred = root -> left;
    while (pred -> right != NULL) {
      pred = pred -> right;
    }
    Splay(pred);
    // Node pred is now the root and has only to_del on its right.
  } else if (root -> left == NULL) {
    Node* succ = root -> right;
    while (succ -> left != NULL) {
      succ = succ -> left;
    }
    Splay(succ);
    // Node succ is now the root and has only to_del on its left.
  } else {
    // Both subtrees exist
    Node* left_subtree = root -> left;
    Node* succ = root -> right;
    while (succ -> left != NULL) {
      succ = succ -> left;
    }
    Splay(succ);
    // Node succ is now the root and to_del is its left child.
    succ -> left = left_subtree;
    left_subtree -> parent = succ;
  }
  delete to_del;
  size--;
  return true;
}

template <typename T>
int SplayTree<T>::GetSize() {
  return size;
}

// Visualizes the tree using GraphViz.
template <typename T>
void SplayTree<T>::Draw(std::string name) {
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
void SplayTree<T>::RotateLeft(Node* curr) {
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
}

template <typename T>
void SplayTree<T>::RotateRight(Node* curr) {
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
}

template <typename T>
void SplayTree<T>::RotateOnParent(Node* pivot) {
  if (pivot -> parent -> left == pivot) {
    RotateRight(pivot -> parent);
  } else {
    RotateLeft(pivot -> parent);
  }
}

template <typename T>
void SplayTree<T>::Zig(Node* curr) {
  RotateOnParent(curr);
}

template <typename T>
void SplayTree<T>::ZigZig(Node* curr) {
  RotateOnParent(curr -> parent);
  RotateOnParent(curr);
}

template <typename T>
void SplayTree<T>::ZigZag(Node* curr) {
  RotateOnParent(curr);
  RotateOnParent(curr);
}

template <typename T>
void SplayTree<T>::Splay(Node* curr) {
  while (curr != root) {
    if (curr -> parent == root) {
      Zig(curr);
    } else {
      Node* curr_p = curr -> parent;
      Node* curr_gp = curr_p -> parent;
      if (curr_p -> left == curr && curr_gp -> left == curr_p ||
          curr_p -> right == curr && curr_gp -> right == curr_p) {
        ZigZig(curr);
      } else {
        ZigZag(curr);
      }
    }
  }
}

template <typename T>
void SplayTree<T>::PrintToDot(Node* curr, std::ofstream &dot_file) {
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
  SplayTree<std::string>* tree = new SplayTree<std::string>();
  tree -> Insert({2, "Two"});
  tree -> Insert({5, "Five"});  // Zig
  tree -> Insert({3, "Three"});  // ZigZag
  tree -> Insert({8, "Eight"});  // ZigZig
  tree -> Insert({7, "Seven"});  // ZigZag
  tree -> Insert({1, "One"});  // ZigZig x 2
  tree -> Draw("splay_before_find");
  std::string data;
  tree -> Find(1, &data);
  tree -> Find(2, &data);  // ZigZag
  std::cout << "Data with key 2: " << data << std::endl;
  tree -> Draw("splay_after_find");
  tree -> Insert({4, "Four"});  // ZigZag + Zig
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  return 0;
}

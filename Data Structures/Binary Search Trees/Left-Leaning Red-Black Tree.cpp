// RandomUsername (Nikola Jovanovic)
// Left-Leaning Red-Black Tree
// Source: https://www.cs.princeton.edu/~rs/talks/LLRB/LLRB.pdf
//         http://www.cs.princeton.edu/~rs/talks/LLRB/Java/RedBlackBST.java

/*
  I couldn't find a working implementation of the Delete procedure for 2-3-4
  variant (all sources simply omit the details). I downloaded and ran the 
  official code that Sedgewick posted and it makes mistakes for fairly simple
  inputs. To be more precise, it creates trees with two consecutive red nodes.
  I had no other choice but to keep that implementation. However, the input
  that I am using to test this code in the main function generates invalid
  trees if allow_4nodes is true.

  Although I still don't have an explanation for this, I believe that me doing 
  dumb stuff is much more likely than Sedgewick doing dumb stuff, so if you 
  spot a mistake anywhere in my coding/reasoning and you have a valid 
  implementation of Delete please let me know. 
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

template <typename T>
class LlRbt {
 public:
  explicit LlRbt(bool allow_4nodes);
  bool Find(int key, T* data);
  bool Insert(std::pair<int, T> kv);
  bool Delete(int key);
  int GetSize();
  int Dummy();
  void Draw(std::string name);
 private:
  struct Node {
    int key;
    bool red;
    T data;
    Node* left;
    Node* right;
    explicit Node(std::pair<int, T> kv) {
      key = kv.first;
      data = kv.second;
      right = left = NULL;
      red = true;  // New nodes are red
    }
  };
  bool IsRed(Node* curr);
  Node* RotateLeft(Node* curr);
  Node* RotateRight(Node* curr);
  void FlipColors(Node* curr);
  Node* FixUp(Node* curr);
  Node* MoveRedLeft(Node* curr);
  Node* MoveRedRight(Node* curr);
  Node* LlRbtInsert(Node* curr, std::pair<int, T> kv);
  Node* LlRbtDeleteMin(Node* curr);
  Node* LlRbtDelete(Node* curr, int key);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
  bool allow_4nodes;
};

template <typename T>
LlRbt<T>::LlRbt(bool allow_4nodes) {
  root = NULL;
  size = 0;
  this -> allow_4nodes = allow_4nodes;
}

template <typename T>
bool LlRbt<T>::Find(int key, T* data) {
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
bool LlRbt<T>::Insert(std::pair<int, T> kv) {
  int size_before = size;
  root = LlRbtInsert(root, kv);
  root -> red = false;
  return size > size_before;
}

template <typename T>
bool LlRbt<T>::Delete(int key) {
  int size_before = size;
  if (!Find(key, new T())) {
    return false;
  }
  root = LlRbtDelete(root, key);
  root -> red = false;
  return size < size_before;
}

template <typename T>
int LlRbt<T>::GetSize() {
  return size;
}

// Visualizes the tree using GraphViz.
template <typename T>
void LlRbt<T>::Draw(std::string name) {
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
bool LlRbt<T>::IsRed(Node* curr) {
  return curr != NULL && curr -> red;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::RotateLeft(Node* curr) {
  Node* pivot = curr -> right;
  curr -> right = pivot -> left;
  pivot -> left = curr;
  std::swap(pivot -> red, curr -> red);
  return pivot;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::RotateRight(Node* curr) {
  Node* pivot = curr -> left;
  curr -> left = pivot -> right;
  pivot -> right = curr;
  std::swap(pivot -> red, curr -> red);
  return pivot;
}

template <typename T>
void LlRbt<T>::FlipColors(Node* curr) {
  curr -> red = !curr -> red;
  curr -> left -> red = !curr -> left -> red;
  curr -> right -> red = !curr -> right -> red;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::FixUp(Node* curr) {
  if (IsRed(curr -> right)) {
    curr = RotateLeft(curr);
  }
  if (IsRed(curr -> left) && IsRed(curr -> left -> left)) {
    curr = RotateRight(curr);
  }
  if (IsRed(curr -> left) && IsRed(curr -> right)) {
    FlipColors(curr);
  }
  return curr;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::MoveRedLeft(Node* curr) {
  FlipColors(curr);
  if (IsRed(curr -> right -> left)) {
    curr -> right = RotateRight(curr -> right);
    curr = RotateLeft(curr);
    FlipColors(curr);
  }
  return curr;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::MoveRedRight(Node* curr) {
  FlipColors(curr);
  if (IsRed(curr -> left -> left)) {
    curr = RotateRight(curr);
    FlipColors(curr);
  }
  return curr;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::LlRbtInsert(Node* curr,
                                               std::pair<int, T> kv) {
  if (curr == NULL) {
    size++;
    return new Node(kv);
  }
  if (allow_4nodes) {
    if (IsRed(curr -> left) && IsRed(curr -> right)) {
      FlipColors(curr);
    }
  }
  if (kv.first < curr -> key) {
    curr -> left = LlRbtInsert(curr -> left, kv);
  } else if (kv.first > curr -> key) {
    curr -> right = LlRbtInsert(curr -> right, kv);
  }
  if (IsRed(curr -> right)) {
    curr = RotateLeft(curr);
  }
  if (IsRed(curr -> left) && IsRed(curr -> left -> left)) {
    curr = RotateRight(curr);
  }
  if (!allow_4nodes) {
    if (IsRed(curr -> left) && IsRed(curr -> right)) {
      FlipColors(curr);
    }
  }
  return curr;
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::LlRbtDeleteMin(Node* curr) {
  if (curr -> left == NULL) {
    delete curr;
    size--;
    return NULL;
  }
  if (!IsRed(curr -> left) && !IsRed(curr -> left -> left)) {
    curr = MoveRedLeft(curr);
  }
  curr -> left = LlRbtDeleteMin(curr -> left);
  return FixUp(curr);
}

template <typename T>
typename LlRbt<T>::Node* LlRbt<T>::LlRbtDelete(Node* curr, int key) {
  if (key < curr -> key) {
    if (!IsRed(curr -> left) && !IsRed(curr -> left -> left)) {
      curr = MoveRedLeft(curr);
    }
    curr -> left = LlRbtDelete(curr -> left, key);
  } else {
    if (IsRed(curr -> left)) {
      curr = RotateRight(curr);
    }
    if (key == curr -> key && curr -> right == NULL) {
      delete curr;
      size--;
      return NULL;
    }
    if (!IsRed(curr -> right) && !IsRed(curr -> right -> left)) {
      curr = MoveRedRight(curr);
    }
    if (key == curr -> key) {
      Node* pred = curr -> right;
      while (pred -> left != NULL) {
        pred = pred -> left;
      }
      curr -> data = pred -> data;
      curr -> key = pred -> key;
      curr -> right = LlRbtDeleteMin(curr -> right);
    } else {
      curr -> right = LlRbtDelete(curr -> right, key);
    }
  }
  return FixUp(curr);
}

template <typename T>
void LlRbt<T>::PrintToDot(Node* curr, std::ofstream& dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << curr -> key << "[label=\"" << curr -> key << "\"";
  if (curr -> red) {
    dot_file << " color=red fontcolor=red";
  }
  dot_file << "];\n";
  if (curr -> left != NULL) {
    dot_file << curr -> key << " -> " << curr -> left -> key;
    if (curr -> left -> red) {
      dot_file << " [color = red]";
    }
    dot_file << "\n";
    PrintToDot(curr -> left, dot_file);
  } else {
    dot_file << "null_l_" << curr -> key << "[shape=point];\n";
    dot_file << curr -> key << " -> " << "null_l_" << curr -> key << "\n";
  }
  if (curr -> right != NULL) {
    dot_file << curr -> key << " -> " << curr -> right -> key << "\n";
    if (curr -> right -> red) {
      dot_file << " [color = red]";
    }
    PrintToDot(curr -> right, dot_file);
  } else {
    dot_file << "null_r_" << curr -> key << "[shape=point];\n";
    dot_file << curr -> key << " -> " << "null_r_" << curr -> key << "\n";
  }
}

int main() {
  LlRbt<std::string>* tree = new LlRbt<std::string>(false);
  tree -> Insert({7, "Seven"});
  tree -> Insert({3, "Three"});
  tree -> Insert({8, "Eight"});
  tree -> Insert({12, "Twelve"});
  tree -> Insert({13, "Thirteen"});
  tree -> Insert({11, "Eleven"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({9, "Nine"});
  tree -> Insert({2, "Two"});
  tree -> Insert({1, "One"});
  tree -> Insert({5, "Five"});
  tree -> Insert({14, "Fourteen"});
  tree -> Insert({6, "Six"});
  tree -> Insert({4, "Four"});
  tree -> Draw("llrbt_full");
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  std::cout << "Deletion: " << tree -> Delete(8) << std::endl;
  tree -> Draw("llrbt_del");
  std::string data;
  tree -> Find(4, &data);
  std::cout << "Data with key 4: " << data << std::endl;
  std::cout << "Failed insertion: " << tree -> Insert({1, "One"}) << std::endl;
  return 0;
}

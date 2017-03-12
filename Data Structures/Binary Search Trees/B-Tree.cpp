// RandomUsername (Nikola Jovanovic)
// B-Tree
// Source: CLRS Third Edition

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

template <typename T>
class BTree {
 public:
  explicit BTree(int t);
  bool Find(int key, T* data);
  bool Insert(std::pair<int, T> kv);
  bool Delete(int key);
  int GetSize();
  int GetHeight();
  void Draw(std::string name);
 private:
  static const int MAX_SIZE = 200;
  class Node {
   public:
    Node() {
      key_count = 0;  // Empty node
    }
    int LowerBound(int key);
    bool Add(std::pair<int, T> kv, Node* left, Node* right);
    void RemoveFirst();
    void RemoveLast();
    void DeleteKeyWithRightChild(int idx);
    int key_count;
    int keys[MAX_SIZE];
    T* data[MAX_SIZE];
    Node* children[MAX_SIZE];
    bool leaf;
  };
  void SplitChild(Node* curr, int child_index);
  Node* MergeChildren(Node* curr, int key_idx);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
  int height;
  int t;  // Minimal deg, deg: [t, 2t], nkeys: [t-1, 2t-1]
};

template <typename T>
BTree<T>::BTree(int t) {
  root = NULL;
  size = height = 0;
  this -> t = t;
}

template <typename T>
bool BTree<T>::Find(int key, T* data) {
  Node* curr = root;
  while (curr != NULL) {
    int idx = curr -> LowerBound(key);
    if (idx < curr -> key_count && key == curr -> keys[idx]) {
      data = curr -> data[idx];
      return true;
    } else {
      curr = curr -> children[idx];
    }
  }
  return false;
}

template <typename T>
bool BTree<T>::Insert(std::pair<int, T> kv) {
  if (root == NULL) {
    root = new Node();
    root -> leaf = true;
    root -> keys[0] = kv.first;
    root -> data[0] = new T();
    *(root -> data[0]) = kv.second;
    root -> children[0] = root -> children[1] = NULL;
    root -> key_count = 1;
    size = height = 1;
    return true;
  }
  // Is the root full?
  if (root -> key_count == 2 * t - 1) {
    Node* new_root = new Node();
    new_root -> leaf = false;
    new_root -> children[0] = root;
    SplitChild(new_root, 0);
    root = new_root;
    height++;
  }
  Node* curr = root;
  while (!curr -> leaf) {
    // Inner node, find the child to go to
    int idx = curr -> LowerBound(kv.first);
    if (curr -> children[idx] -> key_count == 2 * t - 1) {
      SplitChild(curr, idx);
      idx = curr -> LowerBound(kv.first);
    }
    curr = curr -> children[idx];
  }
  if (curr -> Add(kv, NULL, NULL)) {
    size++;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool BTree<T>::Delete(int key) {
  // Check for empty tree or node not inside.
  if (!Find(key, new T())) {
    return false;
  }
  // If a node has t-1 keys it's called "empty", with the
  // exception of the root.
  Node* curr = root;
  while (!curr -> leaf) {
    int idx = curr -> LowerBound(key);
    if (idx < curr -> key_count && key == curr -> keys[idx]) {
      // Case 2 (CLRS)
      // Inner node contains the key
      if (curr -> children[idx] -> key_count >= t) {
        // Case 2a (CLRS)
        // Find a leaf node that contains the predecessor
        Node* pred = curr -> children[idx];
        while (!pred -> leaf) {
          pred = pred -> children[pred -> key_count];
        }
        // Do the swap
        curr -> keys[idx] = pred -> keys[pred -> key_count - 1];
        *(curr -> data[idx]) = *(pred -> data[pred -> key_count - 1]);
        // Continue deleting recursively
        curr = curr -> children[idx];
        key = curr -> keys[idx];
      } else if (curr -> children[idx + 1] -> key_count >= t) {
        // Case 2b (CLRS)
        // Find a leaf node that contains the successor
        Node* succ = curr -> children[idx + 1];
        while (!succ -> leaf) {
          succ = succ -> children[0];
        }
        // Do the swap
        curr -> keys[idx] = succ -> keys[0];
        *(curr -> data[idx]) = *(succ -> data[0]);
        // Continue deleting recursively
        curr = curr -> children[idx + 1];
        key = curr -> keys[idx];
      } else {
        // Case 2c (CLRS)
        // Both kids have t-1 keys, merge them
        curr = MergeChildren(curr, idx);
      }
    } else {
      // Case 3 (CLRS)
      // Inner node does not contain the key (idx = first larger)
      Node* key_node = curr -> children[idx];
      if (key_node -> key_count == t - 1) {
        if (idx > 0 && curr -> children[idx - 1] -> key_count >= t) {
          // Case 3a1 (CLRS)
          Node* l_sib = curr -> children[idx - 1];
          key_node -> Add({curr -> keys[idx - 1], *(curr -> data[idx - 1])},
                          key_node -> children[0],
                          l_sib -> children[l_sib -> key_count]);
          curr -> keys[idx - 1] = l_sib -> keys[l_sib -> key_count - 1];
          *(curr -> data[idx - 1]) = *(l_sib -> data[l_sib -> key_count - 1]);
          l_sib -> RemoveLast();
          curr = key_node;
        } else if (idx < curr -> key_count &&
                   curr -> children[idx + 1] -> key_count >= t) {
          // Case 3a2 (CLRS)
          Node* r_sib = curr -> children[idx + 1];
          key_node -> Add({curr -> keys[idx], *(curr -> data[idx])},
                          key_node -> children[key_node -> key_count],
                          r_sib -> children[0]);
          curr -> keys[idx] = r_sib -> keys[0];
          *(curr -> data[idx]) = *(r_sib -> data[0]);
          r_sib -> RemoveFirst();
          curr = key_node;
        } else {
          // Case 3b (CLRS)
          // Merge
          if (idx > 0) {
            curr = MergeChildren(curr, idx - 1);
          } else {
            curr = MergeChildren(curr, idx);
          }
        }
      } else {
        curr = key_node;
      }
    }
  }
  // We are currently in the leaf that definitely has our key
  curr -> DeleteKeyWithRightChild(curr -> LowerBound(key));
  size--;
  if (size == 0) {
    height = 0;
    root = NULL;  // Empty tree
  }
  return true;
}

template <typename T>
int BTree<T>::GetSize() {
  return size;
}

template <typename T>
int BTree<T>::GetHeight() {
  return height;
}

// Visualizes the tree using GraphViz.
template <typename T>
void BTree<T>::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  dot_file << "node [shape = record,height=.1];\n";
  PrintToDot(root, dot_file);
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

template <typename T>
int BTree<T>::Node::LowerBound(int key) {
  // Return first larger or equal
  for (int idx = key_count - 1; idx >= 0; idx--) {
    if (keys[idx] < key) {
      return idx + 1;
    }
  }
  return 0;
}

template <typename T>
bool BTree<T>::Node::Add(std::pair<int, T> kv, Node* left, Node* right) {
  int idx = LowerBound(kv.first);
  if (idx < key_count && keys[idx] == kv.first) {
    return false;
  }
  for (int i = key_count - 1; i >= idx; i--) {
    keys[i + 1] = keys[i];
    data[i + 1] = data[i];
    children[i + 2] = children[i + 1];
  }
  keys[idx] = kv.first;
  data[idx] = new T();
  *data[idx] = kv.second;
  children[idx] = left;
  children[idx+1] = right;
  // Children are all null since this is a leaf node
  key_count++;
  return true;
}

template <typename T>
void BTree<T>::Node::RemoveFirst() {
  children[0] = children[1];
  DeleteKeyWithRightChild(0);
}

template <typename T>
void BTree<T>::Node::RemoveLast() {
  keys[key_count - 1] = 0;
  delete data[key_count - 1];
  children[key_count] = NULL;
  key_count--;
}

template <typename T>
void BTree<T>::Node::DeleteKeyWithRightChild(int idx) {
  delete data[idx];
  for (int i = idx; i <= key_count - 2; i++) {
    keys[i] = keys[i + 1];
    data[i] = data[i + 1];
    children[i + 1] = children[i + 2];
  }
  children[key_count] = NULL;
  keys[key_count - 1] = 0;
  key_count--;
}

template <typename T>
void BTree<T>::SplitChild(Node* curr, int child_index) {
  // Node curr is not full, child is full, 2t-1 keys
  Node* child = curr -> children[child_index];
  int key_up = child -> keys[t - 1];
  T data_up = *(child -> data[t - 1]);
  // Prepare left and right
  Node* right = new Node();
  right -> leaf = child -> leaf;
  for (int idx = t; idx <= 2 * t - 2; idx++) {
    right -> Add({child -> keys[idx], *(child -> data[idx])},
                 child -> children[idx], child -> children[idx+1]);
  }
  for (int idx = 2*t - 2; idx >= t; idx--) {
    child -> RemoveLast();
  }
  child -> RemoveLast();
  curr -> Add({key_up, data_up}, child, right);
}

template <typename T>
typename BTree<T>::Node* BTree<T>::MergeChildren(Node* curr, int key_idx) {
  Node* left = curr -> children[key_idx];
  Node* right = curr -> children[key_idx + 1];
  left -> Add({curr -> keys[key_idx], *(curr -> data[key_idx])},
                       left -> children[t - 1], right -> children[0]);
  for (int i = 0; i <= t - 2; i++) {
    left -> Add({right -> keys[i], *(right -> data[i])},
                       right -> children[i], right -> children[i+1]);
  }
  for (int i = t - 2; i >= 0; i--) {
    right -> RemoveLast();
  }
  delete right;
  curr -> DeleteKeyWithRightChild(key_idx);
  // Did root become empty?
  if (curr == root && curr -> key_count == 0) {
    root = curr -> children[0];
    delete curr;
    height--;
    return root;
  } else {
    return curr -> children[key_idx];
  }
}

template <typename T>
void BTree<T>::PrintToDot(Node* curr, std::ofstream& dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << "n" << curr -> keys[0] << "[label=\"";
  for (int i = 0; i < curr -> key_count; i++) {
    dot_file << "<c" << i << ">|" << curr -> keys[i] << "|";
  }
  dot_file << "<c" << curr -> key_count << ">\"];\n";
  for (int i = 0; i <= curr -> key_count; i++) {
    dot_file << "n" << curr -> keys[0] <<": c" << i << " -> ";
    if (curr -> children[i] != NULL) {
      dot_file << "n" << curr -> children[i] -> keys[0] << "\n";
    } else {
      dot_file << "null_" << curr -> keys[0] << "_" << i << "\n";
      dot_file << "null_" << curr -> keys[0] << "_" << i;
      dot_file << "[shape=point];\n";
    }
    PrintToDot(curr -> children[i], dot_file);
  }
}

int main() {
  BTree<std::string>* tree = new BTree<std::string>(2);
  tree -> Insert({9, "Nine"});
  tree -> Insert({4, "Four"});
  tree -> Insert({10, "Ten"});
  tree -> Insert({14, "Fourteen"});
  tree -> Insert({13, "Thirteen"});
  tree -> Insert({1, "One"});
  tree -> Insert({6, "Six"});
  tree -> Insert({7, "Seven"});
  tree -> Insert({5, "Five"});
  tree -> Insert({2, "Two"});
  tree -> Insert({3, "Three"});
  tree -> Insert({20, "Twenty"});
  tree -> Insert({8, "Eight"});
  tree -> Draw("btree_full");
  tree -> Delete(1);
  tree -> Delete(2);
  tree -> Delete(3);  // 3BR
  tree -> Delete(9);  // 2C + 2A
  tree -> Delete(13);  // 2B
  tree -> Delete(20);  // 3BL
  tree -> Delete(7);  // 3AL
  tree -> Delete(6);  // 3AR
  tree -> Delete(5);
  tree -> Delete(4);
  tree -> Delete(10);
  tree -> Delete(8);
  tree -> Delete(8);  // Repeated
  tree -> Delete(14);  // Delete last node
  tree -> Delete(8);  // On empty
  tree -> Insert({9, "Nine"});
  std::cout << "Tree height: " << tree -> GetHeight() << std::endl;
  std::cout << "Tree size: " << tree -> GetSize() << std::endl;
  tree -> Draw("btree_end");
  return 0;
}

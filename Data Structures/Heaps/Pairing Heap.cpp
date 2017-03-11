// RandomUsername (Nikola Jovanovic)
// Pairing Heap
// Source: http://www.cise.ufl.edu/~sahni/dsaaj/enrich/c13/pairing.htm

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

struct Node {
  Node* left;
  Node* right;
  Node* first_child;
  int key;
  explicit Node(int key) {
    this -> key = key;
    this -> first_child = NULL;
    this -> left = this -> right = NULL;
  }
};

class PairingHeap {
 public:
  PairingHeap();
  Node* FindMin();
  void DeleteMin();
  void Insert(Node* curr);
  void DecreaseKey(Node* curr, int new_key);
  void Merge(PairingHeap* h);
  int GetSize();
  void Draw(std::string name);
 private:
  explicit PairingHeap(Node* root);
  static PairingHeap* TwoPass(Node* head);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* root;
  int size;
};

PairingHeap::PairingHeap() {
  size = 0;
  root = NULL;
}

Node* PairingHeap::FindMin() {
  return root;
}

void PairingHeap::DeleteMin() {
  Node* child = root -> first_child;
  delete root;
  PairingHeap* new_tree = TwoPass(child);
  root = new_tree -> root;
  delete new_tree;
  size--;
}

void PairingHeap::Insert(Node* curr) {
  PairingHeap* unit_heap = new PairingHeap(curr);
  Merge(unit_heap);
  delete unit_heap;
  size++;
}

void PairingHeap::DecreaseKey(Node* curr, int new_key) {
  // Remove curr from the heap
  if (curr -> right != NULL) {
    curr -> right -> left = curr -> left;
  }
  if (curr -> left != NULL) {
    if (curr -> left -> first_child == curr) {
      // Node curr is the first child, left is its parent in this case
      curr -> left -> first_child = curr -> right;
    } else {
      curr -> left -> right = curr -> right;
    }
  }
  // Reattach curr to the heap
  curr -> key = new_key;
  curr -> left = curr -> right = NULL;
  PairingHeap* subtree_heap = new PairingHeap(curr);
  Merge(subtree_heap);
  delete subtree_heap;
}

// All temporary heaps will have size = 0,
// insertion and deletion functions will maintain the correct size.
void PairingHeap::Merge(PairingHeap* other) {
  Node* other_root = other -> root;
  if (root == NULL) {
    root = other_root;
    size = other -> size;
    return;
  }
  if (other_root != NULL) {
    if (root -> key < other_root -> key) {
      other_root -> left = root;
      other_root -> right = root -> first_child;
      if (root -> first_child != NULL) {
        root -> first_child -> left = other_root;
      }
      root -> first_child = other_root;
    } else {
      root -> left = other_root;
      root -> right = other_root -> first_child;
      if (other_root -> first_child != NULL) {
        other_root -> first_child -> left = root;
      }
      other_root -> first_child = root;
      root = other_root;
    }
    size += other -> size;
  }
}

int PairingHeap::GetSize() {
  return size;
}

// Visualizes the heap using GraphViz.
void PairingHeap::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  PrintToDot(root, dot_file);
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

PairingHeap::PairingHeap(Node* root) {
  size = 0;  // Temporary heap
  this -> root = root;
}

// Multipass is an alternative, but performs worse in practice
PairingHeap* PairingHeap::TwoPass(Node* head) {
  PairingHeap* left_tree = new PairingHeap(head);
  if (head == NULL || head -> right == NULL) {
    return left_tree;
  }
  Node* next = head -> right;
  PairingHeap* right_tree = TwoPass(next -> right);
  next -> left = next -> right = NULL;
  head -> left = head -> right = NULL;
  PairingHeap* next_tree = new PairingHeap(next);
  left_tree -> Merge(next_tree);
  right_tree -> Merge(left_tree);
  delete left_tree;
  delete next_tree;
  return right_tree;
}

void PairingHeap::PrintToDot(Node* curr, std::ofstream &dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << curr -> key << "[label=\"" << curr -> key << "\"];\n";
  Node* child = curr -> first_child;
  if (child == NULL) {
    dot_file << "null_l_" << curr -> key << "[shape=point];\n";
    dot_file << curr -> key << " -> " << "null_l_" << curr -> key << "\n";
  } else {
    while (child != NULL) {
      PrintToDot(child, dot_file);
      dot_file << curr -> key << " -> " << child -> key << "\n";
      child = child -> right;
    }
  }
}

int main() {
  PairingHeap* heap = new PairingHeap();
  heap -> Insert(new Node(2));
  heap -> Insert(new Node(4));
  heap -> Insert(new Node(6));
  heap -> Insert(new Node(8));
  heap -> Insert(new Node(17));
  heap -> Insert(new Node(12));
  heap -> Insert(new Node(10));
  heap -> Insert(new Node(5));
  heap -> Insert(new Node(3));
  heap -> Insert(new Node(9));
  heap -> Insert(new Node(15));
  heap -> Insert(new Node(19));
  Node* sev = new Node(7);
  heap -> Insert(sev);
  std::cout << "Size: " << heap -> GetSize();
  Node* min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("heap_full");
  heap -> DecreaseKey(sev, 1);
  std::cout << "Size: " << heap -> GetSize();
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("heap_dec");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize();
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("heap_del");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize();
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("heap_end");
  return 0;
}

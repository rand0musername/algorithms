// RandomUsername (Nikola Jovanovic)
// Fibonacci Heap
// Source: CLRS, Third Edition

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

struct Node {
  Node* left;
  Node* right;
  Node* parent;
  Node* first_child;
  int key;
  int degree;
  bool marked;
  explicit Node(int key) {
    this -> key = key;
    this -> degree = 0;
    this -> parent = this -> first_child = NULL;
    this -> left = this -> right = this;
    this -> marked = false;
  }
};

class FibonacciHeap {
 public:
  FibonacciHeap();
  Node* FindMin();
  void DeleteMin();
  void Insert(Node* curr);
  void DecreaseKey(Node* curr, int new_key);
  void Merge(FibonacciHeap* h);
  int GetSize();
  void Draw(std::string name);
 private:
  void LinkRootNodes(Node* top, Node* bottom);
  void MakeRootNode(Node* curr);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* min_node;
  int size;
};

FibonacciHeap::FibonacciHeap() {
  size = 0;
  min_node = NULL;
}

Node* FibonacciHeap::FindMin() {
  return min_node;
}

void FibonacciHeap::DeleteMin() {
  if (size == 0) {
    return;
  }
  if (size == 1) {
    delete min_node;
    min_node = NULL;
    size = 0;
    return;
  }
  Node* child = min_node -> first_child;
  int deg = min_node -> degree;
  for (int i = 0; i < deg; i++) {
    Node* next = child -> right;
    MakeRootNode(child);
    child = next;
  }
  int D = 2 * ceil(log2(size));
  Node* tmp[D];
  for (int i = 0; i < D; i++) {
    tmp[i] = NULL;
  }
  Node* curr = min_node -> right;
  while (curr != min_node) {
    Node* next = curr -> right;
    int deg = curr -> degree;
    while (tmp[deg] != NULL) {
      Node* other = tmp[deg];
      if (curr -> key > other -> key) {
        std::swap(curr, other);
      }
      LinkRootNodes(curr, other);
      tmp[deg++] = NULL;
    }
    tmp[deg] = curr;
    curr = next;
  }
  delete min_node;
  // Rebuild the heap
  size--;
  Node* first;
  Node* last;
  first = last = min_node = NULL;
  for (int i = 0; i < D; i++) {
    if (tmp[i] != NULL) {
      if (first == NULL) {
        min_node = first = last = tmp[i];
      } else {
        if (tmp[i] -> key < min_node -> key) {
          min_node = tmp[i];
        }
        last -> right = tmp[i];
        tmp[i] -> left = last;
        last = tmp[i];
      }
    }
  }
  if (first != NULL) {
    last -> right = first;
    first -> left = last;
  }
}

void FibonacciHeap::Insert(Node* curr) {
  FibonacciHeap* unit_heap = new FibonacciHeap();
  unit_heap -> min_node = curr;
  unit_heap -> size = 1;
  Merge(unit_heap);
  delete unit_heap;
}

void FibonacciHeap::DecreaseKey(Node* curr, int new_key) {
  curr -> key = new_key;
  Node* parent = curr -> parent;
  if (parent != NULL && curr -> key < parent -> key) {
    // Cut this child and update min node
    MakeRootNode(curr);
    curr -> marked = false;
    if (curr -> key < min_node -> key) {
      min_node = curr;
    }
    // Do a cascading cut
    curr = parent;
    while (curr != NULL && curr -> marked) {
      parent = curr -> parent;
      MakeRootNode(curr);
      curr -> marked = false;
      curr = parent;
    }
    if (curr != NULL && curr -> parent != NULL) {
      curr -> marked = true;
    }
  } else if (parent == NULL && curr -> key < min_node -> key) {
    min_node = curr;
  }
}

void FibonacciHeap::Merge(FibonacciHeap* other) {
  if (other -> size == 0) {
    return;
  }
  if (this -> size == 0) {
    this -> min_node = other -> min_node;
  } else {
    Node* this_right = this -> min_node -> right;
    Node* other_left = other -> min_node -> left;
    this -> min_node -> right = other -> min_node;
    other -> min_node -> left = this -> min_node;
    this_right -> left = other_left;
    other_left -> right = this_right;
  }
  this -> size += other -> size;
}

int FibonacciHeap::GetSize() {
  return size;
}

// Visualizes the heap using GraphViz.
void FibonacciHeap::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  Node* root = min_node;
  if (root != NULL) {
    do {
      PrintToDot(root, dot_file);
      root = root -> right;
    } while (root != min_node);
  }
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

void FibonacciHeap::LinkRootNodes(Node* top, Node* bottom) {
  bottom -> left -> right = bottom -> right;
  bottom -> right -> left = bottom -> left;
  Node* child = top -> first_child;
  bottom -> parent = top;
  top -> first_child = bottom;
  bottom -> left = bottom -> right = NULL;
  if (child != NULL) {
    bottom -> right = child;
    child -> left = bottom;
  }
  top -> degree++;
  top -> marked = false;
}

void FibonacciHeap::MakeRootNode(Node* curr) {
  if (curr -> left != NULL) {
    curr -> left -> right = curr -> right;
  }
  if (curr -> right != NULL) {
    curr -> right -> left = curr -> left;
  }
  if (curr -> parent != NULL) {
    if (curr -> parent -> first_child == curr) {
      curr -> parent -> first_child = curr -> right;
    }
    curr -> parent -> degree--;
  }
  curr -> parent = NULL;
  Node* min_right = min_node -> right;
  curr -> right = min_right;
  min_right -> left = curr;
  curr -> left = min_node;
  min_node -> right = curr;
}

void FibonacciHeap::PrintToDot(Node* curr, std::ofstream& dot_file) {
  if (curr == NULL) {
    return;
  }
  dot_file << curr -> key << "[label=\"" << curr -> key << "\"";
  if (curr -> marked) {
    dot_file << " color=red fontcolor=red";
  }
  dot_file << "];\n";
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
  FibonacciHeap* heap = new FibonacciHeap();
  heap -> Insert(new Node(4));
  heap -> DeleteMin();
  heap -> DeleteMin();
  heap -> Insert(new Node(4));
  heap -> Insert(new Node(5));
  heap -> Insert(new Node(16));
  heap -> Insert(new Node(26));
  heap -> Insert(new Node(7));
  Node* n11 = new Node(11); heap -> Insert(n11);
  Node* n17 = new Node(17); heap -> Insert(n17);
  Node* n12 = new Node(12); heap -> Insert(n12);
  heap -> Insert(new Node(10));
  Node* n99 = new Node(99); heap -> Insert(n99);
  heap -> Insert(new Node(33));
  heap -> Insert(new Node(95));
  heap -> Insert(new Node(14));
  heap -> Insert(new Node(6));
  heap -> Insert(new Node(9));
  heap -> Insert(new Node(96));
  heap -> Insert(new Node(19));
  heap -> Insert(new Node(8));
  heap -> Draw("fibheap_full");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize();
  Node* min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << " Min: " << min_node -> key << std::endl;
  } else {
    std::cout << " Empty" << std::endl;
  }
  heap -> Draw("fibheap_del");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize();
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << " Min: " << min_node -> key << std::endl;
  } else {
    std::cout << " Empty" << std::endl;
  }
  heap -> Draw("fibheap_del2");
  heap -> DecreaseKey(n11, 3);
  heap -> DecreaseKey(n99, 0);
  heap -> DecreaseKey(n17, 2);
  heap -> DecreaseKey(n12, 1);  // Cascade
  heap -> Draw("fibheap_dec");
  heap -> DeleteMin();
  heap -> DeleteMin();
  heap -> DeleteMin();
  heap -> DeleteMin();
  heap -> DeleteMin();
  heap -> Draw("fibheap_end");
  return 0;
}

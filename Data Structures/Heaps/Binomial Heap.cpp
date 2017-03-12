// RandomUsername (Nikola Jovanovic)
// Binomial Heap
// Source: CLRS, Second Edition

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
  explicit Node(int key) {
    this -> key = key;
    this -> degree = 0;
    this -> parent = this -> first_child = NULL;
    this -> left = this -> right = NULL;
  }
};

class BinomialHeap {
 public:
  BinomialHeap();
  Node* FindMin();
  void DeleteMin();
  void Insert(Node* curr);
  void DecreaseKey(Node* curr, int new_key);
  void Merge(BinomialHeap* h);
  int GetSize();
  void Draw(std::string name);
 private:
  Node* MergeTrees(Node* bottom, Node* top);
  Node* AttachTail(Node* tail, Node* new_node);
  void PrintToDot(Node* curr, std::ofstream& dot_file);
  Node* head;
  int size;
};

BinomialHeap::BinomialHeap() {
  size = 0;
  head = NULL;
}

Node* BinomialHeap::FindMin() {
  Node* curr = head;
  Node* min_node = curr;
  while (curr != NULL) {
    if (curr -> key < min_node -> key) {
      min_node = curr;
    }
    curr = curr -> right;
  }
  return min_node;
}

void BinomialHeap::DeleteMin() {
  Node* min_node = FindMin();
  // Remove the min node
  if (min_node == head) {
    head = min_node -> right;
  } else {
    min_node -> left -> right = min_node -> right;
    if (min_node -> right != NULL) {
      min_node -> right -> left = min_node -> left;
    }
  }
  if (min_node -> degree > 0) {
    // Reverse its child list
    Node* first = min_node -> first_child;
    Node* second = first -> right;
    Node* third = NULL;
    if (second != NULL) {
      third = second -> right;
    }
    first -> right = NULL;
    while (second != NULL) {
      second -> right = first;
      first -> left = second;
      first = second;
      second = third;
      if (third != NULL) {
        third = third -> right;
      }
    }
    first -> left = NULL;
    // Delete the min node and merge two heaps
    delete min_node;
    size--;
    BinomialHeap* child_heap = new BinomialHeap();
    child_heap -> head = first;
    child_heap -> size = (1 << min_node -> degree) - 1;
    size -= child_heap -> size;
    // Leaving parent pointers dirty is acceptible
    Merge(child_heap);
    delete child_heap;
  } else {
    delete min_node;
    size--;
  }
}

void BinomialHeap::Insert(Node* curr) {
  BinomialHeap* unit_heap = new BinomialHeap();
  unit_heap -> head = curr;
  unit_heap -> size = 1;
  Merge(unit_heap);
  delete unit_heap;
}

void BinomialHeap::DecreaseKey(Node* curr, int new_key) {
  curr -> key = new_key;
  while (curr -> parent != NULL && curr -> key < curr -> parent -> key) {
    std::swap(curr -> key, curr -> parent -> key);
    curr = curr -> parent;
  }
}

void BinomialHeap::Merge(BinomialHeap* other) {
  Node* tail = NULL;
  Node* nodes[3];
  nodes[0] = head;
  nodes[1] = other -> head;
  nodes[2] = NULL;  // Carry
  Node* active[3];
  int num_nodes;
  while (nodes[0] != NULL || nodes[1] != NULL || nodes[2] != NULL) {
    // Find the min degree
    int min_deg = INT_MAX;
    for (int i = 0; i < 3; i++) {
      if (nodes[i] != NULL) {
        min_deg = std::min(min_deg, nodes[i] -> degree);
      }
    }
    // Find and merge nodes with min degree
    num_nodes = 0;
    for (int i = 0; i < 3; i++) {
      if (nodes[i] != NULL && nodes[i] -> degree == min_deg) {
        active[num_nodes++] = nodes[i];
        nodes[i] = nodes[i] -> right;
      }
    }
    if (num_nodes == 1) {
      tail = AttachTail(tail, active[0]);
    } else if (num_nodes == 2) {
      if (active[0] -> key < active[1] -> key) {
        nodes[2] = MergeTrees(active[1], active[0]);
      } else {
        nodes[2] = MergeTrees(active[0], active[1]);
      }
    } else {
      tail = AttachTail(tail, active[0]);
      if (active[1] -> key < active[2] -> key) {
        nodes[2] = MergeTrees(active[2], active[1]);
      } else {
        nodes[2] = MergeTrees(active[1], active[2]);
      }
    }
  }
  head = tail;
  while (head -> left != NULL) {
    head = head -> left;
  }
  size += other -> size;
}

int BinomialHeap::GetSize() {
  return size;
}

// Visualizes the heap using GraphViz.
void BinomialHeap::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  Node* root = head;
  while (root != NULL) {
    PrintToDot(root, dot_file);
    root = root -> right;
  }
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

Node* BinomialHeap::MergeTrees(Node* bottom, Node* top) {
  bottom -> parent = top;
  bottom -> right = top -> first_child;
  top -> first_child = bottom;
  top -> degree++;
  bottom -> left = NULL;
  top -> left = top -> right = NULL;
  return top;
}

Node* BinomialHeap::AttachTail(Node* tail, Node* new_node) {
  if (tail == NULL) {
    tail = new_node;
    tail -> left = tail -> right = NULL;
  } else {
    tail -> right = new_node;
    new_node -> left = tail;
    tail = tail -> right;
  }
  return tail;
}

void BinomialHeap::PrintToDot(Node* curr, std::ofstream& dot_file) {
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
  BinomialHeap* heap = new BinomialHeap();
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
  std::cout << "Size: " << heap -> GetSize() << std::endl;
  Node* min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("bnmheap_full");
  heap -> DecreaseKey(sev, 1);
  std::cout << "Size: " << heap -> GetSize() << std::endl;
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("bnmheap_dec");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize() << std::endl;
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("bnmheap_del");
  heap -> DeleteMin();
  std::cout << "Size: " << heap -> GetSize() << std::endl;
  min_node = heap -> FindMin();
  if (min_node != NULL) {
    std::cout << "Min: " << min_node -> key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("bnmheap_end");
  return 0;
}

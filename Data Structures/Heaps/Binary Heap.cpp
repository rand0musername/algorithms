// RandomUsername (Nikola Jovanovic)
// Binary Heap

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

class BinaryHeap {
 public:
  BinaryHeap();
  BinaryHeap(int* arr, int arr_size);
  int* FindMin();
  void DeleteMin();
  void Insert(int key);
  void DecreaseKey(int idx, int new_key);
  void Merge(BinaryHeap* h);
  int GetSize();
  void Draw(std::string name);
 private:
  static const int MAX_SIZE = 1000;
  void SiftDown(int idx);
  void SiftUp(int idx);
  void PrintToDot(int idx, std::ofstream& dot_file);
  int keys[MAX_SIZE];
  int size;
};

BinaryHeap::BinaryHeap() {
  size = 0;
}

BinaryHeap::BinaryHeap(int* arr, int arr_size) {
  size = arr_size;
  std::copy(arr, arr + size, keys + 1);
  for (int i = size / 2; i >= 1; i--) {
    SiftDown(i);
  }
}

int* BinaryHeap::FindMin() {
  if (size == 0) {
    return NULL;
  }
  return &keys[1];
}

void BinaryHeap::DeleteMin() {
  keys[1] = keys[size--];
  SiftDown(1);
}

void BinaryHeap::Insert(int key) {
  keys[++size] = key;
  SiftUp(size);
}

void BinaryHeap::DecreaseKey(int idx, int new_key) {
  keys[idx] = new_key;
  SiftUp(idx);
}

void BinaryHeap::Merge(BinaryHeap* other) {
  std::copy(other -> keys + 1, other -> keys + other -> size + 1,
            keys + size + 1);
  size += other -> size;
  for (int i = size / 2; i >= 1; i--) {
    SiftDown(i);
  }
}

int BinaryHeap::GetSize() {
  return size;
}

// Visualizes the heap using GraphViz.
void BinaryHeap::Draw(std::string name) {
  std::ofstream dot_file;
  dot_file.open(name + ".dot");
  dot_file << "digraph{\n";
  PrintToDot(1, dot_file);
  dot_file << "}\n";
  dot_file.close();
  std::string command = "dot -Tpng " + name + ".dot -o " + name + ".png";
  system(command.c_str());
}

void BinaryHeap::SiftDown(int idx) {
  while (idx <= size) {
    int swap_idx = idx;
    if (2 * idx <= size && keys[2 * idx] < keys[swap_idx]) {
      swap_idx = 2 * idx;
    }
    if (2 * idx + 1 <= size && keys[2 * idx + 1] < keys[swap_idx]) {
      swap_idx = 2 * idx + 1;
    }
    if (swap_idx != idx) {
      std::swap(keys[idx], keys[swap_idx]);
      idx = swap_idx;
    } else {
      return;
    }
  }
}

void BinaryHeap::SiftUp(int idx) {
  while (idx > 1) {
    if (keys[idx / 2] > keys[idx]) {
      std::swap(keys[idx], keys[idx / 2]);
      idx /= 2;
    } else {
      return;
    }
  }
}

void BinaryHeap::PrintToDot(int idx, std::ofstream& dot_file) {
  dot_file << keys[idx] << "[label=\"" << keys[idx] << "\"];\n";
  if (2 * idx <= size) {
    dot_file << keys[idx] << " -> " << keys[2 * idx] << "\n";
    PrintToDot(2 * idx, dot_file);
  } else {
    dot_file << "null_l_" << keys[idx] << "[shape=point];\n";
    dot_file << keys[idx] << " -> " << "null_l_" << keys[idx] << "\n";
  }
  if (2 * idx + 1 <= size) {
    dot_file << keys[idx] << " -> " << keys[2 * idx + 1] << "\n";
    PrintToDot(2 * idx + 1, dot_file);
  } else {
    dot_file << "null_r_" << keys[idx] << "[shape=point];\n";
    dot_file << keys[idx] << " -> " << "null_r_" << keys[idx] << "\n";
  }
}

int main() {
  BinaryHeap* heap = new BinaryHeap();
  heap -> Insert(5);
  heap -> Insert(2);
  heap -> Insert(4);
  heap -> Insert(3);
  heap -> Insert(6);
  heap -> Draw("heap_full");
  heap -> DeleteMin();
  heap -> DecreaseKey(2, 1);
  int* min_key = heap -> FindMin();
  if (min_key != NULL) {
    std::cout << "Min: " << *min_key << std::endl;
  } else {
    std::cout << "Empty" << std::endl;
  }
  heap -> Draw("heap_end");
  std::cout << "Size: " << heap -> GetSize() << std::endl;
  return 0;
}

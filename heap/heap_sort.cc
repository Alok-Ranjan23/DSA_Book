// Min-Heap Descending Order

#include <iostream>
#include <vector>

using namespace std;

class Heap {
  vector<int> arr_;

  int parent(int i) { return (i - 1) / 2; }
  void minheapify(int i, int n) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n && arr_[left]  < arr_[smallest]) smallest = left;
    if (right < n && arr_[right] < arr_[smallest]) smallest = right;
    if (smallest == i) return;
    swap(arr_[i], arr_[smallest]);
    minheapify(smallest,n);
  }

public:
  Heap(vector<int>& a) : arr_(a) {
    int n = arr_.size();
    for (int i = n / 2 - 1; i >= 0; --i)
      minheapify(i,n);
  }

  size_t size() const { return arr_.size(); }

  int top() const {
    if (arr_.empty()) return -1;   // sentinel for empty
    return arr_[0];
  }

  void push(int x) {
    arr_.push_back(x);
    int i = (int)arr_.size() - 1;
    while (i != 0 && arr_[parent(i)] > arr_[i]) {
      swap(arr_[i], arr_[parent(i)]);
      i = parent(i);
    }
  }

  int pop() {
    if (arr_.empty()) return -1;
    int root = arr_[0];
    arr_[0] = arr_.back();
    arr_.pop_back();
    int n = arr_.size();
    if (!arr_.empty()) minheapify(0,n);
    return root;
  }

  // 1 4 2 6 8 3 
  void sort() {
    int n = arr_.size();
    for(int i=n-1;i>=1;--i) {
     swap(arr_[i],arr_[0]); 
     minheapify(0,i);
    }
  }

  void print() const {
    for (int v : arr_) cout << v << ' ';
    cout << '\n';
  }
};

int main() {
    vector<int> arr{4, 8, 2, 6, 1};
    Heap h(arr);
    h.print();          // heapified array
    h.push(3);
    h.print();
    h.sort();
    h.print();
}

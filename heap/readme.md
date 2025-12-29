# Heap / Priority Queue

A comprehensive reference guide for Heap data structure and Priority Queue patterns in Data Structures and Algorithms.

---

## Table of Contents

1. [Introduction](#introduction)
2. [When to Use Heaps](#when-to-use-heaps)
3. [Pattern 1: Basic Heap Operations](#pattern-1-basic-heap-operations)
4. [Pattern 2: Top K Elements](#pattern-2-top-k-elements)
5. [Pattern 3: K-Way Merge](#pattern-3-k-way-merge)
6. [Pattern 4: Two-Heap (Median)](#pattern-4-two-heap-median)
7. [Pattern 5: Heap Sort](#pattern-5-heap-sort)
8. [Pattern 6: Task Scheduling](#pattern-6-task-scheduling)
9. [Quick Reference Table](#quick-reference-table)
10. [Common Mistakes](#common-mistakes)

---

## Introduction

A **Heap** is a complete binary tree that satisfies the heap property. It's typically implemented as an array for efficiency.

### Heap Properties
- **Min-Heap**: Parent ≤ Children (smallest at root)
- **Max-Heap**: Parent ≥ Children (largest at root)

### Array Representation
```
For node at index i:
- Parent:      (i - 1) / 2
- Left Child:  2 * i + 1
- Right Child: 2 * i + 2
```

### Key Benefits
- **Extract Min/Max**: O(log n)
- **Insert**: O(log n)
- **Peek Top**: O(1)
- **Build Heap**: O(n) using Floyd's algorithm

---

## When to Use Heaps

| Scenario | Example |
|----------|---------|
| Find K largest/smallest | Top K songs, K closest points |
| Merge K sorted lists | K-way merge, merge intervals |
| Running median | Stream median, sliding window median |
| Priority scheduling | Task scheduler, CPU scheduling |
| Greedy algorithms | Dijkstra's, Huffman coding |
| Sorting | Heap sort (in-place, O(n log n)) |

---

## Pattern 1: Basic Heap Operations

Implementing a heap from scratch with core operations.

```
        1              (Min-Heap)
       / \
      3   2
     / \ / \
    7  4 5  6
    
Array: [1, 3, 2, 7, 4, 5, 6]
```

### Template (Heapify Down - Min-Heap)
```cpp
void minheapify(int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
    
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minheapify(smallest, n);
    }
}
```

### Template (Build Heap - Floyd's Algorithm)
```cpp
// O(n) time - NOT O(n log n)!
void buildHeap() {
    int n = arr.size();
    // Start from last non-leaf node
    for (int i = n/2 - 1; i >= 0; --i) {
        heapify(i, n);
    }
}
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 1 | **Heap Implementation** | `heap_implementation.cc` | Min/Max heap with all operations | O(log n) ops |

---

## Pattern 2: Top K Elements

Use a heap of size K to find the K largest/smallest elements efficiently.

```
Finding K largest with Min-Heap of size K:
- If new element > heap.top(), replace top
- Heap always contains K largest seen so far

[stream of n elements] → [Min-Heap size K] → K largest
```

### Template (Top K Largest using Min-Heap)
```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;  // Min-heap

for (auto& elem : elements) {
    minHeap.push(elem);
    if (minHeap.size() > k) {
        minHeap.pop();  // Remove smallest
    }
}
// minHeap now contains k largest elements
```

### Why Min-Heap for finding maximums?
- Heap keeps the K largest elements seen
- Min-heap lets us quickly identify and remove the smallest among our K candidates
- When size exceeds K, we efficiently remove the smallest

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 2 | **K Most Played** | `k_most_played.cc` | Min-heap size k, pop when > k | O(n log k) |
| 3 | **Most Played Across Genres** | `most_played_across_genre.cc` | Flatten nested structure, same pattern | O(n log k) |
| 4 | **Top Songs Class** | `top_songs_class.cc` | Fixed-size min-heap, no updates | O(log k) register |
| 5 | **Top Songs With Updates** | `top_songs_class_with_updates.cc` | Max-heap + lazy deletion + hash map | O(log n) register |

---

## Pattern 3: K-Way Merge

Merge K sorted sequences efficiently using a min-heap.

```
Sequence 1: [2, 6, 8]     →
Sequence 2: [3, 7, 10]    →  Min-Heap  →  [2, 3, 5, 6, 7, 8, 9, 10, 12]
Sequence 3: [5, 9, 12]    →
```

### Template
```cpp
// Heap entry: {value, sequence_index, position_in_sequence}
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;

// Initialize: push first element from each sequence
for (int i = 0; i < k; i++) {
    if (!sequences[i].empty()) {
        minHeap.push({sequences[i][0], i, 0});
    }
}

while (!minHeap.empty()) {
    auto [val, seqIdx, pos] = minHeap.top();
    minHeap.pop();
    result.push_back(val);
    
    // Push next element from same sequence
    if (pos + 1 < sequences[seqIdx].size()) {
        minHeap.push({sequences[seqIdx][pos + 1], seqIdx, pos + 1});
    }
}
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 6 | **Sum of First K Prime Powers** | `sum_of_first_k.cc` | Each prime = infinite sorted sequence | O(k log m) |

---

## Pattern 4: Two-Heap (Median)

Use two heaps to track the running median efficiently.

```
Lower Half (Max-Heap)     Upper Half (Min-Heap)
    [1, 2, 3]                 [4, 5, 6]
         ↑                      ↑
       max=3                  min=4
       
Median = (3 + 4) / 2 = 3.5
```

### Template
```cpp
priority_queue<int> maxHeap;  // Lower half (max at top)
priority_queue<int, vector<int>, greater<int>> minHeap;  // Upper half

void addNum(int num) {
    maxHeap.push(num);
    minHeap.push(maxHeap.top());
    maxHeap.pop();
    
    // Rebalance: maxHeap should have >= elements
    if (maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
}

double getMedian() {
    if (maxHeap.size() > minHeap.size())
        return maxHeap.top();
    return (maxHeap.top() + minHeap.top()) / 2.0;
}
```

### Invariants
- `maxHeap.size() == minHeap.size()` or `maxHeap.size() == minHeap.size() + 1`
- All elements in maxHeap ≤ All elements in minHeap
- Median is always accessible in O(1)

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 7 | **Popular Songs Class** | `popular_song_class.cc` | Popular if plays > median | O(log n) register, O(1) query |

---

## Pattern 5: Heap Sort

In-place sorting using heap property.

```
Build Max-Heap → Extract max to end → Heapify remaining → Repeat

[4, 8, 2, 6, 1] → Build → [8, 6, 2, 4, 1]
                          Extract 8 → [6, 4, 2, 1, | 8]
                          Extract 6 → [4, 1, 2, | 6, 8]
                          ...        → [1, 2, 4, 6, 8]
```

### Template
```cpp
// Step 1: Build heap
for (int i = n/2 - 1; i >= 0; --i) {
    heapify(i, n);
}

// Step 2: Extract elements one by one
for (int i = n - 1; i >= 1; --i) {
    swap(arr[0], arr[i]);    // Move current root to end
    heapify(0, i);           // Heapify reduced heap
}
```

### Heap Sort Properties
- **Time**: O(n log n) - guaranteed, unlike QuickSort
- **Space**: O(1) - in-place, unlike MergeSort
- **Stability**: Not stable
- **Min-Heap** → Descending order
- **Max-Heap** → Ascending order

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 8 | **Heap Sort (Descending)** | `heap_sort.cc` | Min-heap → descending order | O(n log n) |
| 9 | **Heap Sort (Ascending)** | `heap_sort2.cc` | Max-heap → ascending order | O(n log n) |

---

## Pattern 6: Task Scheduling

Greedy scheduling using max-heap to prioritize tasks.

```
Tasks by frequency: A(3), B(2), C(1)

Max-Heap picks most frequent → interleave to avoid conflicts
Result: A → B → A → C → A → B
```

### Template (Interleaving / Reorganize)
```cpp
priority_queue<pair<int, T>> maxHeap;  // {count, task}

while (!maxHeap.empty()) {
    auto [count, task] = maxHeap.top();
    maxHeap.pop();
    
    if (task != lastTask) {
        result.push_back(task);
        if (count > 1) maxHeap.push({count - 1, task});
        lastTask = task;
    } else {
        // Must pick second choice
        if (maxHeap.empty()) return {};  // Impossible
        auto [count2, task2] = maxHeap.top();
        maxHeap.pop();
        result.push_back(task2);
        if (count2 > 1) maxHeap.push({count2 - 1, task2});
        maxHeap.push({count, task});  // Put first back
        lastTask = task2;
    }
}
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 10 | **Make Playlist** | `make_playlist.cc` | No consecutive same-artist | O(n log m) |

---

## Quick Reference Table

| File | Pattern | Time | Space |
|------|---------|------|-------|
| `heap_implementation.cc` | Basic Heap | O(log n) ops | O(n) |
| `heap_sort.cc` | Heap Sort | O(n log n) | O(1) |
| `heap_sort2.cc` | Heap Sort | O(n log n) | O(1) |
| `k_most_played.cc` | Top K | O(n log k) | O(k) |
| `make_playlist.cc` | Task Scheduling | O(n log m) | O(n) |
| `most_played_across_genre.cc` | Top K | O(n log k) | O(k) |
| `popular_song_class.cc` | Two-Heap | O(log n) / O(1) | O(n) |
| `sum_of_first_k.cc` | K-Way Merge | O(k log m) | O(m) |
| `top_songs_class.cc` | Top K | O(log k) / O(k) | O(k) |
| `top_songs_class_with_updates.cc` | Top K + Updates | O(log n) / O(m) | O(n) |

---

## Common Mistakes

### 1. Wrong Heap Type for Problem
```cpp
// Finding K largest? Use MIN-heap of size K
// Finding K smallest? Use MAX-heap of size K
priority_queue<int, vector<int>, greater<int>> minHeap;  // For K largest
priority_queue<int> maxHeap;  // For K smallest
```

### 2. Forgetting to Limit Heap Size
```cpp
// Wrong: heap grows to size n
for (auto& x : arr) minHeap.push(x);

// Correct: maintain size k
for (auto& x : arr) {
    minHeap.push(x);
    if (minHeap.size() > k) minHeap.pop();  // Keep only k elements
}
```

### 3. Off-by-One in Build Heap
```cpp
// Wrong: starts too early
for (int i = n/2; i >= 0; --i) heapify(i);

// Correct: last non-leaf is at n/2 - 1
for (int i = n/2 - 1; i >= 0; --i) heapify(i);
```

### 4. Not Incrementing i After Swap with High in Heap Sort
```cpp
// In three-way partition, don't increment i after swapping with high
if (arr[i] > pivot) {
    swap(arr[i], arr[high]);
    high--;
    // i++;  // BUG! Must re-check swapped element
}
```

### 5. Pair Ordering in Priority Queue
```cpp
// Pairs are compared lexicographically (first element, then second)
priority_queue<pair<int, string>> pq;
// {10, "a"} > {10, "b"} because "a" < "b" (reversed!)
// {10, "a"} > {5, "z"}  because 10 > 5
```

### 6. Stale Entries with Updates
```cpp
// When values can be updated, old heap entries become stale
// Solution: Lazy deletion - validate against authoritative source
if (heap_entry.value == map[heap_entry.key]) {
    // Fresh entry - process it
} else {
    // Stale entry - skip it
}
```

---

## Build & Run

```bash
# Build all programs
make

# Build specific program
make heap_sort

# Clean executables
make clean

# Run a program
./heap_sort
```

---

## References

- Each `.cc` file contains detailed Doxygen-style comments explaining the algorithm
- Problem statements are included at the end of each file

---

*Last Updated: December 2025*


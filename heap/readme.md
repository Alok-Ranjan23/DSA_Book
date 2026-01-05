# Heap / Priority Queue

A collection of heap and priority queue problems demonstrating various patterns and techniques.

---

## 1. Basic Heap Operations

Implementing a heap from scratch with core operations.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `heap_implementation.cc` | Implement a heap class | Array-based heap, heapify | O(log n) ops | O(n) |

---

## 2. Top K Elements

Use a heap of size K to efficiently find the K largest/smallest elements.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `k_most_played.cc` | Find K most played songs | Min-heap of size k | O(n log k) | O(k) |
| `top_songs_class.cc` | Top K songs class (no updates) | Fixed-size min-heap | O(log k) register | O(k) |
| `top_songs_class_with_updates.cc` | Top K with cumulative updates | Max-heap + lazy deletion | O(log n) register | O(n) |

---

## 3. K-Way Merge

Merge K sorted sequences efficiently using a min-heap.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `most_played_across_genre.cc` | Top K across sorted genre lists | K-way merge with max-heap | O(k log m) | O(m) |
| `sum_of_first_k.cc` | Sum of first K prime powers | Merge infinite sequences | O(k log m) | O(m) |

---

## 4. Two-Heap (Median Tracking)

Use two heaps to efficiently track the median of a stream.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `popular_song_class.cc` | Is song popular? (plays > median) | Max-heap + min-heap | O(log n) / O(1) | O(n) |

---

## 5. Heap Sort

In-place sorting using heap property.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `heap_sort.cc` | Sort array (descending) | Min-heap → descending | O(n log n) | O(1) |
| `heap_sort2.cc` | Sort array (ascending) | Max-heap → ascending | O(n log n) | O(1) |

---

## 6. Task Scheduling

Greedy scheduling using max-heap to prioritize tasks.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `make_playlist.cc` | No consecutive same-artist songs | Max-heap interleaving | O(n log m) | O(n) |

---

## Heap Pattern Recipes

### Top K Largest (Min-Heap of size K)
```
top_k_largest(elements, k):
  minHeap = empty min-heap
  for each elem in elements:
    minHeap.push(elem)
    if minHeap.size() > k:
      minHeap.pop()  // Remove smallest
  return minHeap contents  // K largest elements
```

**Key insight:** Min-heap lets us quickly remove the smallest among K candidates when a larger element arrives.

### K-Way Merge
```
k_way_merge(sorted_lists, k):
  minHeap = empty min-heap  // {value, list_index, position}
  
  // Initialize with first element from each list
  for i in 0..lists.length:
    minHeap.push({lists[i][0], i, 0})
  
  while result.size() < k and minHeap not empty:
    {val, idx, pos} = minHeap.pop()
    result.add(val)
    
    // Push next element from same list
    if pos + 1 < lists[idx].length:
      minHeap.push({lists[idx][pos+1], idx, pos+1})
  
  return result
```

### Two-Heap Median
```
add_number(num):
  maxHeap.push(num)           // Add to lower half
  minHeap.push(maxHeap.pop()) // Move max to upper half
  
  // Rebalance: maxHeap should have >= elements
  if maxHeap.size() < minHeap.size():
    maxHeap.push(minHeap.pop())

get_median():
  if maxHeap.size() > minHeap.size():
    return maxHeap.top()
  return (maxHeap.top() + minHeap.top()) / 2
```

---

## Quick Reference

```
Array Representation (0-indexed):
  Parent:      (i - 1) / 2
  Left Child:  2 * i + 1
  Right Child: 2 * i + 2

C++ Priority Queue:
  Max-heap (default):  priority_queue<int> pq;
  Min-heap:            priority_queue<int, vector<int>, greater<int>> pq;

Build Heap (Floyd's Algorithm - O(n)):
  for i = n/2 - 1 down to 0:
    heapify(i)

Heap Sort:
  1. Build max-heap: O(n)
  2. For i = n-1 to 1:
       swap(arr[0], arr[i])
       heapify(0, i)  // Heapify reduced heap

Choosing Heap Type:
  Finding K largest?  → Use MIN-heap of size K
  Finding K smallest? → Use MAX-heap of size K
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make heap_sort)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./heap_sort)
```


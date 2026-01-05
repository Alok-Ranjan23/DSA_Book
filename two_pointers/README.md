# Two Pointers

A collection of two pointer problems demonstrating various patterns and techniques.

---

## 1. Opposite Direction (Converging)

Pointers start at opposite ends and move toward each other.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `palindromic_check.cc` | Check if string is palindrome | Compare chars at both ends | O(n) | O(1) |
| `palindromic_sentence.cc` | Palindrome ignoring non-letters | Skip non-letters, case-insensitive | O(n) | O(1) |
| `array_reversal.cc` | Reverse array in-place | Swap and move inward | O(n) | O(1) |
| `two_sum.cc` | Find pair summing to target (sorted) | Sum too big → h--, too small → l++ | O(n) | O(1) |
| `reverse_case.cc` | Match lowercase with uppercase | L finds lowercase, H finds uppercase | O(n) | O(1) |
| `valley_sort.cc` | Sort valley-shaped array | Pick larger of ends, fill from back | O(n) | O(n) |

---

## 2. Same Direction (Fast-Slow / Reader-Writer)

Both pointers move in the same direction at different speeds.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `duplicate_removal.cc` | Remove duplicates in-place | Write only when value changes | O(n) | O(1) |
| `shift_word_back.cc` | Move word to end of string | Skip subsequence, append at end | O(n) | O(1) |
| `smaller_prefix.cc` | Find elements at k, 2k positions | Slow at k, fast at 2k | O(n) | O(1) |

---

## 3. Two Arrays (Parallel Pointers)

One pointer for each array, advancing based on comparison.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `merge_two_sorted_array.cc` | Merge two sorted arrays | Always pick smaller element | O(n+m) | O(n+m) |
| `array_intersection.cc` | Find common elements | Equal → add & advance both | O(n+m) | O(min) |
| `three_way_merge.cc` | Merge three sorted arrays | Find min of 3, skip duplicates | O(n₁+n₂+n₃) | O(k) |
| `missing_number_in_range.cc` | Find missing numbers in range | Compare array with virtual range | O(n+k) | O(k) |
| `interval_intersection.cc` | Find overlapping intervals | max(starts) ≤ min(ends) = overlap | O(n+m) | O(k) |

---

## 4. Three-Way Partitioning

Three pointers divide array into regions (Dutch National Flag).

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `dutch_flag_problem.cc` | Partition into 3 colors | R→low, W→stay, B→high | O(n) | O(1) |
| `quicksort_partition.cc` | Partition around pivot | Three regions: <, =, > pivot | O(n) | O(1) |
| `parity_sorting.cc` | Evens before odds | Simpler 2-way partition | O(n) | O(1) |

---

## 5. Reversal Algorithm

In-place rotation using three reversals.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `prefix_suffix_swap.cc` | Rotate array by k positions | Three reversals | O(n) | O(1) |

---

## Two Pointer Recipes

### Opposite Direction (Converging)
```
converging_pointers(arr):
  l = 0, h = n - 1
  while l < h:
    if condition_move_left:  l++
    else if condition_move_right: h--
    else:
      process(arr[l], arr[h])
      l++; h--
```

### Reader-Writer (Same Direction)
```
reader_writer(arr):
  writer = 0
  for reader = 0 to n-1:
    if should_keep(arr[reader]):
      arr[writer] = arr[reader]
      writer++
  // writer = count of kept elements
```

### Two Arrays Merge
```
merge(arr1, arr2):
  i = 0, j = 0
  while i < n1 and j < n2:
    if arr1[i] < arr2[j]:
      result.add(arr1[i++])
    else:
      result.add(arr2[j++])
  // Handle remaining elements
  while i < n1: result.add(arr1[i++])
  while j < n2: result.add(arr2[j++])
```

### Three-Way Partition (Dutch Flag)
```
partition(arr, pivot):
  low = 0, i = 0, high = n - 1
  while i <= high:
    if arr[i] < pivot:
      swap(arr[low], arr[i])
      low++; i++
    else if arr[i] == pivot:
      i++
    else:  // arr[i] > pivot
      swap(arr[i], arr[high])
      high--
      // Don't increment i - check swapped element
```

### Reversal Algorithm (Rotation)
```
rotate_left_by_k(arr, k):
  reverse(arr, 0, k-1)
  reverse(arr, k, n-1)
  reverse(arr, 0, n-1)
```

---

## Quick Reference

```
When to Use Two Pointers:
  - Sorted array operations (pairs, merging)
  - In-place modifications (remove duplicates, partition)
  - Palindrome problems (symmetry check)
  - Comparing from both ends (valley/mountain arrays)

Common Mistakes:
  1. Off-by-one: Use l < h for pairs, l <= h for all elements
  2. Infinite loop: Always move at least one pointer
  3. Three-way: Don't increment i after swap with high
  4. Empty array: Check n > 0 before setting h = n - 1

Pointer Movement Patterns:
  [→ ... ←]  Converging (opposite direction)
  [→ →]      Same direction (fast-slow)
  [→] [→]    Two arrays (parallel)
  [< | = | >] Three-way partition
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make palindromic_check)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./palindromic_check)
```

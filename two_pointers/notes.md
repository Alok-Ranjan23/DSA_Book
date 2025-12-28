# Two Pointers Technique

A comprehensive reference guide for the Two Pointers pattern in Data Structures and Algorithms.

---

## Table of Contents

1. [Introduction](#introduction)
2. [When to Use Two Pointers](#when-to-use-two-pointers)
3. [Pattern 1: Opposite Direction (Converging)](#pattern-1-opposite-direction-converging)
4. [Pattern 2: Same Direction (Fast-Slow / Reader-Writer)](#pattern-2-same-direction-fast-slow--reader-writer)
5. [Pattern 3: Two Arrays (Parallel Pointers)](#pattern-3-two-arrays-parallel-pointers)
6. [Pattern 4: Three-Way Partitioning](#pattern-4-three-way-partitioning)
7. [Quick Reference Table](#quick-reference-table)
8. [Common Mistakes](#common-mistakes)

---

## Introduction

The **Two Pointers** technique uses two pointers to traverse data structures (usually arrays or strings) to solve problems efficiently, often reducing time complexity from O(n²) to O(n).

### Key Benefits
- **Time Efficiency**: Reduces nested loops to single pass
- **Space Efficiency**: Often achieves O(1) extra space
- **Simplicity**: Clean, readable code

---

## When to Use Two Pointers

| Scenario | Example |
|----------|---------|
| Sorted array operations | Finding pairs, merging |
| In-place modifications | Removing duplicates, partitioning |
| Palindrome problems | Checking symmetry |
| Sliding window variant | Subarray problems |
| Comparing from both ends | Valley/Mountain arrays |

---

## Pattern 1: Opposite Direction (Converging)

Pointers start at opposite ends and move toward each other.

```
[a, b, c, d, e, f, g]
 ↑                 ↑
 L                 H
 →                 ←
```

### Template
```cpp
int l = 0, h = n - 1;
while (l < h) {
    if (condition_to_move_left) l++;
    else if (condition_to_move_right) h--;
    else {
        // Process elements at l and h
        l++; h--;
    }
}
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 1 | **Palindrome Check** | `palindromic_check.cc` | Compare chars at both ends | O(n) / O(1) |
| 2 | **Palindromic Sentence** | `palindromic_sentence.cc` | Skip non-letters, case-insensitive | O(n) / O(1) |
| 3 | **Array Reversal** | `array_reversal.cc` | Swap and move inward | O(n) / O(1) |
| 4 | **2-Sum (Sorted)** | `two_sum.cc` | Sum too big → h--, too small → l++ | O(n) / O(1) |
| 5 | **Reverse Case Match** | `reverse_case.cc` | L finds lowercase, H finds uppercase | O(n) / O(1) |
| 6 | **Valley Sort** | `valley_sort.cc` | Pick larger of ends, fill from back | O(n) / O(n) |

---

## Pattern 2: Same Direction (Fast-Slow / Reader-Writer)

Both pointers move in the same direction at different speeds.

```
[a, b, b, c, c, c, d]
    ↑     ↑
    W     R (Reader ahead of Writer)
    →     →
```

### Template (Reader-Writer)
```cpp
int writer = 0, reader = 0;
while (reader < n) {
    if (should_keep(arr[reader])) {
        arr[writer] = arr[reader];
        writer++;
    }
    reader++;
}
// writer now contains count of kept elements
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 7 | **Duplicate Removal** | `duplicate_removal.cc` | Write only when value changes | O(n) / O(1) |
| 8 | **Shift Word to Back** | `shift_word_back.cc` | Skip subsequence chars, append at end | O(n) / O(1) |
| 9 | **Smaller Prefixes** | `smaller_prefix.cc` | Slow at k, fast at 2k positions | O(n) / O(1) |

---

## Pattern 3: Two Arrays (Parallel Pointers)

One pointer for each array, advancing based on comparison.

```
arr1: [1, 3, 5, 7]
       ↑
       i

arr2: [2, 4, 6]
       ↑
       j
```

### Template (Merge)
```cpp
int i = 0, j = 0;
while (i < n1 && j < n2) {
    if (arr1[i] < arr2[j]) {
        process(arr1[i]);
        i++;
    } else {
        process(arr2[j]);
        j++;
    }
}
// Handle remaining elements
while (i < n1) process(arr1[i++]);
while (j < n2) process(arr2[j++]);
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 10 | **Merge Two Sorted Arrays** | `merge_two_sorted_array.cc` | Always pick smaller element | O(n+m) / O(n+m) |
| 11 | **Array Intersection** | `array_intersection.cc` | Equal → add & advance both | O(n+m) / O(min) |
| 12 | **Three-Way Merge** | `three_way_merge.cc` | Find min of 3, skip duplicates | O(n1+n2+n3) / O(k) |
| 13 | **Missing Numbers in Range** | `missing_number_in_range.cc` | Compare array with virtual range | O(n+k) / O(k) |
| 14 | **Interval Intersection** | `interval_intersection.cc` | max(starts) ≤ min(ends) = overlap | O(n+m) / O(k) |

---

## Pattern 4: Three-Way Partitioning

Three pointers divide array into regions (Dutch National Flag).

```
[  < pivot  |  = pivot  |  unknown  |  > pivot  ]
             ↑           ↑           ↑
             low         i           high
```

### Template
```cpp
int low = 0, i = 0, high = n - 1;
while (i <= high) {
    if (arr[i] < pivot) {
        swap(arr[low], arr[i]);
        low++; i++;
    } else if (arr[i] == pivot) {
        i++;
    } else {  // arr[i] > pivot
        swap(arr[i], arr[high]);
        high--;
        // Don't increment i - need to check swapped element
    }
}
```

### Problems Using This Pattern

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 15 | **Dutch Flag Problem** | `dutch_flag_problem.cc` | R→low, W→stay, B→high | O(n) / O(1) |
| 16 | **Quicksort Partition** | `quicksort_partition.cc` | Three regions: <, =, > pivot | O(n) / O(1) |
| 17 | **Parity Sorting** | `parity_sorting.cc` | Evens to front (simpler 2-way) | O(n) / O(1) |

---

## Special Technique: Reversal Algorithm

Used for in-place rotation without extra space.

```
To rotate left by k: reverse(0,k-1), reverse(k,n-1), reverse(0,n-1)
```

| # | Problem | File | Key Insight | Complexity |
|---|---------|------|-------------|------------|
| 18 | **Prefix-Suffix Swap** | `prefix_suffix_swap.cc` | Three reversals for rotation | O(n) / O(1) |

---

## Quick Reference Table

| File | Pattern | Time | Space |
|------|---------|------|-------|
| `array_intersection.cc` | Two Arrays | O(n+m) | O(min) |
| `array_reversal.cc` | Opposite | O(n) | O(1) |
| `duplicate_removal.cc` | Reader-Writer | O(n) | O(1) |
| `dutch_flag_problem.cc` | Three-Way | O(n) | O(1) |
| `interval_intersection.cc` | Two Arrays | O(n+m) | O(k) |
| `merge_two_sorted_array.cc` | Two Arrays | O(n+m) | O(n+m) |
| `missing_number_in_range.cc` | Two Arrays | O(n+k) | O(k) |
| `palindromic_check.cc` | Opposite | O(n) | O(1) |
| `palindromic_sentence.cc` | Opposite | O(n) | O(1) |
| `parity_sorting.cc` | Three-Way | O(n) | O(1) |
| `prefix_suffix_swap.cc` | Reversal | O(n) | O(1) |
| `quicksort_partition.cc` | Three-Way | O(n) | O(1) |
| `reverse_case.cc` | Opposite | O(n) | O(1) |
| `shift_word_back.cc` | Reader-Writer | O(n) | O(1) |
| `smaller_prefix.cc` | Fast-Slow | O(n) | O(1) |
| `three_way_merge.cc` | Two Arrays | O(n) | O(k) |
| `two_sum.cc` | Opposite | O(n) | O(1) |
| `valley_sort.cc` | Opposite | O(n) | O(n) |

---

## Common Mistakes

### 1. Off-by-One Errors
```cpp
// Wrong: may skip elements or go out of bounds
while (l <= h)  // vs  while (l < h)
```
**Rule**: Use `l < h` when processing pairs, `l <= h` when processing all elements.

### 2. Forgetting to Move Pointers
```cpp
// Infinite loop!
while (l < h) {
    if (arr[l] == arr[h]) {
        // Forgot l++; h--;
    }
}
```

### 3. Wrong Pointer Movement in Three-Way
```cpp
// Wrong: incrementing i after swap with high
if (arr[i] > pivot) {
    swap(arr[i], arr[high]);
    high--;
    i++;  // BUG! Must re-check swapped element
}
```

### 4. Not Handling Empty Arrays
```cpp
int h = n - 1;  // If n=0, h=-1, may cause issues
```

### 5. Case Sensitivity in String Problems
```cpp
// 'A' = 65, 'a' = 97, difference = 32
if (s[l] != s[h] && s[l] + 32 != s[h] && s[l] != s[h] + 32)
```

---

## Build & Run

```bash
# Build all programs
make

# Build specific program
make palindromic_check

# Clean executables
make clean

# Run a program
./palindromic_check
```

---

## References

- Each `.cc` file contains detailed comments explaining the algorithm
- Problem statements are included at the end of each file

---

*Last Updated: December 2025*

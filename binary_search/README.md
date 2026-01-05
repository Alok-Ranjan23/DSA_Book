# Binary Search

A collection of binary search problems demonstrating various patterns and techniques.

---

## 1. Standard Binary Search

Classic search problems in sorted data structures.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `search_sorted_array.cc` | Find target in sorted array | Standard binary search | O(log n) | O(1) |
| `search_sorted_grid.cc` | Find target in sorted 2D grid | Staircase search | O(m + n) | O(1) |
| `huge_array_search.cc` | Search array with unknown length | Exponential + binary search | O(log n) | O(1) |

---

## 2. Finding Transition Points

Problems involving finding where a property changes from true to false (or vice versa).

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `cctv_footage.cc` | First timestamp bike was stolen | Binary search on API | O(log n) | O(1) |
| `race_overtake.cc` | When player 2 overtakes player 1 | First true in boolean array | O(log n) | O(1) |
| `valley_bottom.cc` | Minimum in valley-shaped array | Binary search local minimum | O(log n) | O(1) |

---

## 3. Finding Bounds

Problems involving first/last occurrence or counting.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `target_count_divisible_by_k.cc` | Check if count is divisible by k | Lower + upper bound | O(log n) | O(1) |
| `two_array_two_sum.cc` | Find pair summing to 0 | Binary search + linear scan | O(m log n) | O(1) |

---

## 4. Binary Search on Answer

Problems where we binary search on the answer space, not array indices.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `min_pages_per_day.cc` | Minimum pages to read daily | Binary search + greedy validation | O(n log m) | O(1) |
| `min_subarray_sum_split.cc` | Minimize max subarray sum | Binary search + greedy validation | O(n log s) | O(1) |
| `water_refill.cc` | Compute floor(a/b) without division | Exponential + binary search | O(log n) | O(1) |
| `tide_aerial_view.cc` | Find most balanced picture | Nested binary search | O(P·R·log C) | O(1) |

---

## Transition Point Recipe

The core pattern for most binary search problems:

```
transition_point_recipe()
  define is_before(val) to return whether val is 'before'
  initialize l and r to the first and last values in the range
  handle edge cases:
    - the range is empty 
    - l is 'after'  (the whole range is 'after')
    - r is 'before' (the whole range is 'before')

  while l and r are not next to each other (r - l > 1)
    mid = (l + r) / 2
    if is_before(mid)
      l = mid
    else
      r = mid

  return l (the last 'before'), r (the first 'after'), or something else,
         depending on the problem
```

**Key insight:** Define `is_before()` such that the array looks like `[T, T, T, ..., F, F, F]`. Then `l` converges to last T, `r` to first F.

---

## Quick Reference

```
Standard Binary Search (find exact match):
  while l <= r:
    mid = (l + r) / 2
    if arr[mid] == target: return mid
    if arr[mid] < target: l = mid + 1
    else: r = mid - 1

Leftmost (lower bound):          Rightmost (upper bound):
  while l < r:                     while l < r:
    mid = (l + r) / 2                mid = (l + r + 1) / 2
    if arr[mid] >= target:           if arr[mid] <= target:
      r = mid                          l = mid
    else: l = mid + 1                else: r = mid - 1

Binary Search on Answer:
  l = min_possible_answer
  r = max_possible_answer
  while l < r:
    mid = (l + r) / 2
    if isValid(mid): r = mid      # mid works, try smaller
    else: l = mid + 1             # mid doesn't work, need larger
  return l
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make search_sorted_array)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./search_sorted_array)
```

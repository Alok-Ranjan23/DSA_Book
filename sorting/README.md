# Sorting

A collection of sorting problems demonstrating various patterns and techniques.

---

## 1. Bucket Sort / Non-Comparison Sort

Exploiting bounded value ranges for linear-time sorting.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `sort_by_publication_year.cc` | Sort books by year | Bucket sort on year range [1000, 2025] | O(n + K) | O(n + K) |
| `frequency_sort.cc` | Sort characters by frequency | Bucket sort on frequency counts | O(n + K) | O(n) |

---

## 2. Sort and Scan

Sort the data first, then perform a linear scan to answer the query.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `nested_circle.cc` | Are circles nested? | Sort by radius, check consecutive containment | O(n log n) | O(1) |

---

## 3. Indirect / Stable Sort

Sort indices or auxiliary structures instead of the data itself. Stable sort preserves relative order of equal elements.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `Spreadsheet.cc` | Spreadsheet with row/col sorting | Indirect index sort + grid rebuild | O(C log C + R\*C) | O(R\*C) |
| `delete_operation.cc` | Process delete operations | Stable sort indices + exclusion set | O(n log n + m) | O(n) |
| `delete_op.cc` | Process delete operations (copy) | Stable sort indices + exclusion set | O(n log n + m) | O(n) |

---

## 4. Selection Algorithms (K Smallest)

Find the K smallest elements without fully sorting the array.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `first_k.cc` | Find K smallest elements | QuickSelect (randomized) | O(n) avg | O(n) |
| `first_k.cc` | Find K smallest elements | Max-heap of size k | O(n log k) | O(k) |
| `first_k.cc` | Find K smallest elements | Sorting | O(n log n) | O(1) |

---

## Sorting Pattern Recipes

### Bucket Sort (Bounded Integers)
```
bucket_sort(items, key, min_val, max_val):
  buckets = array of (max_val - min_val + 1) empty lists
  for each item in items:
    buckets[key(item) - min_val].append(item)
  result = concatenate all buckets in order
  return result
```

**Key insight:** When the key range K is small or constant, bucket sort gives O(n + K) time — beating O(n log n) comparison sorts.

### Bucket Sort (Frequency-Based)
```
frequency_bucket_sort(items):
  count = frequency map of items
  max_freq = max(count.values())
  buckets = array of (max_freq + 1) empty lists
  for each (item, freq) in count:
    buckets[freq].append(item)
  traverse buckets from max_freq down to 1
  return collected items
```

**Key insight:** Bucket index = frequency. Traversing high-to-low gives descending frequency order. Scanning items alphabetically gives free tie-breaking.

### Indirect Index Sort
```
indirect_sort(arr):
  indices = [0, 1, ..., n-1]
  stable_sort(indices, key = arr[i])
  // indices[0] = index of smallest element
  // indices[1] = index of second smallest, etc.
  return indices
```

**Key insight:** Sort indices by their corresponding values instead of moving the data. Useful when you need the original positions (e.g., for targeted deletions or column reordering).

### QuickSelect (K-th Smallest)
```
quickselect(arr, k):
  pivot = random element from arr
  smaller = [x for x in arr if x < pivot]
  equal   = [x for x in arr if x == pivot]
  larger  = [x for x in arr if x > pivot]

  if k <= |smaller|:       return quickselect(smaller, k)
  if k <= |smaller|+|equal|: return pivot
  return quickselect(larger, k - |smaller| - |equal|)
```

**Key insight:** Like quicksort but only recurses into one partition. O(n) average because each level processes a shrinking subset (n + n/2 + n/4 + ... = 2n).

---

## Quick Reference

```
Comparison Sorts (general-purpose):
  std::sort        → O(n log n) avg, not stable
  std::stable_sort → O(n log n), stable, O(n) extra space

Non-Comparison Sorts (bounded keys):
  Bucket sort      → O(n + K), stable, K = key range
  Counting sort    → O(n + K), stable, K = key range
  Radix sort       → O(d * (n + K)), stable, d = digits

Selection:
  QuickSelect      → O(n) avg, O(n²) worst
  Max-heap size k  → O(n log k) guaranteed
  Sorting + slice  → O(n log n)

Stability:
  Stable sort preserves original order for equal keys.
  Use when: tie-breaking by original index matters,
            or sorting a 2D structure by one dimension.

Choosing the Right Approach:
  Bounded integer keys?    → Bucket / Counting sort: O(n + K)
  Need K smallest/largest? → QuickSelect: O(n) avg
  Need K smallest, worst-case guarantee? → Max-heap: O(n log k)
  General sorting?         → std::sort: O(n log n)
  Stability required?      → std::stable_sort
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make nested_circle)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./nested_circle)
```

# Sliding Window

A collection of sliding window problems demonstrating various patterns and techniques across fixed-size, resetting, maximum, minimum, and counting windows.

---

## 1. Fixed-Size Window

Window maintains a predetermined, constant length $k$. As the right pointer advances to include a new element, the left pointer advances once the window size hits $k$.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `fixed_size_window/most_weekly_sales.cc` | Max sales across any 7-day period | Running sum in a fixed window of size 7 | O(n) | O(1) |
| `fixed_size_window/most_weekly_sales_k_days.cc` | Start day of best $k$-day sales streak | Fixed window of size $k$ tracking maximum sum | O(n) | O(1) |
| `fixed_size_window/enduring_best_seller_streak.cc` | Check if $k$-day period has identical best seller | Fixed window + hash map size == 1 | O(n · L) | O(k · L) |
| `fixed_size_window/unique_best_seller_streak.cc` | Check if $k$-day period has all unique titles | Fixed window + hash map size == $k$ | O(n · L) | O(k · L) |

---

## 2. Resetting Window

The window expands greedily as long as consecutive elements satisfy a condition. The moment the condition is violated, the window resets immediately past the invalid element.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `resetting_window/longest_good_day_streak.cc` | Most consecutive good days ($\ge 10$ sales) | Reset window past bad day ($l = r + 1$) | O(n) | O(1) |
| `resetting_window/longest_alternating_seq.cc` | Longest alternating good/bad days | Reset window start to point of alternation break | O(n) | O(1) |
| `resetting_window/max_subarray_sum.cc` | Maximum sum non-empty subarray | Kadane variant: reset window when sum $< 0$ | O(n) | O(1) |

---

## 3. Maximum Sliding Window

Find the longest contiguous subarray satisfying a condition (e.g. at most $k$ violations or resource budget). Grows as long as valid; shrinks from the left only when constraint is exceeded.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `maximum_sliding_window/maximum_with_atmost_three_days.cc` | Longest period with at most 3 bad days | Grow while `bad_days < 3`, shrink when violated | O(n) | O(1) |
| `maximum_sliding_window/ad_campaign_boost.cc` | Max consecutive good days with $k$ large boosts (+20) | Treat as at most $k$ bad days; any day is fixable | O(n) | O(1) |
| `maximum_sliding_window/ad_campaign_small_boost.cc` | Max consecutive good days with $k$ small boosts (+5) | Conditional boost + `l == r` guard for un-fixable days | O(n) | O(1) |
| `maximum_sliding_window/boosting_multiple_days.cc` | Max consecutive good days with $k$ unit boosts | Resource budget + `l == r` guard | O(n) | O(1) |
| `maximum_sliding_window/atmost_k_unique.cc` | Longest period with at most $k$ distinct titles | Hash map frequency tracking with distinct count $\le k$ | O(n · L) | O(k · L) |

---

## 4. Minimum Sliding Window

Find the shortest contiguous subarray meeting a target condition. Grows until the target is satisfied, then shrinks from the left while recording the minimum size.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `minimum_sliding_window/shortest_period_over_20_sales.cc` | Shortest period with total sales $> 20$ | Grow while sum $\le 20$, shrink when $> 20$ | O(n) | O(1) |
| `minimum_sliding_window/shortest_with_all_letters.cc` | Shortest substring of $s_1$ containing all of $s_2$ | Freq map + `char_to_match` counter | O(n + m) | O(m) |
| `minimum_sliding_window/small_range_with_k_elements.cc` | Smallest range $[low, high]$ covering $\ge k$ elements | Sort + min sliding window of size $k$ | O(n log n) | O(1) |
| `minimum_sliding_window/strong_start_and_ending.cc` | Max combined good days at start + end with $k$ boosts | Complement: minimize bad middle window | O(n) | O(1) |

---

## 5. Counting Problems

Count subarrays that satisfy conditions using sliding window properties and algebraic reductions.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `counting_problems/count_subarray_atmost_kBad.cc` | Count subarrays with at most $k$ bad days | Max window: each grow step adds $(r - l)$ | O(n) | O(1) |
| `counting_problems/count_subarray_exactly_kBad.cc` | Count subarrays with exactly $k$ bad days | `atMost(k) - atMost(k - 1)` | O(n) | O(1) |
| `counting_problems/count_subarray_atleast_kBad.cc` | Count subarrays with at least $k$ bad days | Complement: `total - atMost(k - 1)` | O(n) | O(1) |
| `counting_problems/count_subarrays_bad_days_range.cc` | Count subarrays with bad days in $[k_1, k_2]$ | Range: `atMost(k2) - atMost(k1 - 1)` | O(n) | O(1) |
| `counting_problems/count_good_start_good_end.cc` | Count subarrays starting and ending on good days | Combinatorics: $g \cdot (g + 1) / 2$ | O(n) | O(1) |
| `counting_problems/count_subarrays_all_remainders.cc` | Count subarrays with all 3 remainders mod 3 | Complement: `total - atMost(2 remainders)` | O(n) | O(1) |
| `counting_problems/count_subarrays_with_drops.cc` | Subarrays with atMost / exactly / atLeast $k$ drops | Consecutive drop tracking + inclusion-exclusion | O(n) | O(1) |
| `counting_problems/count_good_subarrays_with_atleast_k_sales.cc` | Subarrays with no bad days and sales $\ge k$ | Segment split + min window adding $(n - r + 1)$ | O(n) | O(n) |

---

## Sliding Window Recipes

### 1. Fixed-Size Window Template
```python
def fixed_length_window(arr, k):
  # initialize l, r = 0, data structures, cur_best
  while r < len(arr):
    # grow window: add arr[r], r += 1
    if r - l == k:
      # update cur_best
      # shrink window: remove arr[l], l += 1
  return cur_best
```

### 2. Resetting Window Template
```python
def resetting_window(arr):
  # initialize l, r = 0, data structures, cur_best
  while r < len(arr):
    if can_extend_window(arr[r]):
      # grow window, update cur_best, r += 1
    else:
      # reset window and data structures past arr[r]
  return cur_best
```

### 3. Maximum Sliding Window Template
```python
def maximum_window(arr):
  # initialize l, r = 0, data structures, cur_best
  while r < len(arr):
    if window_would_be_valid_with(arr[r]):
      # grow window: add arr[r], r += 1
      # cur_best = max(cur_best, r - l)
    elif l == r:
      # element is fundamentally un-fixable: skip it
      l += 1
      r += 1
    else:
      # shrink window: remove arr[l], l += 1
  return cur_best
```

> **When is the `l == r` guard needed?**
>
> - **No guard needed:** If every element can satisfy `can_grow` when the window is empty (e.g., replacement budget $> 0$). Shrinking always restores validity before $l$ can catch $r$.
> - **Guard needed:** If some elements can **never** satisfy `can_grow` regardless of window state (e.g., boost $+5$ on an element of 4 cannot reach 10). Without `l == r`, $l$ overtakes $r$, leading to out-of-bounds access.

### 4. Minimum Sliding Window Template
```python
def minimum_window(arr):
  # initialize l, r = 0, cur_best = infinity
  while True:
    if window_must_grow_to_become_valid:
      if r == len(arr):
        break
      # grow window: add arr[r], r += 1
    else:
      # cur_best = min(cur_best, r - l)
      # shrink window: remove arr[l], l += 1
  return cur_best
```

### 5. Counting Subarrays Patterns
```
Number of subarrays in window [l, r):
  - AtMost(k):   each valid expansion adds (r - l) new subarrays ending at r - 1
  - AtLeast(k):  total_subarrays - atMost(k - 1)
  - Exactly(k):  atMost(k) - atMost(k - 1)
  - Range(k1,k2): atMost(k2) - atMost(k1 - 1)
```

---

## Build & Run

Each subdirectory contains its own `Makefile`:

```bash
# Navigate to any category
cd fixed_size_window    # or resetting_window, maximum_sliding_window, etc.

make              # Build all programs in the directory
make <program>    # Build specific (e.g., make most_weekly_sales)
make clean        # Remove all compiled binaries
./<program>       # Run (e.g., ./most_weekly_sales)
```

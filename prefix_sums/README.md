# Prefix Sums

A collection of problems solved with **prefix sums** and their relatives (**difference arrays**, **prefix sum + hash map**, **prefix/suffix products**), turning O(n²) or O(n·q) brute force into O(n) preprocessing plus O(1) per query.

---

## 1. Range Sum / Count Queries (Prefix Sum)

Precompute running totals once; any range `[l, r]` is then a difference of two prefix values.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `channel_views.cc` | Total views in each period `[l, r]` | `prefix[r] - prefix[l-1]` (`l == 0` special case) | O(n + p) | O(n) |
| `youtube_video_reception.cc` | Number of positive days (likes > dislikes) in each period | Prefix **count** over a 0/1 flag | O(n + p) | O(n) |
| `balance_point.cc` | First index where left sum == right sum | Running prefix sum + shrinking total, no array | O(n) | O(1) |

---

## 2. Range Updates (Difference Array)

Many "add `v` to every element in `[l, r]`" updates. Record `+v` at `l` and `-v` at `r+1`, then one prefix pass applies them all.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `segmented_video_votes.cc` | Net vote count at every minute after range votes | Difference array → prefix sum | O(n + m) | O(n) |
| `most_booked_slot.cc` | Earliest slot with the most bookings after bulk bookings | Difference array + first max (strict `<`, start at `-1`) | O(n + k) | O(n) |
| `all_overbooked_slots.cc` | Number of slots whose bookings exceed `cap` | Difference array + count `slots[i] + prefix[i] > cap` | O(n + k) | O(n) |

---

## 3. Subarray Sum Equals K (Prefix Sum + Hash Map)

A subarray `arr[j+1..i]` sums to `k` exactly when `prefix[j] == prefix[i] - k`. Look up earlier prefixes in a hash map. Works with **negative numbers**, unlike a sliding window.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `count_subarrays_with_sum_k.cc` | Number of subarrays with sum `k` | Map prefix → **frequency**, seed `{0: 1}`, `long long` count | O(n) | O(n) |
| `longest_subarrays_with_sum_k.cc` | Longest subarray with sum `k` (`-1` if none) | Map prefix → **first index**, seed `{0: -1}` | O(n) | O(n) |

---

## 4. Prefix / Suffix Products

The answer for `i` depends on everything to its left and everything to its right.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `exclusive_product.cc` | Product of all elements except `arr[i]`, mod 10⁹+7 | `prefix[i-1] * suffix[i+1]`, no division (zeros, modulo) | O(n) | O(n) |

---

## 5. Sum of Absolute Differences (Sort + Prefix Sum)

`abs()` blocks prefix sums; sorting fixes the sign of every difference.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `youtube_video_unusual_days.cc` | Highest `Σ \|score[i] - score[j]\|` over all days | Sort, then left part + right part from a size `n+1` prefix | O(n log n) | O(n) |

---

## Prefix Sum Recipe

Two common layouts. Both cost O(n) to build and O(1) per range query.

### Inclusive prefix (size `n`)
Used in `channel_views.cc`, `youtube_video_reception.cc`, `count_subarrays_with_sum_k.cc`, `longest_subarrays_with_sum_k.cc`.

```
build(arr)
  P[0] = arr[0]
  for i from 1 to n-1:
    P[i] = P[i-1] + arr[i]              # P[i] = arr[0] + ... + arr[i]

range_sum(l, r)                          # inclusive [l, r]
  if l == 0: return P[r]
  return P[r] - P[l-1]
```

### Exclusive prefix (size `n+1`)
Used in `youtube_video_unusual_days.cc`. The extra leading `0` removes the `l == 0` branch.

```
build(arr)
  P = [0] * (n+1)
  for i from 0 to n-1:
    P[i+1] = P[i] + arr[i]              # P[i] = arr[0] + ... + arr[i-1]

range_sum(l, r)                          # inclusive [l, r]
  return P[r+1] - P[l]
```

### Example: `arr = [3, 5, 4, 8, 7, 2]`

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|-------|---|---|---|---|---|---|---|
| `arr` | 3 | 5 | 4 | 8 | 7 | 2 | |
| Inclusive `P` | 3 | 8 | 12 | 20 | 27 | 29 | |
| Exclusive `P` | 0 | 3 | 8 | 12 | 20 | 27 | 29 |

Sum of `[2, 4]` = 4 + 8 + 7 = **19**: inclusive `P[4] - P[1] = 27 - 8`, exclusive `P[5] - P[2] = 27 - 8`.

**Variants:**
- **Prefix count:** add `(condition ? 1 : 0)` instead of the value (`youtube_video_reception.cc`).
- **Running prefix:** if you only scan once, keep a single running sum instead of an array (`balance_point.cc`).
- **Prefix product:** multiply instead of add; take `% mod` after each step (`exclusive_product.cc`).

---

## Difference Array Recipe

The **inverse** of a prefix sum: a range update becomes two point updates.

```
apply_ranges(n, updates)                 # each update = [l, r, v]
  diff = [0] * n
  for (l, r, v) in updates:
    diff[l] += v                         # start adding v at l
    if r+1 < n: diff[r+1] -= v           # stop adding v after r
  return prefix_sum(diff)                # final value at every index
```

### Example: `segmented_video_votes.cc`, `n = 6`

| Vote `[l, r, v]` | `diff` after the update |
|------------------|-------------------------|
| start | `[0, 0, 0, 0, 0, 0]` |
| `[3, 4, +1]` | `[0, 0, 0, 1, 0, -1]` |
| `[0, 0, +1]` | `[1, -1, 0, 1, 0, -1]` |
| `[1, 3, +1]` | `[1, 0, 0, 1, -1, -1]` |
| `[0, 5, -1]` | `[0, 0, 0, 1, -1, -1]` (`r+1 = 6` skipped) |
| **prefix sum** | **`[0, 0, 0, 1, 0, -1]`** |

**Key insight:** each update costs O(1) no matter how wide the range is, and a single O(n) prefix pass applies all of them. Order of updates doesn't matter.

---

## Prefix Sum + Hash Map Recipe

```
count_subarrays(arr, k)                  # how MANY subarrays sum to k
  freq = {0: 1}                          # empty prefix
  P = 0, count = 0
  for x in arr:
    P += x
    count += freq.get(P - k, 0)          # look up BEFORE inserting
    freq[P] += 1
  return count

longest_subarray(arr, k)                 # LONGEST subarray summing to k
  first = {0: -1}                        # empty prefix "before index 0"
  P = 0, best = -1
  for i, x in enumerate(arr):
    P += x
    if P - k in first: best = max(best, i - first[P - k])
    if P not in first: first[P] = i      # keep EARLIEST index only
  return best
```

### Example: `arr = [1, 2, 3, 2, 1]`, `k = 3`

| `i` | `arr[i]` | `P` | `P - k` | Earlier prefix found | Subarray |
|-----|----------|-----|---------|----------------------|----------|
| 0 | 1 | 1 | -2 | — | — |
| 1 | 2 | 3 | 0 | `0` at index -1 | `[1, 2]`, length 2 |
| 2 | 3 | 6 | 3 | `3` at index 1 | `[3]`, length 1 |
| 3 | 2 | 8 | 5 | — | — |
| 4 | 1 | 9 | 6 | `6` at index 2 | `[2, 1]`, length 2 |

Count = **3**, longest = **2**.

| Want | Map stores | Seed | Update rule |
|------|------------|------|-------------|
| **Count** of subarrays | prefix → frequency | `{0: 1}` | always `freq[P]++` (after lookup) |
| **Longest** subarray | prefix → first index | `{0: -1}` | insert only if `P` is new |
| **Shortest** subarray | prefix → last index | `{0: -1}` | always overwrite `last[P] = i` |

---

## Prefix / Suffix Product Recipe

```
exclusive_product(arr)
  pre[i] = arr[0] * ... * arr[i]         # left to right, % mod each step
  suf[i] = arr[i] * ... * arr[n-1]       # right to left, % mod each step
  res[0]   = suf[1]                      # nothing on the left
  res[n-1] = pre[n-2]                    # nothing on the right
  res[i]   = pre[i-1] * suf[i+1]         # left of i  x  right of i
```

### Example: `arr = [1, 3, 2, 1]`

| Index | 0 | 1 | 2 | 3 |
|-------|---|---|---|---|
| `arr` | 1 | 3 | 2 | 1 |
| `pre` | 1 | 3 | 6 | 6 |
| `suf` | 6 | 6 | 2 | 1 |
| `res` | 6 | 2 | 3 | 6 |

**Why no division:** `total / arr[i]` breaks when `arr[i] == 0`, and `(a / b) % m != (a % m) / b`, so it can't be combined with a running modulo.

---

## Sort + Prefix Sum Recipe (Sum of Absolute Differences)

```
max_total_deviation(s)
  sort(s)
  P = exclusive prefix of s              # size n+1, P[0] = 0
  for i in 0..n-1:
    left  = s[i] * i       - P[i]                 # Σ (s[i] - s[j]),  j < i
    right = (P[n] - P[i+1]) - s[i] * (n-1-i)      # Σ (s[j] - s[i]),  j > i
    best  = max(best, left + right)
```

### Example: scores `[3, 5, -8]` → sorted `[-8, 3, 5]`, `P = [0, -8, -5, 0]`

| `i` | `s[i]` | left | right | total |
|-----|--------|------|-------|-------|
| 0 | -8 | 0 | 8 − (−8)·2 = 24 | **24** |
| 1 | 3 | 3·1 − (−8) = 11 | 5 − 3·1 = 2 | 13 |
| 2 | 5 | 5·2 − (−5) = 15 | 0 | 15 |

**Key insight:** sorting doesn't change any day's total deviation; it only guarantees `s[j] <= s[i]` on the left and `s[j] >= s[i]` on the right, so each `|s[i] - s[j]|` has a known sign.

---

## Common Pitfalls

- **Overflow:** sums of 10⁵ values up to 10⁴ reach 10⁹ (near `INT_MAX`); subarray **counts** reach n²/2 ≈ 5·10⁹ → use `long long`.
- **`l == 0`:** inclusive prefix has no `P[-1]`; either branch on it or use the size `n+1` layout.
- **Hash-map seed:** forget `{0: 1}` / `{0: -1}` and subarrays starting at index 0 are missed.
- **Lookup before insert** in the count version, otherwise `k == 0` matches a prefix with itself.
- **Difference array end:** skip `diff[r+1]` when `r+1 == n` (or allocate size `n+1`).
- **Ties / initial max:** start the running max below any valid value (e.g. `-1`) and use strict `<` to keep the earliest index.
- **Modulo products:** widen to a 64-bit type before multiplying (`long long`; `long` is only 32-bit on Windows).

---

## Quick Reference

```
Many range-sum queries on a static array      -> prefix sum, P[r] - P[l-1]
Count elements matching a condition in ranges -> prefix count over 0/1 flags
Many range-add updates, read values at the end-> difference array + one prefix pass
Count subarrays with sum k (negatives OK)     -> prefix sum + hash map of frequencies
Longest subarray with sum k                   -> prefix sum + hash map of first index
Answer depends on "everything except i"       -> prefix + suffix arrays
Sum of |a[i] - a[j]| over all j               -> sort + prefix sum
Left sum == right sum                         -> running prefix + (total - prefix - a[i])
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make channel_views)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./channel_views)
```

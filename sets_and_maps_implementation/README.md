# Sets and Maps Implementation

Hand-built hash containers (no `unordered_set` / `unordered_map`), implemented with **separate chaining**, a **multiplicative (Knuth) hash**, and **load-factor-driven resizing**. Each file builds one data structure from a `vector` of bucket `vector`s.

---

## 1. Hash Sets

Store unique elements; answer "is it present?" in O(1) average time.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `hash_set_class.cc` | `add` / `remove` / `contains` / `size` for ints | Chained buckets of `int`, swap-with-last delete | O(1) avg/op | O(n + cap) |
| `hash_set_class_extension.cc` | Hash set + `elements`, `union`, `intersection` | Union = add both (dedupe via `add`); intersection = filter by `s.contains` | O(1) avg/op; union O(n + m), intersection O(n) | O(n + cap) |

---

## 2. Hash Maps

Associate each key with a value; update in place when the key already exists.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `hash_map_class.cc` | `add` / `remove` / `contains` / `get` / `size` / `keys` / `values` | Chained buckets of `pair<int, string>`; `get` returns `""` as null | O(1) avg/op; `keys`/`values` O(n + cap) | O(n + cap) |

---

## 3. Multi-Containers (Duplicates Allowed)

Allow repeated elements/keys by storing a **count** or a **value list** per distinct key, and keep two separate counters.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `multiset.cc` | Set allowing copies; `size` counts copies | `(element, count)` pairs; `_size` = copies, `_num_keys` = distinct (drives load factor) | O(1) avg/op | O(u + cap) |
| `multimap.cc` | Map allowing many values per key; `remove(k)` drops all | `(key, vector<string>)` pairs; `_size` = pairs, `resize_size` = distinct keys | O(1) avg/op; `get` O(v) to copy | O(n + u + cap) |

`n` = elements / pairs, `u` = distinct keys, `cap` = number of buckets, `v` = values for one key.

---

## Design Shared by All Files

```
Hash        h(x, cap) = floor(cap * frac(x * C)),  C = (sqrt(5) - 1) / 2 ≈ 0.618
Buckets     vector<vector<Entry>>, entry lives in buckets[h(x, cap)]
Lookup      scan one bucket linearly                       -> O(1) average
Delete      overwrite with bucket's last entry, pop_back   -> O(1) once found
Grow        load factor  > 1            -> cap * 2, rehash everything
Shrink      load factor  < 0.25 && cap > 10 -> cap / 2, rehash everything
```

**Load factor = distinct keys / cap.** For the multi-containers this must count *distinct keys*, not total copies/pairs, because only distinct keys occupy bucket slots. `size()` reports the user-facing count separately.

**Average cost is O(1)** per operation (amortized for `add`/`remove` because of occasional O(n + cap) rehashes). Worst case is O(n) if every key lands in the same bucket.

> **Note:** `hash_map_class.cc`, `hash_set_class.cc`, `hash_set_class_extension.cc`, and `multimap.cc` compute `frac` with `static_cast<int>`, which truncates toward zero, so **negative keys produce a negative bucket index**. `multiset.cc` uses `floor()` and handles negatives correctly.

---

## Core Idioms

```
# Bucket lookup
bin = h(x, cap)
for e in buckets[bin]:
  if e.key == x: return e

# Insert with resize
if x not in table:
  buckets[h(x, cap)].append(x); keys += 1
  if keys / cap > 1: rehash(cap * 2)

# O(1) unordered delete inside a bucket
bucket[i] = bucket[last]; bucket.pop()

# Rehash (cap must change BEFORE computing new bins)
cap = new_cap
for e in old_entries: new_buckets[h(e.key, cap)].append(e)

# Multi-container counters
size     += 1   on every add          # user-visible count
num_keys += 1   only for a new key    # drives load factor
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make multiset)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./multiset)
```

# Sets and Maps

A collection of problems solved with hash-based containers (`unordered_set` and `unordered_map`), demonstrating membership testing, frequency counting, lookup tables, and stateful tracking.

---

## 1. Set Membership & Duplicate Detection

Use a hash **set** to test "have I seen this before?" in O(1) average time.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `account_sharing_detection.cc` | Find an IP of a shared (repeated) username | Early exit on first duplicate seen | O(n) | O(n) |
| `multi_account_cheating.cc` | Two users with the identical set of IPs | Sort each list to a canonical key, hash `vector<string>` | O(n) | O(n) |

---

## 2. Frequency Counting

Use a hash **map** of `key -> count`, then scan for the answer.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `most_shared_account.cc` | Username with the most connections | Count, then take the max | O(n) | O(n) |
| `most_frequent_octet.cc` | Most common first octet of IPs | Parse substring + count (≤ 256 keys) | O(n) | O(1) |
| `word_expansion_class.cc` | Is `s2` = `s1` plus one extra letter? | Char-frequency cancel (anagram + 1) | O(n + m) | O(1) |
| `largest_set_intersection.cc` | Which set to drop to maximize intersection | Count containing-sets per value | O(T + k) | O(T) |

---

## 3. Lookup Tables & Complement Search

Map a value to useful info so a related value can be located in O(1).

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `find_all_squares.cc` | All pairs where `arr[i]^2 == arr[j]` | `value -> index` map | O(n) | O(n) |
| `product_of_alphabetical_sum.cc` | Three words whose sums multiply to target | Set of sums + fix-two-lookup-third | O(N + S²) | O(1) |

---

## 4. Stateful Tracking with Multiple Maps

Combine several maps/sets to track evolving state across a sequence of events.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `cheater_detection.cc` | Adjacent students with identical mistakes | `desk -> id/answers` maps + grid `(row, col)` math | O(N·k) | O(N·k) |
| `action_log_anomalies.cc` | Tickets with bad open/close history | `opened`/`seen`/`working` maps & sets, single sweep | O(N) | O(N) |

---

## 5. Map/Set-Backed Class Design

Build a small data structure on top of nested hash containers.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `domain_resolver.cc` | Register/query IP → domain → subdomain | `unordered_map<string, unordered_set<string>>` (nested) | O(1) avg/op | O(D + S) |

---

## Choosing a Container

```
Need to know only "is it present?" / dedupe        -> unordered_set
Need to associate a key with a value or a count     -> unordered_map
Need group membership (one key, many values)        -> unordered_map<K, unordered_set<V>>
Need a custom key (vector, pair, struct)            -> provide a hash functor
```

**Average cost is O(1)** for insert / find / erase on hash containers; worst case is O(n) under adversarial collisions. Use these structures to trade O(n) extra space for turning an O(n²) brute-force scan into a single O(n) pass.

---

## Core Idioms

```
# Duplicate detection (set)
seen = {}
for x in items:
  if x in seen: return x        # first repeat
  seen.add(x)

# Frequency count then max (map)
count = {}
for x in items: count[x] += 1
best = argmax(count)            # scan map for highest count

# Complement / lookup table (map)
index = { value: i for i, value in enumerate(arr) }
if complement in index: ...     # O(1) partner lookup

# Canonical key for unordered data
key = sorted(list)              # order-independent identity
```

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make find_all_squares)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./find_all_squares)
```

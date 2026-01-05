# String Manipulation

A collection of string manipulation problems demonstrating various patterns and techniques.

---

## 1. Basic String Operations

Fundamental operations for string processing without built-in methods.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `string_split.cc` | Split string by delimiter | Accumulator + tokenization | O(n) | O(n) |
| `string_join.cc` | Join strings with delimiter | Pre-allocate + append | O(m) | O(m) |

---

## 2. String Matching / Search

Finding patterns within text strings.

| File | Problem | Key Technique | Time | Space |
|------|---------|---------------|------|-------|
| `string_matching.cc` | Find first occurrence of pattern | Rabin-Karp rolling hash | O(n + m) avg | O(1) |

---

## String Pattern Recipes

### String Split
```
split(s, delimiter):
  result = []
  current_token = ""
  
  for each char in s:
    if char == delimiter:
      result.append(current_token)
      current_token = ""
    else:
      current_token += char
  
  result.append(current_token)  // Don't forget final token
  return result
```

**Edge cases:**
- Empty string → `[]`
- Consecutive delimiters → empty strings in result
- Leading/trailing delimiters → empty strings at edges

### String Join
```
join(arr, separator):
  if arr is empty:
    return ""
  
  result = arr[0]
  for i = 1 to arr.length - 1:
    result += separator + arr[i]
  
  return result
```

**Optimization:** Pre-calculate total length and `reserve()` to avoid reallocations.

### Rabin-Karp Rolling Hash
```
index_of(text, pattern):
  n = text.length, m = pattern.length
  if m > n: return -1
  
  pat_hash = hash(pattern)
  text_hash = hash(text[0..m-1])
  
  if pat_hash == text_hash and text[0..m-1] == pattern:
    return 0
  
  // Precompute BASE^(m-1) for O(1) rolling
  power = BASE^(m-1) mod MOD
  
  for i = 1 to n - m:
    // Rolling hash: remove leftmost, add rightmost
    text_hash = (text_hash - text[i-1] * power) * BASE + text[i+m-1]
    text_hash = text_hash mod MOD
    
    if text_hash == pat_hash and text[i..i+m-1] == pattern:
      return i
  
  return -1
```

**Key insight:** Rolling hash updates in O(1), making average case O(n + m) instead of O(n × m).

---

## Quick Reference

```
C++ String Operations:
  s.size() / s.length()     // Length
  s[i] / s.at(i)            // Access character
  s += c                    // Append char (amortized O(1))
  s += str                  // Append string
  s.substr(pos, len)        // Substring (O(len) - creates copy)
  s.find(pattern)           // Built-in search (O(n*m) worst)
  s.reserve(n)              // Pre-allocate capacity

Rolling Hash Formula:
  hash("abc") = a*128² + b*128¹ + c*128⁰
  
  To slide from "abc" to "bcd":
  new_hash = (old_hash - a*128²) * 128 + d

Avoid String Copies:
  // Bad: O(m) substring copy
  if (s.substr(i, m) == pattern) ...
  
  // Good: O(m) in-place comparison
  bool match = true;
  for (int j = 0; j < m; j++) {
    if (s[i+j] != pattern[j]) { match = false; break; }
  }
```

---

## Complexity Summary

| Algorithm | Average Time | Worst Time | Space |
|-----------|-------------|------------|-------|
| Brute Force Match | O(n × m) | O(n × m) | O(1) |
| Rabin-Karp | O(n + m) | O(n × m) | O(1) |
| KMP | O(n + m) | O(n + m) | O(m) |
| Boyer-Moore | O(n / m) | O(n × m) | O(k) |

Where n = text length, m = pattern length, k = alphabet size.

---

## Build & Run

```bash
make              # Build all programs
make <program>    # Build specific (e.g., make string_split)
make clean        # Remove all binaries
./<program>       # Run (e.g., ./string_split)
```


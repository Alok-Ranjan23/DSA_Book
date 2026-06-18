/**
 * @file multi_account_cheating.cc
 * @brief Detect whether two users share the exact same set of IP addresses
 *
 * This file checks if any two users connected from the identical set of IPs.
 * Since the IP lists are unordered, each list is sorted to obtain a canonical
 * form, then stored in a hash set. A collision in the set means a duplicate
 * IP set exists, implying the same person behind two accounts.
 *
 * Key Concepts:
 * - Canonicalizing an unordered list by sorting before comparison
 * - Hashing a vector<string> via a custom hash functor (VectorStringHash)
 * - Duplicate detection with an unordered_set
 *
 * Time Complexity: O(N)
 *   - N = number of users. Each list has <= 10 IPs (constant), so sorting and
 *     hashing each list is O(1) work; the log factor is log(list size), not
 *     log(N). Total work is therefore linear in the number of users.
 *
 * Space Complexity: O(N)
 *   - Hash set stores up to N canonicalized IP lists
 */

#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

/**
 * @brief Custom hash functor so vector<string> can be used as a set key
 *
 * The standard library does not provide a hash for vector<string>, so we
 * combine the hashes of the individual strings. The mixing constant
 * 0x9e3779b9 and the bit shifts spread the bits to reduce collisions
 * (the same boost::hash_combine technique).
 */
struct VectorStringHash {
  size_t operator()(const std::vector<std::string>& vec) const {
    size_t seed = 0;                  // 1. Initialize the final hash value
    hash<string> hasher;              // 2. Use the standard built-in string hasher

    for (const string& str : vec) {   // 3. Loop through every string in the vector
      // 4. The Magic Formula:
      seed ^= hasher(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;                      // 5. Return the combined hash
  }
};

/**
 * @brief Determine whether any two users share an identical set of IPs
 *
 * @param users Vector of (username, IP list) pairs; IP lists are unordered
 * @return true if two users have the exact same set of IPs, false otherwise
 *
 * Algorithm:
 * 1. For each user, sort their IP list to get an order-independent key.
 * 2. If that sorted list already exists in the set, a duplicate set was
 *    found -> return true.
 * 3. Otherwise, insert the sorted list and continue.
 * 4. If no duplicates are found, return false.
 */
//Time O(N)  (each IP list is bounded by 10 entries, so per-user work is O(1))
//Space O(N)
bool is_same_user(vector<pair<string, vector<string>>>& users) {
  unordered_set<vector<string>,VectorStringHash> uset;
  for(auto& user: users) {
    vector<string> ip_list = user.second;
    // Sort so that lists with the same IPs in different orders match
    sort(ip_list.begin(),ip_list.end());
    // Identical sorted list already seen -> same person, two accounts
    if(uset.find(ip_list) != uset.end()) {
      return true;
    }
    uset.insert(ip_list);
  }
  return false;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Example 1: "bob" and "bob2" have the same IPs (different order) -> true
  vector<pair<string, vector<string>>>users {
    {"mike", {"203.0.3.10", "208.51.0.5", "52.0.2.5"}},
    {"bob",  {"111.0.0.10", "222.0.0.5", "222.0.0.8"}},
    {"bob2", {"222.0.0.5", "222.0.0.8", "111.0.0.10"}}
  };
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  // Example 2: distinct IP sets -> false
  users = {
    {"alice", {"1.1.1.1"}},
    {"bob", {"2.2.2.2"}}
  };
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  // Example 3: no users -> false
  users = {};
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Multi-Account Cheating
 *
 * Our company runs an online game where the terms of service state that each
 * person can only have one account. We have a list of usernames and the
 * (unordered) list of IP addresses that they have ever connected from. We say
 * two users are suspected of belonging to the same person if the list of IPs
 * is the same. Return whether any two lists contain the exact same set of IPs.
 *
 * Example 1: users = [
 *   ("mike", ["203.0.3.10", "208.51.0.5", "52.0.2.5"]),
 *   ("bob", ["111.0.0.10", "222.0.0.5", "222.0.0.8"]),
 *   ("bob2", ["222.0.0.5", "222.0.0.8", "111.0.0.10"])
 * ]
 * Output: True. Users "bob" and "bob2" have the same IPs.
 *
 * Example 2: users = [
 *   ("alice", ["1.1.1.1"]),
 *   ("bob", ["2.2.2.2"])
 * ]
 * Output: False. No two users have the same IPs.
 *
 * Example 3: users = []
 * Output: False. There are no users.
 *
 * Constraints:
 * - The length of users is at most `10^5`
 * - Each username is non-empty and unique
 * - Each list of IPs has between `1` and `10` IPs
 * - All IPs are unique and follow the IPv4 format
 * - Each octet is a number between `0` and `255`
 *
 *============================================================================*/

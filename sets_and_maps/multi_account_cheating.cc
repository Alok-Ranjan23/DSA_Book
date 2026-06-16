#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

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

//Time O(NlogN)
//Space O(N)
bool is_same_user(vector<pair<string, vector<string>>>& users) {
  unordered_set<vector<string>,VectorStringHash> uset;
  for(auto& user: users) {
    vector<string> ip_list = user.second;
    sort(ip_list.begin(),ip_list.end());
    if(uset.find(ip_list) != uset.end()) {
      return true;
    }
    uset.insert(ip_list);
  }
  return false;
}

// To execute C++, please define "int main()"
int main() {
  // Example 1
  vector<pair<string, vector<string>>>users {
    {"mike", {"203.0.3.10", "208.51.0.5", "52.0.2.5"}},
    {"bob",  {"111.0.0.10", "222.0.0.5", "222.0.0.8"}},
    {"bob2", {"222.0.0.5", "222.0.0.8", "111.0.0.10"}}
  };
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  //Example 2
  users = {
    {"alice", {"1.1.1.1"}},
    {"bob", {"2.2.2.2"}}
  };
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  //Example 2
  users = {};
  cout<<boolalpha;
  cout<<is_same_user(users)<<"\n--------------\n";

  return 0;
}

// Multi-Account Cheating

// Our company runs an online game where the terms of service state that each person can only have one account. We have a list of usernames and the (unordered) list of IP addresses that they have ever connected from. We say two users are suspected of belonging to the same person if the list of IPs is the same. Return whether any two lists contain the exact same set of IPs.

// Example 1: users = [
//   ("mike", ["203.0.3.10", "208.51.0.5", "52.0.2.5"]),
//   ("bob", ["111.0.0.10", "222.0.0.5", "222.0.0.8"]),
//   ("bob2", ["222.0.0.5", "222.0.0.8", "111.0.0.10"])
// ]
// Output: True. Users "bob" and "bob2" have the same IPs.

// Example 2: users = [
//   ("alice", ["1.1.1.1"]),
//   ("bob", ["2.2.2.2"])
// ]
// Output: False. No two users have the same IPs.

// Example 3: users = []
// Output: False. There are no users.

// Constraints:

// - The length of users is at most `10^5`
// - Each username is non-empty and unique
// - Each list of IPs has between `1` and `10` IPs
// - All IPs are unique and follow the IPv4 format
// - Each octet is a number between `0` and `255`

/**
 * @file most_shared_account.cc
 * @brief Find the username that appears in the most connections (most shared)
 *
 * This file uses a hash map to count how many times each username appears
 * across a list of (IP, username) connections, then returns the username
 * with the highest count (provided it is shared, i.e. appears more than once).
 *
 * Key Concepts:
 * - Frequency counting with an unordered_map (hash map)
 * - Single pass to build counts, second pass to find the maximum
 * - optional<string> to represent "no shared account found"
 *
 * Time Complexity: O(n)
 *   - One pass to count, one pass to find the max over at most n entries
 *
 * Space Complexity: O(n)
 *   - Hash map stores up to n distinct usernames
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
using namespace std;

/**
 * @brief Determine the most shared username among the connections
 *
 * @param connections Vector of (IP, username) pairs
 * @return The most shared username, or nullopt if no username is shared
 *
 * Algorithm:
 * 1. Tally the number of connections per username in a hash map.
 * 2. Scan the map to track the username with the highest count.
 * 3. A username is "shared" only if it appears more than once; otherwise
 *    return nullopt to signal that no account is being shared.
 */
//Time : O(n)
//Space: O(n)
optional<string> detect_shared_account(vector<pair<string,string>> & connections) {
  unordered_map<string,int> umap; // {name,count}
  // Count how many connections each username has
  for(auto& connection: connections) {
    umap[connection.second]++;
  }
  string most_shared_account {};
  int count {0};
  // Find the username with the maximum connection count
  for(auto& [username, connection_count]: umap) {
    if(count<connection_count) {
      most_shared_account = username;
      count = connection_count;
    }
  }
  // Only count it as "shared" if it appears in more than one connection
  if(count > 1) return most_shared_account;
  return nullopt;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Example 1: "mike" appears twice -> most shared account
  vector<pair<string,string>> connections {
    {"203.0.113.10", "mike"},
    {"208.51.100.25", "bob"},
    {"202.0.2.5", "mike"},
    {"203.0.113.15", "bob2"}
  };
  auto user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";

  // Example 2: tie between "alice" and "bob" (each twice) -> either is valid
  connections =  {
    {"1.1.1.1", "alice"},
    {"1.1.1.2", "bob"},
    {"1.1.1.3", "alice"},
    {"1.1.1.4", "bob"}
  };
  user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";

  // Example 3: no connections -> nothing is shared
  connections =  {};
  user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Most Shared Account
 *
 * You've compiled a list of IP addresses of all the clients connected to your
 * service and the username associated with each one. Assume all IPs are unique
 * and username lengths are between `1` and `30`. We say a username is being
 * shared if it appears in two (or more) connections. Return the most shared
 * username. In case of a tie, return any of them.
 *
 * Example 1: connections = [("203.0.113.10", "mike"), ("208.51.100.25", "bob"),
 *                           ("202.0.2.5", "mike"), ("203.0.113.15", "bob2")]
 * Output: "mike". User "mike" is connected twice, while other users are
 * connected once.
 *
 * Example 2: connections = [("1.1.1.1", "alice"), ("1.1.1.2", "bob"),
 *                           ("1.1.1.3", "alice"), ("1.1.1.4", "bob")]
 * Output: "alice". Both "alice" and "bob" are connected twice, so either would
 * be a valid output.
 *
 * Example 3: connections = []
 * Output: None. There are no connections.
 *
 * Constraints:
 * - The length of connections is at most `10^5`
 * - All IPs are unique
 * - Username lengths are between `1` and `30` characters
 * - All usernames contain only lowercase letters
 *
 *============================================================================*/

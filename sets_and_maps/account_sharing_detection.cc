/**
 * @file account_sharing_detection.cc
 * @brief Detect whether any username appears in two or more connections
 *
 * This file scans a list of (IP, username) connections and, using a hash set
 * of seen usernames, detects the first username that reappears. When a repeat
 * is found, it returns the IP of the current (duplicate) connection.
 *
 * Key Concepts:
 * - Membership testing with an unordered_set (hash set)
 * - Early exit on the first duplicate username encountered
 * - Empty string sentinel to indicate "no sharing detected"
 *
 * Time Complexity: O(n)
 *   - Single pass over the connections with O(1) set lookups/inserts
 *
 * Space Complexity: O(n)
 *   - Hash set stores up to n distinct usernames
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/**
 * @brief Return an IP of a shared username, or "" if none is shared
 *
 * @param connections Vector of (IP, username) pairs
 * @return The IP of the first duplicated username, or "" if no sharing exists
 *
 * Algorithm:
 * 1. Walk the connections, tracking usernames already seen in a hash set.
 * 2. If the current username is already in the set, it is shared -> return
 *    this connection's IP immediately.
 * 3. Otherwise, record the username and continue.
 * 4. If the loop finishes with no repeats, return the empty string.
 */
string detect_shared_account(vector<pair<string,string>> & connections) {
  unordered_set<string> uset; //name
  for(auto& connection: connections) {
    // Username already seen -> account is shared, report current IP
    if(uset.find(connection.second)!=uset.end()) {
      return connection.first;
    }
    // First time seeing this username, remember it
    uset.insert(connection.second);
  }
  // No username repeated -> nothing is shared
  return "";
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Example 1: "mike" repeats -> returns the IP of the duplicate connection
  vector<pair<string,string>> connections 
  {
    {"203.0.113.10", "mike"}, 
    {"298.51.100.25", "bob"}, 
    {"292.0.2.5", "mike"}, 
    {"203.0.113.15", "bob2"}
  };
  string user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";

  // Example 2: both "mike" and "bob" repeat -> any of their IPs is valid
  connections =  {
    {"111.0.0.0", "mike"}, 
    {"111.0.0.1", "mike"}, 
    {"111.0.0.2", "bob"}, 
    {"111.0.0.3", "bob"}
  };
  user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";

  // Example 3: all usernames unique -> empty string
  connections =  {
    {"111.0.0.0", "mike"}, 
    {"111.0.0.1", "mike2"}, 
    {"111.0.0.2", "mike3"}, 
    {"111.0.0.3", "mike4"}
  };
  user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Account Sharing Detection
 *
 * You've compiled a list of IP addresses of all the clients connected to your
 * service and the username associated with each one. Assume all IPs are unique
 * and username lengths are between `1` and `30`. We say a username is being
 * shared if it appears in two connections.
 *
 * If usernames are being shared, return an IP of any of them. Otherwise,
 * return an empty string.
 *
 * Example 1: connections = [("203.0.113.10", "mike"), ("298.51.100.25", "bob"),
 *                           ("292.0.2.5", "mike"), ("203.0.113.15", "bob2")]
 * Output: "203.0.113.10". User "mike" is connected from that IP and
 * "292.0.2.5", so "292.0.2.5" would also be a valid output.
 *
 * Example 2: connections = [("111.0.0.0", "mike"), ("111.0.0.1", "mike"),
 *                           ("111.0.0.2", "bob"), ("111.0.0.3", "bob")]
 * Output: "111.0.0.0". Any of the IPs would be a valid output.
 *
 * Example 3: connections = [("111.0.0.0", "mike"), ("111.0.0.1", "mike2"),
 *                           ("111.0.0.2", "mike3"), ("111.0.0.3", "mike4")]
 * Output: ""
 *
 * Constraints:
 * - The length of `connections` is at most `10^5`
 * - All IPs are unique
 * - Username lengths are between `1` and `30` characters
 * - All `usernames` contain only lowercase letters
 *
 *============================================================================*/

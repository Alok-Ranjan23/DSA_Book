/**
 * @file most_frequent_octet.cc
 * @brief Find the most common first octet among a list of IPv4 addresses
 *
 * This file extracts the first octet (the portion before the first dot) of
 * each IPv4 address, counts the occurrences with a hash map, and returns the
 * octet that appears most frequently.
 *
 * Key Concepts:
 * - String parsing to isolate the first octet (substring before '.')
 * - Frequency counting with an unordered_map (hash map)
 * - optional<string> to represent the empty-input case
 *
 * Time Complexity: O(n)
 *   - One pass over n IPs to count, one pass over the distinct octets
 *
 * Space Complexity: O(1)
 *   - At most 256 distinct first-octet values (0-255) are possible
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
using namespace std;

/**
 * @brief Determine the most frequent first octet across the given IPs
 *
 * @param ips Vector of IPv4 address strings (e.g. "203.0.113.10")
 * @return The most common first octet as a string, or nullopt if ips is empty
 *
 * Algorithm:
 * 1. For each IP, slice out the substring before the first '.' (first octet).
 * 2. Tally each first octet in a hash map.
 * 3. Scan the map to find the octet with the highest count.
 * 4. Return nullopt when there are no IPs (count stays 0).
 */
//Time O(n)
//Space: O(1) : only 256 unique values possible for first octet
optional<string> most_frequent_octet (vector<string>& ips) {
  unordered_map <string,int> octet_umap;
  for(auto& ip: ips) {
    // Locate the first '.' and take everything before it as the first octet
    int first_dot = ip.find('.');
    string first_octet (ip,0,first_dot);
    octet_umap[first_octet]++;    
  }
  string freq_octet {};
  int count {0};
  // Track the first octet with the highest occurrence count
  for(auto& [octet, octet_count]: octet_umap) {
    if(count<octet_count) {
      freq_octet = octet;
      count = octet_count;
    }
  }
  // count == 0 means there were no IPs at all
  if(count>0) return freq_octet;
  return nullopt;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Example 1: "203" appears twice as the first octet
  vector<string> ips {"203.0.113.10", "208.51.100.5", "202.0.2.5", "203.0.113.5"};
  auto freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  
  // Example 2: "10" appears twice, "192" once
  ips = {"10.0.0.1", "10.0.0.2", "192.168.1.1"};
  freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  
  // Example 3: no IPs -> None
  ips = {};
  freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 *
 * # Most Frequent Octet
 *
 * You've compiled a list of IP addresses of all the clients connected to your
 * service. Assume all IPs are unique and follow the IPv4 format, which consists
 * of four 8-bit numbers (called octets) separated by dots. Return the most
 * common first octet among the connections.
 *
 * Example 1: ips = ["203.0.113.10", "208.51.100.5", "202.0.2.5", "203.0.113.5"]
 * Output: "203". 203 appears twice as the first octet.
 *
 * Example 2: ips = ["10.0.0.1", "10.0.0.2", "192.168.1.1"]
 * Output: "10". 10 appears twice as the first octet, while 192 appears once.
 *
 * Example 3: ips = []
 * Output: None. There are no IP addresses.
 *
 * Constraints:
 * - The length of `ips` is at most 10^5
 * - All IPs are unique and follow the IPv4 format
 * - Each octet is a number between `0` and `255`
 *
 *============================================================================*/

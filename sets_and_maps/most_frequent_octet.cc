#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
using namespace std;

//Time O(n)
//Space: O(1) : only 256 unique values possible for first octet
optional<string> most_frequent_octet (vector<string>& ips) {
  unordered_map <string,int> octet_umap;
  for(auto& ip: ips) {
    int first_dot = ip.find('.');
    string first_octet (ip,0,first_dot);
    octet_umap[first_octet]++;    
  }
  string freq_octet {};
  int count {0};
  for(auto& [octet, octet_count]: octet_umap) {
    if(count<octet_count) {
      freq_octet = octet;
      count = octet_count;
    }
  }
  if(count>0) return freq_octet;
  return nullopt;
}

// To execute C++, please define "int main()"
int main() {
  vector<string> ips {"203.0.113.10", "208.51.100.5", "202.0.2.5", "203.0.113.5"};
  auto freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  
  ips = {"10.0.0.1", "10.0.0.2", "192.168.1.1"};
  freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  
  ips = {};
  freq_octet = most_frequent_octet(ips);
  if(freq_octet.has_value()) cout<<freq_octet.value()<<"\n";
  else cout<<"None\n";
  cout<<"--------------------------------------\n";
  return 0;
}

// Most Frequent Octet

// You've compiled a list of IP addresses of all the clients connected to your service. Assume all IPs are unique and follow the IPv4 format, which consists of four 8-bit numbers (called octets) separated by dots. Return the most common first octet among the connections.

// Example 1: ips = ["203.0.113.10", "208.51.100.5", "202.0.2.5", "203.0.113.5"]
// Output: "203". 203 appears twice as the first octet.

// Example 2: ips = ["10.0.0.1", "10.0.0.2", "192.168.1.1"]
// Output: "10". 10 appears twice as the first octet, while 192 appears once.

// Example 3: ips = []
// Output: None. There are no IP addresses.

// Constraints:

// - The length of `ips` is at most 10^5
// - All IPs are unique and follow the IPv4 format
// - Each octet is a number between `0` and `255`

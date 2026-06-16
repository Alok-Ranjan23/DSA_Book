#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
using namespace std;

//Time : O(n)
//Space: O(n)
optional<string> detect_shared_account(vector<pair<string,string>> & connections) {
  unordered_map<string,int> umap; // {name,count}
  for(auto& connection: connections) {
    umap[connection.second]++;
  }
  string most_shared_account {};
  int count {0};
  for(auto& [username, connection_count]: umap) {
    if(count<connection_count) {
      most_shared_account = username;
      count = connection_count;
    }
  }
  if(count > 1) return most_shared_account;
  return nullopt;
}

// To execute C++, please define "int main()"
int main() {
  vector<pair<string,string>> connections {
    {"203.0.113.10", "mike"},
    {"208.51.100.25", "bob"},
    {"202.0.2.5", "mike"},
    {"203.0.113.15", "bob2"}
  };
  auto user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";

  connections =  {
    {"1.1.1.1", "alice"},
    {"1.1.1.2", "bob"},
    {"1.1.1.3", "alice"},
    {"1.1.1.4", "bob"}
  };
  user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";

  connections =  {};
  user_ip = detect_shared_account(connections); 
  if(user_ip.has_value()) cout<<user_ip.value()<<"\n";
  else cout<<"None"<<"\n";
  return 0;
}

// Most Shared Account

// You've compiled a list of IP addresses of all the clients connected to your service and the username associated with each one. Assume all IPs are unique and username lengths are between `1` and `30`. We say a username is being shared if it appears in two (or more) connections. Return the most shared username. In case of a tie, return any of them.

// Example 1: connections = [("203.0.113.10", "mike"), ("208.51.100.25", "bob"), ("202.0.2.5", "mike"), ("203.0.113.15", "bob2")]
// Output: "mike". User "mike" is connected twice, while other users are connected once.

// Example 2: connections = [("1.1.1.1", "alice"), ("1.1.1.2", "bob"), ("1.1.1.3", "alice"), ("1.1.1.4", "bob")]
// Output: "alice". Both "alice" and "bob" are connected twice, so either would be a valid output.

// Example 3: connections = []
// Output: None. There are no connections.

// Constraints:

// - The length of connections is at most `10^5`
// - All IPs are unique
// - Username lengths are between `1` and `30` characters
// - All usernames contain only lowercase letters

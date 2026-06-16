#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

string detect_shared_account(vector<pair<string,string>> & connections) {
  unordered_set<string> uset; //name
  for(auto& connection: connections) {
    if(uset.find(connection.second)!=uset.end()) {
      return connection.first;
    }
    uset.insert(connection.second);
  }
  return "";
}

// To execute C++, please define "int main()"
int main() {
  vector<pair<string,string>> connections 
  {
    {"203.0.113.10", "mike"}, 
    {"298.51.100.25", "bob"}, 
    {"292.0.2.5", "mike"}, 
    {"203.0.113.15", "bob2"}
  };
  string user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";

  connections =  {
    {"111.0.0.0", "mike"}, 
    {"111.0.0.1", "mike"}, 
    {"111.0.0.2", "bob"}, 
    {"111.0.0.3", "bob"}
  };
  user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";

  connections =  {
    {"111.0.0.0", "mike"}, 
    {"111.0.0.1", "mike2"}, 
    {"111.0.0.2", "mike3"}, 
    {"111.0.0.3", "mike4"}
  };
  user_ip = detect_shared_account(connections); cout<<user_ip<<"\n";
  return 0;
}

// Account Sharing Detection

// You've compiled a list of IP addresses of all the clients connected to your service and the username associated with each one. Assume all IPs are unique and username lengths are between `1` and `30`. We say a username is being shared if it appears in two connections.

// If usernames are being shared, return an IP of any of them. Otherwise, return an empty string.

// Example 1: connections = [("203.0.113.10", "mike"), ("298.51.100.25", "bob"), ("292.0.2.5", "mike"), ("203.0.113.15", "bob2")]
// Output: "203.0.113.10". User "mike" is connected from that IP and "292.0.2.5", so "292.0.2.5" would also be a valid output.

// Example 2: connections = [("111.0.0.0", "mike"), ("111.0.0.1", "mike"), ("111.0.0.2", "bob"), ("111.0.0.3", "bob")]
// Output: "111.0.0.0". Any of the IPs would be a valid output.

// Example 3: connections = [("111.0.0.0", "mike"), ("111.0.0.1", "mike2"), ("111.0.0.2", "mike3"), ("111.0.0.3", "mike4")]
// Output: ""

// Constraints:

// - The length of `connections` is at most `10^5`
// - All IPs are unique
// - Username lengths are between `1` and `30` characters
// - All `usernames` contain only lowercase letters

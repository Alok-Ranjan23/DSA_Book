#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

/*
Time  Complexity: O(nlogk)
Space Complexity: O(k)
*/
vector<string> k_most_played(vector<pair<string,int>>& songs, int k) {
  vector<string> res;
  priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;
  for(auto& p : songs) {
    pq.push({p.second,p.first});
    if(pq.size()>static_cast<size_t>(k)) pq.pop();
  }
  while(!pq.empty()) {
    res.push_back(pq.top().second);
    pq.pop();
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<pair<string,int>> songs {
    {"All the Single Brackets", 132},
    {"Oops! I Broke Prod Again", 274},
    {"Coding In The Deep", 146},
    {"Boolean Rhapsody", 193},
    {"Here Comes The Bug", 291},
    {"All About That Base Case", 291}};
  int k = 3;
  for(auto& song: k_most_played(songs,k)) cout<<song<<"\n";
  return 0;
}

// # K Most Played

// You are given a list of `(title, plays)` tuples where the first element is the name of a song, and the second is the number of times the song has been played. You are also given a positive integer `k`. Return the `k` most played songs from the list, in any order.

// - If the list has fewer than `k` songs, return all of them.
// - Break ties in any way you want.
// - You can assume that song titles have a length of at most `50`.

// Example:
// songs = [["All the Single Brackets", 132],
//          ["Oops! I Broke Prod Again", 274],
//          ["Coding In The Deep", 146],
//          ["Boolean Rhapsody", 193],
//          ["Here Comes The Bug", 291],
//          ["All About That Base Case", 291]]
// k = 3
// Output: ["All About That Base Case", "Here Comes The Bug", "Oops! I Broke Prod Again"]. Any order of these (excellent) songs would be valid.

// Follow-up: Can you solve it using only `O(k)` space?

// Constraints:

// - The length of `songs` is at most `10^5`
// - Each element in `songs` is a tuple with a string and an integer
// - All song titles are unique
// - The length of the string in each song is at most `50`
// - `1 <= k <= 10^5`

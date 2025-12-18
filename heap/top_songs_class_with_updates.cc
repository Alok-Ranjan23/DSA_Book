#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class TopSongs {
  int k_;
  priority_queue<pair<int,string>> pq;
  unordered_map<string,int> umap;
  public:
  TopSongs(int k);
  void register_plays(const string&,int);
  vector<string> top_k();
};

TopSongs::TopSongs(int k): k_{k},pq{} {}

void TopSongs::register_plays(const string& title,int count) {
  int newTotalPlays = count;
  if (umap.count(title)) {
    newTotalPlays += umap[title];
  }
  umap[title] = newTotalPlays;
  pq.push({newTotalPlays, title});
}

vector<string> TopSongs::top_k() {
  vector<string> res;
  while (res.size() < static_cast<size_t>(k_) && !pq.empty()) {
    auto [count, title] = pq.top();
    pq.pop();
    if (umap[title] == count) {
      res.push_back(title);
    }
  }
  for (const auto& title : res) {
    pq.push({umap[title], title});
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  TopSongs s = TopSongs(3);
  s.register_plays("Boolean Rhapsody", 100);
  s.register_plays("Boolean Rhapsody", 193);
  s.register_plays("Coding In The Deep", 75);
  s.register_plays("Coding In The Deep", 75);
  s.register_plays("All About That Base Case", 200);
  s.register_plays("All About That Base Case", 90);
  s.register_plays("All About That Base Case", 1);
  s.register_plays("Here Comes The Bug", 223);
  s.register_plays("Oops! I Broke Prod Again", 274);
  s.register_plays("All the Single Brackets", 132);
  for(auto& title : s.top_k()) cout<<title<<"\n";
  return 0;
}

// # Top Songs Class With Updates

// Implement a `TopSongs` class that receives an integer `k > 0` during initialization and has two methods:

// - `register_plays(title, plays)` indicates that a song was played a given number of times. It returns nothing. If the song was already registered, the new plays should be **added** to the total number of plays for that song.
// - `top_k()` returns the (up to) `k` registered song titles with the most plays, in any order, and breaking ties arbitrarily.

// Example:
// s = TopSongs(3)
// s.register_plays("Boolean Rhapsody", 100)
// s.register_plays("Boolean Rhapsody", 193)  # Total 293
// s.register_plays("Coding In The Deep", 75)
// s.register_plays("Coding In The Deep", 75)  # Total 150
// s.register_plays("All About That Base Case", 200)
// s.register_plays("All About That Base Case", 90)  # Total 290
// s.register_plays("All About That Base Case", 1)   # Total 291
// s.register_plays("Here Comes The Bug", 223)
// s.register_plays("Oops! I Broke Prod Again", 274)
// s.register_plays("All the Single Brackets", 132)
// s.top_k()  # Returns ["All About That Base Case", "Boolean Rhapsody", "Oops! I Broke Prod Again"]

// Analyze the space and runtime of each operation in terms of the number of songs registered so far. The goal is to minimize the total runtime assuming we will make the same number of operations of each type and that `k` will be relatively small compared to the number of songs.

// Constraints:

// - `0 < k < 1000`
// - Song titles are unique and have at most `50` characters.
// - Each time a song is registered, the number of plays is at least `1`.
// - The total number of plays for a song never exceeds `10^9`.

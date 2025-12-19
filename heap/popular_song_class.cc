#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

class PopularSongs {
  unordered_map<string,int> umap;
  priority_queue<int> max_pq;
  priority_queue<int,vector<int>,greater<int>> min_pq;
  public:
  void register_plays(const string& title, int plays);
  bool is_popular(const string& title);
};

//O(logn)
void PopularSongs::register_plays(const string& title, int plays) {
  umap[title] = plays;
  max_pq.push(plays);
  min_pq.push(max_pq.top());max_pq.pop();
  if(max_pq.size()<min_pq.size()) {
    max_pq.push(min_pq.top());min_pq.pop();
  }
}

//O(1)
bool PopularSongs::is_popular(const string& title) {
  if(!umap.count(title)) return false;
  int playCount = umap[title];
  int median = (max_pq.size()>min_pq.size())?max_pq.top():(max_pq.top() + min_pq.top())/2;
  return median<playCount;
}

// To execute C++, please define "int main()"
int main() {
  PopularSongs p = PopularSongs();
  cout<<boolalpha;
  p.register_plays("Boolean Rhapsody", 193);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns False
  p.register_plays("Coding In The Deep", 140);
  p.register_plays("All the Single Brackets", 132);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns True
  cout<<p.is_popular("Coding In The Deep")<<"\n"; // Returns False
  cout<<p.is_popular("All the Single Brackets")<<"\n"; // Returns False
  p.register_plays("All About That Base Case", 291);
  p.register_plays("Oops! I Broke Prod Again", 274);
  p.register_plays("Here Comes The Bug", 223);
  cout<<p.is_popular("Boolean Rhapsody")<<"\n"; // Returns False
  cout<<p.is_popular("Here Comes The Bug")<<"\n"; // Returns True
  return 0;
}

// # Popular Songs Class

// Implement a `PopularSongs` class that has two methods:

// - `register_plays(title, plays)` indicates that a song was played a given number of times. It returns nothing. The method is never called with the same title twice.
// - `is_popular(title)` returns whether the given song is popular. A song is _popular_ if its play count is strictly higher than the median play count.

// The median of a collection of integers with odd size is the middle element in sorted order; if the size is even, the median is the average of the two middle elements.

// Example:

// p = PopularSongs()
// p.register_plays("Boolean Rhapsody", 193)
// p.is_popular("Boolean Rhapsody")                   # Returns False
// p.register_plays("Coding In The Deep", 140)
// p.register_plays("All the Single Brackets", 132)
// p.is_popular("Boolean Rhapsody")                   # Returns True
// p.is_popular("Coding In The Deep")                 # Returns False
// p.is_popular("All the Single Brackets")            # Returns False
// p.register_plays("All About That Base Case", 291)
// p.register_plays("Oops! I Broke Prod Again", 274)
// p.register_plays("Here Comes The Bug", 223)
// p.is_popular("Boolean Rhapsody")                   # Returns False
// p.is_popular("Here Comes The Bug")                 # Returns True

// Analyze the space and runtime of each operation in terms of the number of songs registered so far. The goal is to minimize the total runtime assuming we will make the same number of operations of each type.

// Constraints:

// - Song titles are unique and have at most `50` characters.
// - The number of plays is at least `1` and at most `10^9`.
// - The number of registered songs is at most `10^5`.

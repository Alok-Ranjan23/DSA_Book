#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

/*
   ip: aabbbcccc
   op: [c,b,a]  {c:4,b:3,a:2}
   //frequency sort
   
   a,b,c
  [2,3,4]:26 charcter  UMAP vs counting array
   
  [{a:2},{b:3},{c:4}]   UMAP
  traverse UMAP
  //O(26log26) --- O(26)
  {
{(4,c),(3,b),(2,a)}
  }

   **BUCKET SORT**
      K largest element
      K smallest element


    *QuickSelect -- O(N)

    a b c
   [2,3,4]
   

   [1,2,3,4]
   [  a b c] -- vector<pair<int,set<int>>
      d                <-

      O(26+ O(N))

O(Nlogk) ----> O(N) with bucket sort
 0,1,2,
[0,{},{a,z}]
  aabcdefghijklmnopqrstuvwxyzz
O(26 + O(2))
   [1,2]
    b a
    c z
    d
    e
    f
[2,..........................2]
*/

/*
Time Complexity: O(N+K) = O(N), N is number of char in input
Space Complexity: O(N) 
*/
vector<char> sort_by_freq(string& input) {
  //Step1: Frquency Count: O(N), N: input size
  vector<int> counter(26,0);
  int highest_count = 0;
  for(auto &c: input) {
    highest_count = max(highest_count, ++counter[c-'a']);
  }

  //Step2: Bucket created: n size and to address same count, we have queue
  vector<queue<int>> bucket (highest_count + 1);

  //Step3: Fill buckets: pick queue based on count(i.e. index) and push index(chars) into them.
  //       Scanning from index=0 to 25 preserve lexciographical order in same count value.
  //T(n) belongs to O(26):: O(K)
  for(int i=0;i<26;++i) {
    if(counter[i]!=0) {
      bucket[counter[i]].push(i);
    }
  }

  //Step4: Traverse from last index(highest count value) and if queue not empty push those    character into result. : O(N)
  vector<char> results;
  for(int i=highest_count;i>0;--i) {
    while(!bucket[i].empty()) {  
      results.push_back(bucket[i].front()+'a'); 
      bucket[i].pop();
    }
  }
  return results;
}


// To execute C++, please define "int main()"
int main() {
  string word = "supercalifragilisticexpialidocious";
  vector<char> res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";
  word = "aabbbcccc";
  res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";
  word = "abc";
  res = sort_by_freq(word);
  for(auto&x : res) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

// # Sorting By Frequency

// Given a string, `word`, consisting of lowercase letters only, return a sorted array with all the letters in `word` sorted from most frequent to least frequent. If two frequencies are the same, break the tie alphabetically.

// Example 1: word = "supercalifragilisticexpialidocious"
// Output: ['i', 'a', 'c', 'l', 's', 'e', 'o', 'p', 'r', 'u', 'd', 'f', 'g', 't', 'x']

// Example 2: word = "aabbbcccc"
// Output: ['c', 'b', 'a']. 'c' appears 4 times, 'b' appears 3 times, and 'a' appears 2 times.

// Example 3: word = "abc"
// Output: ['a', 'b', 'c']. All letters appear once, so they are sorted alphabetically.

// Constraints:

// - The length of `word` is at most `10^5`
// - `word` contains only lowercase letters

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
using namespace std;


/*  -- O(n)
 * 15 4 13 8 10 5 2 3 9 11,    k=8
 *         pv
 *
 * s = {4,5,2,3}
 * e = {8}
 * g = {15,13,10,9,11}
 *
 * 
 * */

int quickselect(std::vector<int>& arr, int k) {
  size_t n = arr.size();
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dis(0, n-1);
  int pivot = arr[dis(gen)];
  
  vector<int> smaller,equal,larger;
  for(auto&x: arr) {
    if(x<pivot) smaller.push_back(x);
    else if(x==pivot) equal.push_back(x);
    else larger.push_back(x);
  }
  int S = smaller.size();
  int E = equal.size();

  if (k <= S) {
    return quickselect(smaller, k);
  } else if (k <= S + E) {
    return equal[0];
  }
  return quickselect(larger, k - S - E);
}

vector<int> find_k(vector<int>& arr,int k) {
  int kthVal = quickselect(arr, k);
  std::vector<int> result;
  for (int x : arr) {
    if (x <= kthVal) {
      result.push_back(x);
    }
  }
  return result;
}


vector<int> find_k_max_heap2(vector<int>& arr,int k) {
  priority_queue<int> pq;
  int n = arr.size();
  for(int i=0;i<n;++i) {
    pq.push(arr[i]);
    if(pq.size()>static_cast<size_t>(k)) pq.pop();
  }
  vector<int> res;
  while(!pq.empty()) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

vector<int> find_k_max_heap(vector<int>& arr,int k) {
  priority_queue<int> pq {arr.begin(),arr.begin()+k};
  int n = arr.size();
  for(int i=k;i<n;++i) {
    if(arr[i]<pq.top()) {
      pq.pop();pq.push(arr[i]);
    }
  }
  vector<int> res;
  while(!pq.empty()) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

vector<int> find_k_min_heap(vector<int>& arr,int k) {
  priority_queue<int,vector<int>,greater<int>> pq {arr.begin(),arr.end()};
  vector<int> res;
  while(!pq.empty() && k--) {
    res.push_back(pq.top());pq.pop();
  }
  return res;
}

vector<int> find_k_sorting(vector<int>& arr,int k) {
  sort(arr.begin(),arr.end());
  return vector<int>(arr.begin(),arr.begin()+k);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr {15, 4, 13, 8, 10, 5, 2, 20, 3, 9, 11, 27};int k=5;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";
  arr = {5,3,1,4,2};k=1;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";
  arr = {5,3,1,4,2};k=4;
  for(auto&x: find_k(arr,k))cout<<x<<" ";
  cout<<"\n";
  return 0;
}

// Your previous Plain Text content is preserved below:

// Hello! Your interview question is below. Write code in this pad just like you would normally – your AI Interviewer will be able to see it.

// # First K

// Given an array of `n` unique integers, `arr`, return the `k` smallest numbers, in any order.

// Example 1: arr = [15, 4, 13, 8, 10, 5, 2, 20, 3, 9, 11, 27], k = 5
// Output: [4, 3, 2, 5, 8]. The order doesn't matter.

// Example 2: arr = [5, 3, 1, 4, 2], k = 1
// Output: [1]. The smallest element.

// Example 3: arr = [5, 3, 1, 4, 2], k = 4
// Output: [1, 2, 3, 4]. All elements except the largest one.

// Constraints:

// - `0 ≤ k ≤ n ≤ 10^5`
// - All elements in `arr` are unique
// - Each element in `arr` is between `-10^9` and `10^9`

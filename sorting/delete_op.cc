#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> delete_op(vector<int>& nums,vector<int>& op) {
  vector<int> include_index;
  unordered_set<int> exclude;
  
  int n = nums.size();
  for(int i=0;i<n;++i) include_index.push_back(i);
  
  stable_sort(include_index.begin(), include_index.end(), [&nums](const int& i, const int& j)
   {return nums[i]<nums[j];});
  
  int smallIdx = 0;
  for(auto& o: op) {
    if(o>=0 && o<n) exclude.insert(o);
    else {
      while(smallIdx<n && exclude.count(include_index[smallIdx])) {
        smallIdx++;
      } 
      if(smallIdx<n) {
        exclude.insert(include_index[smallIdx]);
        smallIdx++;
      }
    }
  }

  std::vector<int> res;
  for (int i = 0; i < n; i++) {
    if (!exclude.count(i)) {
      res.push_back(nums[i]);
    }
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> nums {50,30,70,20,80};
  vector<int> op {2,-1,4,-1};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";
  nums = {1,2,3};
  op = {};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";
  nums = {1,2,3};
  op = {-1,-1,-1};
  for (auto&x : delete_op(nums,op)) cout<<x<<" ";
  cout<<"\n";
  return 0;
}

// # Delete Operations

// You're given an array of `n` integers, `nums`, and another array of at most `n` integers, `operations`, where each integer represents an _operation_ to be performed on `nums`.

// - If the operation number is `k ≥ 0`, the operation is "delete the number at index `k` in the **original** array if it has not been deleted yet. Otherwise, do nothing."
// - If the operation number is `-1`, the operation is "delete the smallest number in `nums` that has not been deleted yet, breaking ties by smaller index."

// Return the state of `nums` after applying all the operations. Every number in operations is guaranteed to be between `-1` and `n-1` inclusive.

// Example 1: nums = [50, 30, 70, 20, 80], operations = [2, -1, 4, -1]
// Output: [50]
// Explanation:
// - Delete index 2 in the original array, element 70: [50, 30, 20, 80]
// - Delete 20, the smallest non-deleted number: [50, 30, 80]
// - Delete index 4 in the original array, element 80: [50, 30]
// - Delete 30, the smallest non-deleted number: [50]

// Example 2: nums = [1, 2, 3], operations = []
// Output: [1, 2, 3]. No operations to perform.

// Example 3: nums = [1, 2, 3], operations = [-1, -1, -1]
// Output: []. All elements are deleted.

// Constraints:

// - `1 ≤ n ≤ 10^5`
// - Each element in `nums` is between `-10^9` and `10^9`
// - `operations.length ≤ n`
// - Each element in `operations` is between `-1` and `n-1`

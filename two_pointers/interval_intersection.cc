/**
 * @file interval_intersection.cc
 * @brief Find intersection of two lists of intervals using two pointers
 * 
 * This file implements interval intersection algorithm that finds all
 * overlapping regions between two sorted lists of non-overlapping intervals.
 * 
 * Key Concepts:
 * - Two Pointer Technique: One pointer for each interval list
 * - Interval overlap detection: max(starts) <= min(ends)
 * - Advancing the pointer whose interval ends first
 * 
 * Time Complexity: O(n + m) where n and m are list lengths
 * Space Complexity: O(k) where k is the number of intersections
 * 
 * Algorithm:
 * - For each pair of intervals, compute potential intersection
 * - Intersection exists if max(start1, start2) <= min(end1, end2)
 * - Advance the pointer whose interval ends first (exhausted interval)
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Finds all intersections between two lists of intervals
 * @param arr1 First list of non-overlapping sorted intervals
 * @param arr2 Second list of non-overlapping sorted intervals
 * @return Vector of intervals representing all intersections
 * 
 * Each interval is represented as pair<int,int> where first=start, second=end.
 * The algorithm advances pointers based on which interval ends first.
 */
vector<pair<int,int>> interval_intersection(vector<pair<int,int>>& arr1,
                                            vector<pair<int,int>>& arr2) {
  vector<pair<int,int>> res;
  int n1 = arr1.size();
  int n2 = arr2.size();
  int i=0,j=0;
  while(i<n1 && j<n2) {
    int first  = max(arr1[i].first,arr2[j].first);
    int second = min(arr1[i].second,arr2[j].second);
    if(first<=second) res.push_back({first,second});
    if(second == arr2[j].second) j++;
    if(second == arr1[i].second) i++;
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  vector<pair<int,int>> arr1 {{0,1},{4,6},{7,8}};
  vector<pair<int,int>> arr2 {{2,3},{5,9},{10,11}};
  for(auto& p: interval_intersection(arr1,arr2)) cout<<p.first<<" "<<p.second<<"\n";
  cout<<"\n";
  arr1 = {{2,4},{5,8}};
  arr2 = {{3,3},{4,7}};
  for(auto& p: interval_intersection(arr1,arr2)) cout<<p.first<<" "<<p.second<<"\n";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Interval Intersection
 * 
 * In this problem, we represent an interval as an array with two integers,
 * [start, end], where start <= end. Both endpoints are considered part of
 * the interval, which may consist of a singular point if start == end.
 * 
 * You are given two arrays of intervals, arr1 and arr2. For each array, the
 * intervals are non-overlapping (they don't even share an endpoint) and
 * sorted from left to right. Return a similarly non-overlapping, sorted
 * array of intervals representing the intersection of the intervals in
 * arr1 and arr2.
 * 
 * Example 1:
 * Input:
 * arr1 = [[0, 1], [4, 6], [7, 8]]
 * arr2 = [[2, 3], [5, 9], [10, 11]]
 * Output: [[5, 6], [7, 8]]
 * Explanation:
 * - [4, 6] from arr1 intersects with [5, 9] from arr2 to give [5, 6]
 * - [7, 8] from arr1 intersects with [5, 9] from arr2 to give [7, 8]
 * 
 * Example 2:
 * Input:
 * arr1 = [[2, 4], [5, 8]]
 * arr2 = [[3, 3], [4, 7]]
 * Output: [[3, 3], [4, 4], [5, 7]]
 * 
 * Constraints:
 * - 0 ≤ arr1.length, arr2.length ≤ 10^6
 * - arr1[i].length = arr2[j].length = 2
 * - -10^9 ≤ start ≤ end ≤ 10^9 for each interval
 * - Each list is sorted and non-overlapping
 * 
 *============================================================================*/

/**
 * @file count_unique_sum_zero.cc
 * @brief Count unique submultisets with sum equal to zero
 * 
 * This file implements a backtracking solution to count the number of
 * unique submultisets of a multiset that have a sum of zero. A multiset
 * allows duplicate elements, and we count based on VALUES not positions.
 * 
 * Key Concepts:
 * - Multiset: a set that allows repeated elements
 * - Submultiset: obtained by removing any number of elements
 * - Uniqueness based on element VALUES, not their positions
 * - Group identical elements and decide how many copies to include
 * 
 * Time Complexity: O(∏(count_i + 1)) where count_i is frequency of each unique value
 *   - For n elements with k unique values: worst case O((n/k + 1)^k)
 *   - With n ≤ 20, this is manageable
 * 
 * Space Complexity: O(k) where k = number of unique values
 *   - Map to store counts: O(k)
 *   - Recursion stack: O(k) depth
 * 
 * Algorithm Insight:
 * Instead of generating 2^n subsets and deduplicating, we:
 * 1. Group elements by value and count occurrences
 * 2. For each unique value, decide how many copies to include (0 to count)
 * 3. This naturally generates only unique submultisets
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;

/** Global counter for submultisets with sum zero */
int count_result = 0;

/**
 * @brief Recursive backtracking function to count zero-sum submultisets
 * 
 * @param items    Vector of (value, count) pairs for each unique element
 * @param index    Current index in items being processed
 * @param curr_sum Running sum of the current submultiset
 * 
 * Algorithm:
 * 1. Base case: if processed all unique values, check if sum is 0
 * 2. For current value, try including 0, 1, 2, ..., count copies
 * 3. Recurse to next unique value for each choice
 * 
 * Example: items = [(-1, 2), (1, 2)] means two -1s and two 1s
 * We try: 0×(-1), 1×(-1), 2×(-1) combined with 0×1, 1×1, 2×1
 */
void solve(vector<pair<int, int>>& items, int index, int curr_sum) {
    // Base case: processed all unique values
    if (index == (int)items.size()) {
        if (curr_sum == 0) {
            count_result++;  // Found a valid zero-sum submultiset
        }
        return;
    }
    
    int val = items[index].first;   // Current unique value
    int cnt = items[index].second;  // How many copies available
    
    // EXPLORE: Try including 0, 1, 2, ..., cnt copies of this value
    for (int i = 0; i <= cnt; i++) {
        solve(items, index + 1, curr_sum + i * val);
    }
}

/**
 * @brief Wrapper function to count unique zero-sum submultisets
 * 
 * @param S The input multiset (array with possible duplicates)
 * @return Number of unique submultisets with sum = 0
 * 
 * Steps:
 * 1. Group elements by value using a map
 * 2. Convert to vector of (value, count) pairs
 * 3. Use backtracking to explore all combinations
 */
int count_unique_sum_zero(vector<int>& S) {
    // Step 1: Group elements by value and count occurrences
    map<int, int> counts;
    for (int x : S) {
        counts[x]++;
    }
    
    // Step 2: Convert to vector for easier indexed access
    vector<pair<int, int>> items(counts.begin(), counts.end());
    
    // Step 3: Reset counter and solve
    count_result = 0;
    solve(items, 0, 0);
    
    return count_result;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
    // Example 1: S = [1, 1, -1, -1]
    // Unique zero-sum submultisets: [], [1, -1], [1, 1, -1, -1]
    // Count: 3
    vector<int> S1 = {1, 1, -1, -1};
    cout << "S = [1, 1, -1, -1]" << endl;
    cout << "Unique zero-sum submultisets: " << count_unique_sum_zero(S1) << endl;
    cout << "(Expected: 3 -> [], [1,-1], [1,1,-1,-1])" << endl << endl;
    
    // Example 2: S = []
    // Unique zero-sum submultisets: []
    // Count: 1
    vector<int> S2 = {};
    cout << "S = []" << endl;
    cout << "Unique zero-sum submultisets: " << count_unique_sum_zero(S2) << endl;
    cout << "(Expected: 1 -> [])" << endl << endl;
    
    // Example 3: S = [-1, 2, 1, 0, 3]
    // Unique zero-sum submultisets: [], [0], [-1, 1], [-1, 0, 1]
    // Count: 4
    vector<int> S3 = {-1, 2, 1, 0, 3};
    cout << "S = [-1, 2, 1, 0, 3]" << endl;
    cout << "Unique zero-sum submultisets: " << count_unique_sum_zero(S3) << endl;
    cout << "(Expected: 4 -> [], [0], [-1,1], [-1,0,1])" << endl;
    
    return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Count Unique Submultisets With Sum Zero
 * 
 * A _multiset_ is a set that allows repeated elements. A _submultiset_ of
 * a multiset S is another multiset obtained by removing any number of
 * elements from S.
 * 
 * We are given an array with n integers representing a multiset (it can
 * have duplicates).
 * 
 * Return the number of **unique** submultisets of S with sum 0, ignoring
 * which position in S the values came from.
 * 
 * Example 1: S = [1, 1, -1, -1]
 * Output: 3. The unique submultisets with sum 0 are [], [1, 1, -1, -1]
 * and [1, -1]. The last one can be obtained in more than one way.
 * 
 * Example 2: S = []
 * Output: 1. [] is a submultiset of [] with sum 0.
 * 
 * Example 3: S = [-1, 2, 1, 0, 3]
 * Output: 4. The unique submultisets with sum 0 are [-1, 1], [-1, 1, 0],
 * [0], and [].
 * 
 * Constraints:
 * - The length of S is at most 20.
 * - The elements in S are integers.
 * 
 *============================================================================*/

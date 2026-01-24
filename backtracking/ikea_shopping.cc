/**
 * @file ikea_shopping.cc
 * @brief Maximize style ratings within budget using 0/1 Knapsack backtracking
 * 
 * This file implements the classic 0/1 Knapsack problem using backtracking.
 * Given items with prices and style ratings, select items to maximize total
 * rating without exceeding the budget. Each item can only be picked once.
 * 
 * Key Concepts:
 * - 0/1 Knapsack: each item is either taken (1) or not taken (0)
 * - Binary decision tree: include or exclude each item
 * - Constraint: total price must not exceed budget
 * - Objective: maximize total style rating
 * 
 * Time Complexity: O(2^n) where n = number of items
 *   - Each item has 2 choices (take or skip)
 *   - Pruning: skip items that exceed remaining budget
 * 
 * Space Complexity: O(n) for recursion stack and current selection
 * 
 * Comparison with DP approach:
 * - Backtracking: O(2^n) time, O(n) space, returns actual items
 * - DP: O(n * budget) time, O(n * budget) space, returns max value
 * - For small n (≤15), backtracking is simpler and sufficient
 */

#include <iostream>
#include <vector>
using namespace std;

/** Global vector to store the best selection of item indices */
vector<int> ans {};

/** Global variable to store the maximum rating achieved */
float final_rating = 0.0f;

/**
 * @brief Recursive backtracking function for 0/1 Knapsack
 * 
 * @param prices       Array of item prices
 * @param rating       Array of item style ratings
 * @param budget       Remaining budget
 * @param index        Current item index being considered
 * @param n            Total number of items
 * @param curr         Current selection (list of indices)
 * @param total_rating Running sum of ratings for current selection
 * 
 * Algorithm:
 * 1. Base case: if index == n, check if current selection is best
 * 2. For current item:
 *    a. If affordable: try TAKING it (add to selection, recurse)
 *    b. Always try SKIPPING it (don't add, recurse)
 * 
 * Pruning: Only consider taking an item if it fits in remaining budget
 */
void solve(vector<int>& prices, vector<float>& rating, int budget, 
           int index, int n, vector<int>& curr, float& total_rating) {
  // Base case: considered all items
  if(index == n) {
    // Update best solution if current is better
    if(total_rating > final_rating) {
      final_rating = total_rating;
      ans = vector<int>(curr);  // Store copy of current selection
    }
    return;
  }
  
  // Branch 1: TAKE current item (only if affordable)
  if(prices[index] <= budget) {
    curr.push_back(index);                    // CHOOSE: select this item
    total_rating += rating[index];            // Add rating
    solve(prices, rating, budget - prices[index], index+1, n, curr, total_rating);
    total_rating -= rating[index];            // UNCHOOSE: remove rating
    curr.pop_back();                          // Remove from selection
  }
  
  // Branch 2: SKIP current item (always possible)
  solve(prices, rating, budget, index+1, n, curr, total_rating);
  
  return;
}

/**
 * @brief Wrapper function for IKEA shopping optimization
 * 
 * @param prices Array of item prices
 * @param rating Array of item style ratings (0-10)
 * @param budget Total budget available
 * 
 * Result stored in global variables: ans (indices) and final_rating (sum)
 */
void ikea_shopping(vector<int>& prices, vector<float>& rating, int budget) {
  vector<int> curr;        // Current selection being built
  float total_rating = 0;  // Rating sum for current selection
  int n = rating.size();
  solve(prices, rating, budget, 0, n, curr, total_rating);
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: Budget = 20
  // Items: [10, 5, 15, 8, 3] prices, [7.0, 3.5, 9.0, 6.0, 2.0] ratings
  // Best: items [0, 3] -> price=18, rating=13.0
  int budget = 20;
  vector<int> prices {10, 5, 15, 8, 3};
  vector<float> rating {7.0, 3.5, 9.0, 6.0, 2.0};
  ikea_shopping(prices, rating, budget);
  
  cout << "Budget: " << budget << "\n";
  cout << "Prices:  [10, 5, 15, 8, 3]\n";
  cout << "Ratings: [7.0, 3.5, 9.0, 6.0, 2.0]\n";
  cout << "Total Rating: " << final_rating << "\n";
  cout << "Selected Items: [";
  for(size_t i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if(i < ans.size() - 1) cout << ", ";
  }
  cout << "]\n\n";
  
  // Example 2: Budget = 10
  // Items: [2, 3, 4, 5] prices, [1.0, 2.0, 3.5, 4.0] ratings
  // Best: items [2, 3] -> price=9, rating=7.5
  ans = vector<int>();
  final_rating = 0;
  budget = 10;
  prices = {2, 3, 4, 5};
  rating = {1.0, 2.0, 3.5, 4.0};
  ikea_shopping(prices, rating, budget);
  
  cout << "Budget: " << budget << "\n";
  cout << "Prices:  [2, 3, 4, 5]\n";
  cout << "Ratings: [1.0, 2.0, 3.5, 4.0]\n";
  cout << "Total Rating: " << final_rating << "\n";
  cout << "Selected Items: [";
  for(size_t i = 0; i < ans.size(); i++) {
    cout << ans[i];
    if(i < ans.size() - 1) cout << ", ";
  }
  cout << "]\n";
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # IKEA Shopping
 * 
 * A magazine has rated every IKEA item from 1 to 10 in terms of style.
 * We have gone to IKEA with a limited budget and the goal of maximizing
 * the sum of style ratings of the items we buy. We also don't want to
 * pick more than one of each item. We are given 3 things:
 * 
 * - `budget`, a positive integer,
 * - `prices`, an array of n positive integers,
 * - `ratings`, an array of n positive floating-point numbers (0 to 10).
 * 
 * There are n items. Item i has price prices[i] and style rating ratings[i].
 * Return an array with the indices of the items that we should buy.
 * 
 * Example 1:
 * budget = 20
 * prices =  [10,  5,   15,  8,   3]
 * ratings = [7.0, 3.5, 9.0, 6.0, 2.0]
 * Output: [0, 3]. Items 0 and 3 give rating sum of 13 within budget.
 * 
 * Example 2:
 * budget = 10
 * prices =  [2,   3,   4,   5]
 * ratings = [1.0, 2.0, 3.5, 4.0]
 * Output: [2, 3]
 * 
 * Constraints:
 * - n <= 15
 * - budget <= 10^6
 * - prices[i] <= 10^4 for all i
 * - ratings[i] is a floating-point number between 0 and 10 (inclusive)
 * 
 *============================================================================*/

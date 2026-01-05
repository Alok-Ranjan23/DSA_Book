/**
 * @file min_pages_per_day.cc
 * @brief Binary Search on Answer - Minimum pages per day to finish reading
 * 
 * This file implements "binary search on the answer" pattern to find the
 * minimum number of pages that must be read daily to finish all chapters
 * within a given number of days.
 * 
 * Key Concepts:
 * - Binary search on answer space, not array indices
 * - Monotonic feasibility: if X pages/day works, X+1 also works
 * - Greedy validation: check if a given rate is feasible
 * - Similar to "Capacity to Ship Packages" or "Split Array Largest Sum"
 * 
 * Time Complexity: O(n * log(max_pages))
 *   - Binary search: O(log(max_pages))
 *   - Validation: O(n) for each binary search iteration
 * Space Complexity: O(1)
 * 
 * Algorithm Pattern: Binary Search on Answer + Greedy Validation
 * 
 * Search space: [1, max(page_counts)]
 *   - Minimum: 1 page/day (slowest possible)
 *   - Maximum: max chapter size (can finish any chapter in 1 day)
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*============================================================================
 * VALIDATION FUNCTION
 *============================================================================*/

/**
 * @brief Checks if reading 'mid' pages per day allows finishing within 'days'
 * @param page_counts Array of page counts for each chapter
 * @param mid Pages to read per day (candidate answer)
 * @param days Maximum days available
 * @return true if we can finish all chapters within 'days'
 * 
 * Algorithm:
 * For each chapter with P pages, reading at rate R pages/day:
 *   - Days needed = ceil(P / R) = P/R + (P%R != 0)
 *   - Note: We finish a chapter and rest, don't start next same day
 * 
 * Total days = sum of days needed for each chapter
 * Valid if total_days <= days
 * 
 * Example: page_counts = [20, 15, 17, 10], mid = 5
 *   Chapter 1: ceil(20/5) = 4 days
 *   Chapter 2: ceil(15/5) = 3 days
 *   Chapter 3: ceil(17/5) = 4 days (17 = 5+5+5+2)
 *   Chapter 4: ceil(10/5) = 2 days
 *   Total = 13 days
 */
bool isValid(vector<int>& page_counts, int mid, int days) {
  int days_taken = 0;
  
  for(auto& x : page_counts) {
    // Ceiling division: days for this chapter = ceil(x / mid)
    days_taken += x / mid + (x % mid != 0);
  }
  
  return days_taken <= days;
}

/*============================================================================
 * BINARY SEARCH ON ANSWER
 *============================================================================*/

/**
 * @brief Finds minimum pages per day to finish all chapters within deadline
 * @param page_counts Array of page counts for each chapter
 * @param days Number of days until the interview
 * @return Minimum pages that must be read daily
 * 
 * Algorithm:
 * Binary search on the answer (pages per day):
 * 1. Search range: [1, max(page_counts)]
 *    - Lower bound: 1 (minimum possible rate)
 *    - Upper bound: largest chapter (guarantees any chapter in 1 day)
 * 
 * 2. For each candidate 'mid':
 *    - If isValid(mid): mid might be answer, try smaller (r = mid)
 *    - If not valid: need more pages/day (l = mid + 1)
 * 
 * 3. Return l (or r, they converge to the minimum valid answer)
 * 
 * Why this works:
 * - Monotonic property: if X pages/day is enough, X+1 is definitely enough
 * - We binary search for the smallest X that is "enough"
 * 
 * Visual for page_counts = [20, 15, 17, 10], days = 14:
 *   Search: [1, 20]
 *   mid=10: 2+2+2+1=7 days <= 14 ✓, search [1, 10]
 *   mid=5:  4+3+4+2=13 days <= 14 ✓, search [1, 5]
 *   mid=3:  7+5+6+4=22 days > 14 ✗, search [4, 5]
 *   mid=4:  5+4+5+3=17 days > 14 ✗, search [5, 5]
 *   Answer: 5
 */
int min_pages_per_day(vector<int>& page_counts, int days) {
  int l = 1;
  int r = *max_element(page_counts.begin(), page_counts.end());
  
  while(l < r) {
    int mid = l + (r - l) / 2;
    
    if(isValid(page_counts, mid, days)) {
      r = mid;            // mid works, try to find smaller
    } else {
      l = mid + 1;        // mid doesn't work, need more pages/day
    }
  }
  
  return r;               // l == r == minimum valid answer
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example 1: 5 pages/day over 13 days
  vector<int> page_counts{20, 15, 17, 10};
  int days = 14;
  cout << min_pages_per_day(page_counts, days) << "\n";  // Output: 5
  
  // Example 2: Tight deadline requires 17 pages/day
  page_counts = {20, 15, 17, 10};
  days = 5;
  cout << min_pages_per_day(page_counts, days) << "\n";  // Output: 17
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT
 *============================================================================
 * 
 * # Min Pages Per Day
 * 
 * You have upcoming interviews and have selected specific chapters from 
 * BCtCI to read beforehand. Given an array, `page_counts`, where each 
 * element represents a chapter's page count, and the number of days, 
 * `days`, until your interview, determine the minimum number of pages 
 * you must read daily to finish on time. Assume that:
 * 
 * - You must read all the pages of a chapter before moving on to another.
 * - If you finish a chapter on a given day, you practice for the rest 
 *   of the day and don't start the next chapter until the next day.
 * - len(page_counts) <= days.
 * 
 * Example 1: page_counts = [20, 15, 17, 10], days = 14
 * Output: 5. We can read 5 pages daily and finish all chapters. At a 
 * maximum of 5 pages per day, we spend:
 * - 4 days on the first chapter.
 * - 3 days on the second chapter.
 * - 4 days on the third chapter (stopping when we finish early).
 * - 2 days on the fourth chapter.
 * In total, we spent 13 days reading 5 pages a day, which is the lowest 
 * amount we can read daily and still finish on time.
 * 
 * Example 2: page_counts = [20, 15, 17, 10], days = 5
 * Output: 17
 * 
 * Constraints:
 * - 1 <= len(page_counts) <= days <= 10^6
 * - 1 <= page_counts[i] <= 10^4
 * 
 *============================================================================*/

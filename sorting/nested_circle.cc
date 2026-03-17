/**
 * @file nested_circle.cc
 * @brief Determine if Circles are Nested using Sorting and Containment Check
 * 
 * This file implements a function that checks whether a set of circles are
 * "nested" — meaning they can be ordered such that each circle is completely
 * contained within the next larger one.
 * 
 * Key Concepts:
 * - Circle containment: Circle B is inside Circle A if
 *   distance(centerA, centerB) + radiusB <= radiusA
 * - Sorting by radius (descending) creates a candidate nesting order
 * - Only consecutive pairs need checking after sorting
 * 
 * Algorithm:
 * 1. Sort circles by radius in descending order (largest first)
 * 2. For each consecutive pair (i, i+1), check if circle[i] contains circle[i+1]
 * 3. If all consecutive containments hold, circles are nested
 * 4. If any check fails, they are not nested
 * 
 * Why sorting by radius works:
 * - If circles are nested, there's a unique ordering by size
 * - The largest circle must contain all others
 * - The second-largest must contain all except the largest, etc.
 * - Checking consecutive pairs is sufficient because containment is transitive
 * 
 * Containment formula:
 *   distance(A_center, B_center) + B_radius <= A_radius
 *   where distance = sqrt((x1-x2)^2 + (y1-y2)^2)
 * 
 * Time Complexity: O(n log n) for sorting + O(n) for containment checks
 * Space Complexity: O(1) auxiliary (sorting is in-place)
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

/** @brief Circle type: ((center_x, center_y), radius) */
using circle = pair<pair<int,int>,int>;

/**
 * @brief Checks if circle A completely contains circle B
 * @param a Outer circle (potential container)
 * @param b Inner circle (potential contained)
 * @return true if B is entirely within A (strict, no boundary touching)
 * 
 * Uses the Euclidean distance between centers plus the inner radius.
 * If this sum is <= the outer radius, the inner circle fits entirely within.
 * 
 * Geometric intuition: The farthest point of B from A's center is at
 * distance(A_center, B_center) + B_radius. This must be <= A_radius.
 */
bool contains(circle a, circle b) {
  auto centerA = a.first;
  auto radiusA = a.second;
  auto centerB = b.first;
  auto radiusB = b.second;
  double center_dist = sqrt((centerA.first-centerB.first) * (centerA.first-centerB.first) + (centerA.second-centerB.second) * (centerA.second-centerB.second));

  return center_dist + radiusB < radiusA;

}

/**
 * @brief Determines if all circles are nested (each inside the next larger one)
 * @param circles Vector of circles (modified: sorted by radius descending)
 * @return true if circles form a valid nesting, false otherwise
 * 
 * A single circle is trivially nested. For multiple circles, sorts by
 * radius descending and verifies each circle[i] contains circle[i+1].
 * 
 * Time Complexity: O(n log n) - dominated by the sort
 */
bool is_nested(vector<circle>& circles) {
  sort(circles.begin(), circles.end(), [](const circle& a,const circle& b){
    return a.second>b.second;
  });
  int n=circles.size();
  for(int i=0;i<n-1;++i) {
    if (!contains(circles[i],circles[i+1])) return false; 
  }
  return true;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Test 1: Two non-nested circles (neither contains the other)
  vector<circle> circles {
    {{4,4},5}, {{8,4},2}
  };
  std::cout << std::boolalpha;
  cout<<is_nested(circles)<<"\n";   // Expected: false
  
  // Test 2: Three nested circles
  circles = {
    {{4,4},5}, {{5,3},3}, {{5,3},2}
  };
  std::cout << std::boolalpha;
  cout<<is_nested(circles)<<"\n";   // Expected: true
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Nested Circles
 * 
 * You are given a non-empty array of circles, where each circle is specified
 * by its center coordinates (x, y) and its radius r. Determine whether the
 * circles are nested:
 * 
 * 1. A single circle is considered nested.
 * 2. One circle completely surrounds all the others (without touching
 *    boundaries), and the other circles are themselves nested (recursive).
 * 
 * Constraints:
 * - The length of circles is at most 10^4
 * - All coordinates and radii are integers between -10^4 and 10^4
 * 
 *============================================================================*/

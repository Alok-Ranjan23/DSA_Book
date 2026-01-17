/**
 * @file nested_array_sum.cc
 * @brief Calculate the sum of all integers in a nested array structure
 * 
 * A nested array is an array where each element is either:
 * 1. An integer, or
 * 2. Another nested array (recursive definition)
 * 
 * Key Concepts:
 * - Tree-like data structure using shared_ptr for memory management
 * - Recursive traversal to sum all leaf values
 * - Factory functions (Node) for cleaner syntax when constructing nested arrays
 * 
 * Time Complexity: O(n) where n is total number of elements (including nested)
 * Space Complexity: O(d) where d is maximum nesting depth (recursion stack)
 */

#include <initializer_list>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/**
 * @struct NestedArray
 * @brief Represents either a single integer value or a list of nested arrays
 * 
 * This is a variant-like structure:
 * - If is_value is true, this node holds an integer in value_
 * - If is_value is false, this node holds child nodes in arrays
 */
struct NestedArray {
  bool is_value;
  int value_;
  vector<shared_ptr<NestedArray>> arrays{};
  NestedArray(int value): is_value(true), value_(value) {}
  NestedArray(initializer_list<shared_ptr<NestedArray>> elems): is_value(false), value_(0), arrays(elems) {}
};

/*============================================================================
 * FACTORY FUNCTIONS - Syntactic sugar for cleaner nested array construction
 *============================================================================*/

/**
 * @brief Creates a leaf node containing an integer value
 * @param v The integer value to store
 * @return shared_ptr to the new NestedArray node
 */
shared_ptr<NestedArray> Node(int v) { 
    return make_shared<NestedArray>(v); 
}

/**
 * @brief Creates an internal node containing child nested arrays
 * @param l Initializer list of child NestedArray pointers
 * @return shared_ptr to the new NestedArray node
 */
shared_ptr<NestedArray> Node(initializer_list<shared_ptr<NestedArray>> l) { 
    return make_shared<NestedArray>(l); 
}

/**
 * @brief Recursively calculates the sum of all integers in a nested array
 * @param node Pointer to the root of the nested array structure
 * @return Sum of all integer values in the nested structure
 * 
 * Algorithm:
 * 1. Base case: null node returns 0
 * 2. If node is a value, return that value
 * 3. Otherwise, recursively sum all children
 */
long long calculateSum(shared_ptr<NestedArray> node) {
    if (!node) return 0;
    if (node->is_value) {
        return node->value_;
    }
    
    long long total = 0;
    for (auto& child : node->arrays) {
        total += calculateSum(child);
    }
    return total;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Example: [1, [2, 3], [4, [5]], 6]
  auto myArr = Node({
    Node(1),
    Node({Node(2), Node(3)}),
    Node({Node(4), Node({Node(5)})}),
    Node(6)
  });
  cout<<calculateSum(myArr)<<"\n";
  myArr = Node({
    Node(-1),
    Node({Node(-2), Node(3)}),
    Node({Node(4), Node({Node(-5)})}),
    Node(6)
  });
  cout<<calculateSum(myArr)<<"\n";
   myArr = Node({
    Node({}),
    Node({Node(1), Node(2)}),
    Node({}),
    Node({Node(3)})
  });
  cout<<calculateSum(myArr)<<"\n";
  myArr = Node({});
  cout<<calculateSum(myArr)<<"\n";
  myArr = Node({
    Node({Node({Node({Node(1)})}), Node(2)}),
  });
  cout<<calculateSum(myArr)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Nested Array Sum
 * 
 * A _nested array_ is an array where each element is either:
 * 1. An integer, or
 * 2. A nested array (note that this is a recursive definition).
 * 
 * The _sum_ of a nested array is defined recursively as the sum of all its 
 * elements. Given a nested array, `arr`, return its sum.
 * 
 * Example 1: arr = [1, [2, 3], [4, [5]], 6]
 * Output: 21
 * 
 * Example 2: arr = [[[[1]], 2]]
 * Output: 3
 * 
 * Example 3: arr = []
 * Output: 0
 * 
 * Example 4: arr = [[], [1, 2], [], [3]]
 * Output: 6
 * 
 * Example 5: arr = [-1, [-2, 3], [4, [-5]], 6]
 * Output: 5
 * 
 * Constraints:
 * - The array can be nested to depth at most 500
 * - Each integer in the array is between -10^9 and 10^9
 * - The total number of integers in the array (counting nested ones) is at 
 *   most 10^5
 * 
 *============================================================================*/

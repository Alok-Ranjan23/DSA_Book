/**
 * @file robot_instructions.cc
 * @brief Expand robot movement instructions with repetition operator '2'
 * 
 * Given a string of robot instructions containing 'L', 'R', and '2':
 * - 'L' and 'R' are direct movement commands
 * - '2' means: execute all following instructions twice, but skip the 
 *   immediate next instruction on the second pass
 * 
 * Key Concepts:
 * - Recursive string expansion based on position
 * - '2' creates branching: full suffix + suffix starting 2 positions ahead
 * - String concatenation builds the final expanded instruction sequence
 * 
 * Time Complexity: O(2^k * n) where k is number of '2's and n is string length
 *                  (each '2' can potentially double the output)
 * Space Complexity: O(2^k * n) for the result string + O(n) recursion stack
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Recursively expands robot instructions starting from given index
 * @param moves The original instruction string
 * @param index Current position in the string
 * @return Expanded instruction string (only 'L' and 'R' characters)
 * 
 * Algorithm:
 * 1. Base case: reached end of string, return empty string
 * 2. If current char is '2':
 *    - First pass: expand from index+1 (include next instruction)
 *    - Second pass: expand from index+2 (skip next instruction)
 *    - Return concatenation of both passes
 * 3. If current char is 'L' or 'R':
 *    - Add current char + expansion of rest of string
 * 
 * Example trace for "2LR":
 * - At index 0, char='2': return expand(1) + expand(2)
 * - expand(1): 'L' + expand(2) = 'L' + 'R' = "LR"
 * - expand(2): 'R' + expand(3) = 'R' + "" = "R"
 * - Result: "LR" + "R" = "LRR"
 */
string robot_instruction(const string& moves,int index) {
  if(static_cast<size_t>(index)==moves.size()) return "";
  if(moves[index]=='2') {
    return robot_instruction(moves, index+1) + robot_instruction(moves, index+2);
  }
  return moves[index] + robot_instruction(moves, index+1); 
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  cout<<robot_instruction("LL",0)<<"\n";
  cout<<robot_instruction("2LR",0)<<"\n";
  cout<<robot_instruction("2L",0)<<"\n";
  cout<<robot_instruction("22LR",0)<<"\n";
  cout<<robot_instruction("LL2R2L",0)<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Robot Instructions
 * 
 * We are given a string, `seq`, with a sequence of instructions for a robot.
 * The string consists of characters `'L'`, `'R'`, and `'2'`. The letters 'L' 
 * and 'R' instruct the robot to move left or right.
 * 
 * The character `'2'` (which never appears at the end of the string) means 
 * "perform all the instructions after this `'2'` twice, but skip the 
 * instruction immediately following the `'2'` during the second repetition." 
 * Output a string with the final list of left and right moves that the robot 
 * should do.
 * 
 * Example 1: seq = "LL"
 * Output: "LL"
 * 
 * Example 2: seq = "2LR"
 * Output: "LRR". The '2' indicates that we need to do "LR" first and then "R".
 * 
 * Example 3: seq = "2L"
 * Output: "L". The '2' indicates that we need to do "L" first and then "" 
 * (the empty string).
 * 
 * Example 4: seq = "22LR"
 * Output: "LRRLR". The first '2' indicates that we need to do "2LR" first 
 * and then "LR".
 * 
 * Example 5: seq = "LL2R2L"
 * Output: "LLRLL"
 * 
 * Constraints:
 * - The length of `seq` is at most `10^4`
 * - `seq` consists only of the characters `'L'`, `'R'`, and `'2'`
 * - `'2'` never appears at the end of `seq`
 * 
 *============================================================================*/

/**
 * @file cheater_detection.cc
 * @brief Find pairs of students who made identical mistakes and sit side by side
 *
 * Desks are numbered from 1 and laid out in rows of m. Two students are
 * "suspect" if they have the exact same answers (which, for a non-perfect
 * score, means identical mistakes) and sit immediately left/right of each
 * other in the same row. We map each desk to its occupant so that, for every
 * student, we can look up the neighbour to their right in O(1) and compare.
 *
 * Key Concepts:
 * - desk -> id and desk -> answers lookup tables (unordered_map)
 * - Converting a linear desk number to (row, col) via / and % by m
 * - "Identical mistakes" reduces to "identical answer arrays that differ from
 *   the answer key", so a perfect score is never suspect
 *
 * Indexing note: the maps are keyed by (desk - 1), so looking up the raw,
 * 1-indexed `desk` of a student actually retrieves the occupant of desk+1 --
 * i.e. their right-hand neighbour. The offset is intentional and consistent.
 *
 * Time Complexity: O(N * k)
 *   - N = number of students, k = length of the answer array. Building the
 *     maps copies each student's k answers: O(N*k). The second pass does, per
 *     student, a constant number of O(k) vector copies/compares plus O(1)
 *     average hash lookups: O(N*k). Hash ops are O(1) average (O(N) worst case
 *     under adversarial collisions).
 *
 * Space Complexity: O(N * k)
 *   - desk_to_answer stores N answer vectors of length k; desk_to_id stores N
 *     ints; the result holds up to O(N) pairs.
 */
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
using namespace std;

/// A student's id, 1-indexed desk number, and their k answer characters.
struct Students {
  int id;
  int desk;
  vector<char> answers;
};

/**
 * @brief Return all pairs of side-by-side students with identical mistakes
 *
 * @param answers The exam answer key (k characters)
 * @param m       Number of desks per row
 * @param students List of students (id, desk, answers)
 * @return Pairs {id_a, id_b} of suspect students; order is unspecified
 *
 * Algorithm:
 * 1. Map every desk (stored 0-indexed as desk-1) to its student id and answers.
 * 2. For each student at 1-indexed desk D, look up key D in the maps, which
 *    (because keys are desk-1) yields the right-hand neighbour at desk D+1.
 * 3. Skip perfect scores; report the pair when the two answer arrays match and
 *    is_adjacent confirms both desks share a row.
 *
 * Time:  O(N * k)   (see file header)
 * Space: O(N * k)
 */
//Time O(N * k)   (N students, k = answer length; O(1) average hash lookups)
//Space O(N * k)  (maps store N answer vectors of length k)
vector<pair<int,int>> cheater_detection(vector<char>& answers, int m, vector<Students>& students) {
  // True iff desk2 sits immediately to the right of desk1 in the same row.
  auto is_adjacent = [m](int desk1, int desk2) {
    int row1 = desk1 / m;
    int col1 = desk1 % m;
    int row2 = desk2 / m;
    int col2 = desk2 % m;
    return row1 == row2 && col1 + 1 == col2;
  };

  vector<pair<int,int>> res;
  unordered_map <int,int> desk_to_id;
  unordered_map<int, vector<char>> desk_to_answer;
  for(auto& student: students) {                       // O(N*k): copy answers
    desk_to_id[student.desk-1]     = student.id;
    desk_to_answer[student.desk-1] = student.answers; 
  }
  for(auto& student: students) {
    int id               = student.id;
    int desk             = student.desk;               // 1-indexed
    vector<char> answer1 = student.answers;
    if(answer1==answers) continue;                      // perfect score: not suspect
    // key == desk retrieves the occupant of desk+1 (the right neighbour)
    if(desk_to_answer.find(desk) == desk_to_answer.end()) continue;
    vector<char> answer2 = desk_to_answer[desk];
    if(answer1==answer2 && is_adjacent (desk-1, desk)) res.push_back({id,desk_to_id[desk]}); 
  }
  return res;
}

// To execute C++, please define "int main()"
int main() {
  // Example 1: 
  vector<char> answers = {'a', 'b', 'c', 'c'}; int m = 5; 
  vector<Students> students = {
    {4, 10, {'a', 'b', 'c', 'd'}},
    {1, 6, {'a', 'b', 'c', 'd'}},
    {3, 8, {'a', 'b', 'd', 'd'}},
    {5, 11, {'a', 'b', 'c', 'd'}},
    {9, 7, {'a', 'b', 'c', 'd'}},
    {6, 16, {'a', 'b', 'd', 'd'}}
  };
  vector<pair<int,int>> cheater_pair = cheater_detection(answers, m, students);
  for(auto& p : cheater_pair) cout<<p.first<<" "<<p.second<<"\n";
  cout<<" --------------------------------------- \n";
  // Example 2:
  answers = {'a', 'b'}, m = 2, 
  students = {
    {1, 1, {'a', 'b'}},
    {2, 2, {'a', 'b'}} 
  };
  cheater_pair = cheater_detection(answers, m, students);
  for(auto& p : cheater_pair) cout<<p.first<<" "<<p.second<<"\n";
  cout<<" --------------------------------------- \n";

  // Example 3: 
  answers = {'a', 'b'}, m = 2, 
  students = {
    {1, 1, {'b', 'b'}},
    {2, 2, {'b', 'b'}}
  };
  cheater_pair = cheater_detection(answers, m, students);
  for(auto& p : cheater_pair) cout<<p.first<<" "<<p.second<<"\n";
  cout<<" --------------------------------------- \n";

  return 0;
}

// # Cheater Detection

// You are given an array, `answers`, with the answers of a multi-choice test. The list has `k` characters (`'a'`, `'b'`, `'c'`, or `'d'`), where `k` is the number of questions in the exam.

// You are also given an array, `students`, of students' answers for the test. Each entry is a tuple `[student_id, desk, answers]`, where:

// - Student IDs are unique positive integers.
// - Desks are unique positive integers. Desks are arranged in rows of `m` desks, starting with desks `1` to `m` in the first row, `m+1` to `2m` in the second row, and so on. Not all desks may be occupied. E.g., there may be a student at desk `2` but none at desk `1`.
// - For each student, `answers` is an array of `k` characters (`'a'`, `'b'`, `'c'`, or `'d'`).

// Two students are considered _suspect_ if they have made **identical mistakes** and **sit next to each other** in the same row (we don't care about students in the front or behind one another).

// Return a list of all pairs of suspect students in any order (the order of the two students in a pair also doesn't matter).

// Example 1: answers = ['a', 'b', 'c', 'c'], m = 5, students = [
//     # student ID, desk, answers
//     (4, 10, ['a', 'b', 'c', 'd']),
//     (1, 6,  ['a', 'b', 'c', 'd']),
//     (3, 8,  ['a', 'b', 'd', 'd']),
//     (5, 11, ['a', 'b', 'c', 'd']),
//     (9, 7,  ['a', 'b', 'c', 'd']),
//     (6, 16, ['a', 'b', 'd', 'd'])
// ]
// Output: [[1, 9]]. Students 1 and 9 made the same mistakes and sit next to each other.

// Example 2: answers = ['a', 'b'], m = 2, students = [
//     (1, 1, ['a', 'b']),
//     (2, 2, ['a', 'b'])
// ]
// Output: []. Perfect scores are not suspicious.

// Example 3: answers = ['a', 'b'], m = 2, students = [
//     (1, 1, ['b', 'b']),
//     (2, 2, ['b', 'b'])
// ]
// Output: [[1, 2]]. Both students made the same mistake and sit next to each other.

// Constraints:

// - The length of `answers` is at most `10^5`
// - The length of `students` is at most `10^5`
// - All `answers` are 'a', 'b', 'c', or 'd'
// - All student IDs are unique positive integers
// - All desks are unique positive integers
// - `m` is a positive integer less than `10^5`

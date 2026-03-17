/**
 * @file sort_by_publication_year.cc
 * @brief Sort Books by Publication Year using Bucket Sort and Comparison Sort
 * 
 * This file implements two approaches to sort an array of Book objects by
 * their publication year:
 * 1. Comparison-based sort using std::sort - O(n log n)
 * 2. Bucket sort exploiting the bounded year range [1000, 2025] - O(n + K)
 * 
 * Key Concepts:
 * - Comparison Sort: General-purpose, works for any comparable key
 * - Bucket/Counting Sort: Exploits bounded integer range for linear time
 * - Operator Overloading: Custom ostream operator<< for Book printing
 * 
 * Why Bucket Sort is O(n) here:
 * - Year range K = 2025 - 1000 + 1 = 1026 (constant)
 * - Allocate K buckets, one per year
 * - Place each book in its year bucket: O(n)
 * - Concatenate buckets: O(n + K) = O(n) since K is constant
 * - Preserves insertion order within the same year (stable)
 * 
 * Time Complexities:
 * - sort_by_publication_sorting(): O(n log n) - comparison sort
 * - sort_by_publication():         O(n + K)   - bucket sort, K = year range
 * 
 * Space Complexity: O(n + K) for bucket sort, O(1) auxiliary for comparison sort
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
using namespace std;

/**
 * @struct Book
 * @brief Represents a book with title, author, page count, genre, and year
 */
struct Book {
  string title;
  string author;
  unsigned int page_count;
  string genre;
  unsigned int year;
};

/**
 * @brief Stream insertion operator for printing Book objects
 * @param os Output stream
 * @param b Book to print
 * @return Reference to the output stream (enables chaining)
 */
ostream& operator<<(ostream& os, const Book& b) {
  os<<b.title<<" "<<b.author<<" "<<b.page_count<<" "<<b.genre<<" "<<b.year<<"\n";
  return os;
}

/**
 * @brief Sorts books by year using comparison-based std::sort
 * @param books Vector of books to sort (modified in-place)
 * 
 * Uses a lambda comparator on the year field.
 * Simple but O(n log n) even though years are bounded integers.
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(1) auxiliary (in-place sort)
 */
void sort_by_publication_sorting(vector<Book>& books) {
  sort(books.begin(),books.end(),[](const Book& a, const Book& b){return a.year<b.year;});
  return;
}

/**
 * @brief Sorts books by year using bucket sort for O(n) performance
 * @param books Vector of books (read-only)
 * @return New vector of books sorted by publication year
 * 
 * Algorithm:
 * 1. Create K buckets (one per year in [1000, 2025])
 * 2. Place each book into buckets[book.year - MIN_YEAR]
 * 3. Concatenate all buckets from index 0 to K-1
 * 
 * This is stable: books within the same year retain their original order.
 * 
 * Time Complexity: O(n + K) where K = MAX_YEAR - MIN_YEAR + 1 = 1026
 * Space Complexity: O(n + K) for the bucket storage
 */
vector<Book> sort_by_publication(const vector<Book>& books) {
  const unsigned int MIN_YEAR = 1000;
  const unsigned int MAX_YEAR = 2025;
  vector<vector<Book>> buckets(MAX_YEAR - MIN_YEAR + 1);
  
  for (const auto& book : books) {
    buckets[book.year - MIN_YEAR].push_back(book);
  }
  
  vector<Book> result;
  for (const auto& bucket : buckets) {
    for (const auto& book : bucket) {
      result.push_back(book);
    }
  }
  return result;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  vector<Book> books {
    {"Shadow of Tomorrow", "Elliot Greyson", 350, "Science Fiction", 2020},
    {"Whispers in the Wind", "Lila Hart", 280, "Romance", 2018},
    {"Echoes of Eternity", "Mara Vance", 420, "Fantasy", 2018},
    {"Fragments of Dawn", "Cora Blake", 310, "Mystery", 2019},
    {"Beneath the Starlit Sky", "Aria Monroe", 270, "Drama", 2020}
  };

  vector<Book> res = sort_by_publication(books);
  for(auto& book: res) cout<<book<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Sort By Publication Year
 * 
 * You are given an array, `books`, of objects of a `Book` class, where each
 * book has fields `title`, `author`, `page_count`, `genre`, and `year_published`.
 * 
 * Return the books sorted by publication year. It doesn't matter how you
 * break ties.
 * 
 * Constraints:
 * - The length of `books` is at most 5 * 10^6
 * - All years are between 1000 and 2025 (inclusive)
 * 
 *============================================================================*/

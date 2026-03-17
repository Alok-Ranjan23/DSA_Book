#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
using namespace std;

struct Book {
  string title;
  string author;
  unsigned int page_count;
  string genre;
  unsigned int year;
};

ostream& operator<<(ostream& os, const Book& b) {
  os<<b.title<<" "<<b.author<<" "<<b.page_count<<" "<<b.genre<<" "<<b.year<<"\n";
  return os;
}

void sort_by_publication_sorting(vector<Book>& books) {
  sort(books.begin(),books.end(),[](const Book& a, const Book& b){return a.year<b.year;});
  return;
}

vector<Book> sort_by_publication(const vector<Book>& books) {
  const unsigned int MIN_YEAR = 1000;
  const unsigned int MAX_YEAR = 2025;
  vector<vector<Book>> buckets(MAX_YEAR - MIN_YEAR + 1);
  
  // Place books in buckets by year
  for (const auto& book : books) {
    buckets[book.year - MIN_YEAR].push_back(book);
  }
  
  // Collect sorted books
  vector<Book> result;
  for (const auto& bucket : buckets) {
    for (const auto& book : bucket) {
      result.push_back(book);
    }
  }
  return result;
}

// To execute C++, please define "int main()"
// book1 + book2
// operator+(book b2) {
//   this.title + b2.title;
// }      book3 =book.operator+(b2);---> book3 = book + b2
//
// operator<<(os, book) {
// return os --- chaining  
// }  cout<<book
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

// Your previous Plain Text content is preserved below:

// Hello! Your interview question is below. Write code in this pad just like you would normally – your AI Interviewer will be able to see it.

// # Sort By Publication Year

// You are given an array, `books`, of objects of a `Book` class, where each book has fields `title`, `author`, `page_count`, `genre`, and `year_published`.

// Return the books sorted by publication year. It doesn't matter how you break ties.

// Example 1:
// books = [
//   Book("Shadow of Tomorrow", "Elliot Greyson", 350, "Science Fiction", 2020),
//   Book("Whispers in the Wind", "Lila Hart", 280, "Romance", 2018),
//   Book("Echoes of Eternity", "Mara Vance", 420, "Fantasy", 2018),
//   Book("Fragments of Dawn", "Cora Blake", 310, "Mystery", 2019),
//   Book("Beneath the Starlit Sky", "Aria Monroe", 270, "Drama", 2020)
// ]
// Output: [
//   Book("Echoes of Eternity", "Mara Vance", 420, "Fantasy", 2018),
//   Book("Whispers in the Wind", "Lila Hart", 280, "Romance", 2018),
//   Book("Fragments of Dawn", "Cora Blake", 310, "Mystery", 2019),
//   Book("Beneath the Starlit Sky", "Aria Monroe", 270, "Drama", 2020),
//   Book("Shadow of Tomorrow", "Elliot Greyson", 350, "Science Fiction", 2020)
// ]

// Example 2:
// books = []
// Output: []. Empty list is valid input.

// Example 3:
// books = [Book("Solo", "Author", 100, "Genre", 2000)]
// Output: [Book("Solo", "Author", 100, "Genre", 2000)]. Single book is already sorted.

// Constraints:

// - The length of `books` is at most `5 * 10^6`
// - All years are between `1000` and `2025` (inclusive)

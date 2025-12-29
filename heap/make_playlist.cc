/**
 * @file make_playlist.cc
 * @brief Reorder Songs to Avoid Consecutive Same-Artist using Max-Heap
 * 
 * This file implements a function that reorders songs so that no two songs
 * by the same artist are played back-to-back. Uses a greedy max-heap approach.
 * 
 * Key Concepts:
 * - Task Scheduling Pattern: Similar to "reorganize string" or "task scheduler"
 * - Greedy Max-Heap: Always pick from artist with most songs remaining
 * - Interleaving: Alternate between artists to avoid consecutive same-artist
 * 
 * Algorithm:
 * 1. Group songs by artist into a hash map
 * 2. Build max-heap with (artist, songsList) ordered by list size
 * 3. Greedily pick from artist with most songs (ensures spread)
 * 4. If top artist == last used artist, pick second-top instead
 * 5. Re-push artist if they have more songs remaining
 * 6. Return empty if impossible (top == last and heap is empty)
 * 
 * Why Max-Heap by song count?
 * - Artists with more songs need more "spread" opportunities
 * - Processing them first ensures they can interleave with others
 * - If most-frequent artist has > (n+1)/2 songs, it's impossible
 * 
 * Time Complexity: O(n log m) where n = songs, m = unique artists
 *   - Each song is pushed/popped once: O(log m) per operation
 * 
 * Space Complexity: O(n + m) - hash map + heap storage
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

/*============================================================================
 * FUNCTION IMPLEMENTATION
 *============================================================================*/

/**
 * @brief Reorders songs so no two consecutive songs have the same artist
 * @param songs Vector of (title, artist) pairs
 * @return Reordered song titles, or empty vector if impossible
 * 
 * Heap Structure: {artist, songsList}
 * - Max-heap ordered by songsList.size() (most songs = highest priority)
 * - Custom comparator: a.size < b.size gives max-heap behavior
 * 
 * Greedy Strategy:
 * - Always pick from artist with most remaining songs
 * - Exception: if same as last artist, pick second-most instead
 * - This maximizes opportunities to interleave artists
 * 
 * Time Complexity: O(n log m)
 */
vector<string> make_playlist(vector<pair<string,string>>& songs) {
  vector<string> res;
  
  // Step 1: Group songs by artist
  // Key: artist name, Value: list of song titles
  unordered_map<string, vector<string>> umap;
  for(auto&song: songs) {
    umap[song.second].push_back(song.first);
  }
  
  // Step 2: Build max-heap ordered by number of songs per artist
  // HeapEntry = {artist_name, list_of_songs}
  using HeapEntry = pair<string, vector<string>>;
  auto cmp = [](const HeapEntry& a, const HeapEntry& b) {
    return a.second.size() < b.second.size();  // For max heap
  };
  priority_queue<HeapEntry, vector<HeapEntry>, decltype(cmp)> max_heap(cmp);

  for (const auto& [artist, songsList] : umap) {
    max_heap.push({artist, songsList});
  }
  
  // Track last artist to avoid consecutive same-artist
  string lastArtist;
  
  // Step 3-6: Greedy selection with interleaving
  while (!max_heap.empty()) {
    auto [artist, songList] = max_heap.top();
    max_heap.pop();
    
    // Case A: Different artist than last - safe to use
    if (artist != lastArtist) {
      res.push_back(songList.back());
      songList.pop_back();
      lastArtist = artist;
      
      // Re-push if artist has more songs
      if (!songList.empty()) {
        max_heap.push({artist, songList});
      }
    } 
    // Case B: Same artist as last - must use second choice
    else {
      // Impossible: only one artist left and it's the same as last
      if (max_heap.empty()) {
        return {};
      }
      
      // Use second-top artist instead
      auto [artist2, songList2] = max_heap.top();
      max_heap.pop();
      res.push_back(songList2.back());
      songList2.pop_back();
      lastArtist = artist2;
      
      // Re-push both artists if they have remaining songs
      if (!songList2.empty()) {
        max_heap.push({artist2, songList2});
      }
      max_heap.push({artist, songList});  // Put first artist back
    }
  }
  return res;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

// To execute C++, please define "int main()"
int main() {
  // Test: 4 songs by "A Dell", 3 by "The Bugs", 2 by "Michael JSON", 1 by "Johnny Cache"
  // Total: 10 songs, most frequent artist has 4 songs
  // Since 4 <= (10+1)/2 = 5, a valid arrangement exists
  vector<pair<string,string>> songs {
    {"Coding In The Deep", "A Dell"},
    {"Hello World", "A Dell"},
    {"Someone Like GNU", "A Dell"},
    {"Make You Read My Logs", "A Dell"},
    {"Hey Queue", "The Bugs"},
    {"Here Comes the Bug", "The Bugs"},
    {"Merge Together", "The Bugs"},
    {"Dirty Data", "Michael JSON"},
    {"Man in the Middle Attack", "Michael JSON"},
    {"Ring Of Firewalls", "Johnny Cache"}
  };
  
  // Expected: Interleaved playlist with no consecutive same-artist songs
  for(auto&x : make_playlist(songs)) cout<<x<<"\n";
  cout<<"\n";
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Make Playlist
 * 
 * Imagine your picky friends give you a list of song–artist tuples to create 
 * a playlist. Your task is to reorder the songs so that no two songs by the 
 * same artist are played back-to-back. If it's not possible, return an empty 
 * list.
 * 
 * Example:
 * songs = [["Coding In The Deep", "A Dell"],
 *          ["Hello World", "A Dell"],
 *          ["Someone Like GNU", "A Dell"],
 *          ["Make You Read My Logs", "A Dell"],
 *          ["Hey Queue", "The Bugs"],
 *          ["Here Comes the Bug", "The Bugs"],
 *          ["Merge Together", "The Bugs"],
 *          ["Dirty Data", "Michael JSON"],
 *          ["Man in the Middle Attack", "Michael JSON"],
 *          ["Ring Of Firewalls", "Johnny Cache"]]
 * 
 * Output: [
 *   "Coding In The Deep",         // A Dell
 *   "Hey Queue",                  // The Bugs
 *   "Hello World",                // A Dell
 *   "Dirty Data",                 // Michael JSON
 *   "Someone Like GNU",           // A Dell
 *   "Here Comes the Bug",         // The Bugs
 *   "Make You Read My Logs",      // A Dell
 *   "Man in the Middle Attack",   // Michael JSON
 *   "Merge Together",             // The Bugs
 *   "Ring Of Firewalls"           // Johnny Cache
 * ]
 * 
 * Constraints:
 * - The number of songs, `n`, is at most `10^5`.
 * - Each element in `songs` is a tuple with two strings.
 * - Song and artist names have at most `100` characters.
 * 
 *============================================================================*/

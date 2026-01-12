/**
 * @file viewer_counter_class.cc
 * @brief Track live stream viewers within a sliding time window
 * 
 * This file implements a ViewerCounter class that tracks viewers of different
 * types (subscriber, follower, guest) within a configurable time window.
 * 
 * Key Concepts:
 * - Queue per viewer type (FIFO for time-ordered events)
 * - Sliding window: remove expired timestamps on query
 * - Lazy cleanup: only remove old entries when queried
 * 
 * Time Complexity:
 * - join(): O(1) - just push to queue
 * - get_viewers(): Amortized O(1) - each element removed at most once
 * 
 * Space Complexity: O(n) where n is total number of join events
 */

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * @class ViewerCounter
 * @brief Tracks viewer counts within a sliding time window per viewer type
 * 
 * Viewers are categorized by type (e.g., "subscriber", "follower", "guest").
 * Each type maintains its own queue of timestamps for efficient counting.
 */
class ViewerCounter {
  int window_;                              // Window size in time units
  unordered_map<string,queue<int>> category; // Type -> queue of timestamps
  
  public:
    /**
     * @brief Constructor - creates a ViewerCounter with specified window
     * @param window The time window size (>= 1)
     */
    ViewerCounter(int window):window_(window) {}
    
    /**
     * @brief Registers a viewer joining at a specific time
     * @param timestamp The time when viewer joined
     * @param type The viewer type ("subscriber", "follower", "guest", etc.)
     */
    void join(int timestamp, const string& type);
    
    /**
     * @brief Gets count of viewers of a type within the time window
     * @param time The current time (end of window)
     * @param type The viewer type to count
     * @return Number of viewers in window [time - window, time]
     */
    int get_viewers(int time, const string& type);
};

/*============================================================================
 * IMPLEMENTATION SECTION
 *============================================================================*/

/**
 * join() - Record a new viewer
 * 
 * Simply push timestamp to the appropriate queue.
 * Cleanup of old timestamps is deferred to get_viewers (lazy approach).
 */
void ViewerCounter::join(int timestamp, const string& type) {
  category[type].push(timestamp);
}

/**
 * get_viewers() - Count viewers in time window
 * 
 * Algorithm:
 * 1. Get reference to queue for this viewer type
 * 2. Remove expired timestamps (< time - window) from front
 * 3. Count remaining timestamps that fall within window
 * 
 * Note: Step 2 modifies the queue (lazy cleanup), but this is safe
 * because expired entries will never be needed again.
 */
int ViewerCounter::get_viewers(int time, const string& type) {
  queue<int>& q = category[type];
  
  // Remove expired timestamps from front of queue
  while (!q.empty() && q.front() < (time - window_)) {
    q.pop();
  }

  // Count timestamps in window [time - window, time]
  int count = 0;
  queue<int> temp = q;    // Copy queue to iterate without modifying
  while(!temp.empty()) {
    int val = temp.front();
    if(val >= (time-window_) && val <= time) {
      count++;            // Timestamp falls within window
    }
    temp.pop();
  }
  return count;
}

/*============================================================================
 * MAIN FUNCTION - Test/Demo Section
 *============================================================================*/

int main() {
  // Create counter with window size 10
  ViewerCounter counter = ViewerCounter(10);
  
  // Simulate viewers joining at different times
  counter.join(1, "subscriber");   // t=1: 1 subscriber
  counter.join(1, "guest");        // t=1: 1 guest
  counter.join(2, "follower");     // t=2: 1 follower
  counter.join(2, "follower");     // t=2: 2 followers
  counter.join(2, "follower");     // t=2: 3 followers
  counter.join(3, "follower");     // t=3: 4 followers total
  
  // Query at time 10, window = [0, 10]
  cout<<counter.get_viewers(10, "subscriber")<<"\n";  // Expected: 1
  cout<<counter.get_viewers(10, "guest")<<"\n";       // Expected: 1
  cout<<counter.get_viewers(10, "follower")<<"\n";    // Expected: 4
  
  // Query at time 13, window = [3, 13]
  // Only follower at t=3 falls in window, others at t=2 are excluded
  cout<<counter.get_viewers(13, "follower")<<"\n";    // Expected: 1
  
  return 0;
}

/*============================================================================
 * PROBLEM STATEMENT (for reference)
 *============================================================================
 * 
 * # Viewer Counter Class
 * 
 * Streamers make money based on the number of views they receive while
 * streaming. Implement a ViewerCounter class that tracks the number of viewers
 * within a configurable time window for a live stream event. Viewer types may
 * be "guest", "follower", or "subscriber".
 * 
 * ViewerCounter API:
 * - __init__(window): establishes a window size ≥ 1.
 * - join(t, v): registers that a viewer of type v joined at time t.
 * - get_viewers(t, v): gets the viewer count of viewer type v within the time
 *                      window of length 'window' ending at timestamp t:
 *                      [t - window, t], with both endpoints included.
 * 
 * Example:
 *   counter = ViewerCounter(10)
 *   counter.join(1, "subscriber")
 *   counter.join(1, "guest")
 *   counter.join(2, "follower")
 *   counter.join(2, "follower")
 *   counter.join(2, "follower")
 *   counter.join(3, "follower")
 *   counter.get_viewers(10, "subscriber")  # Returns 1
 *   counter.get_viewers(10, "guest")       # Returns 1
 *   counter.get_viewers(10, "follower")    # Returns 4
 *   counter.get_viewers(13, "follower")    # Returns 1
 * 
 *============================================================================*/

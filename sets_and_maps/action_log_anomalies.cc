/**
 * @file action_log_anomalies.cc
 * @brief Find every support ticket whose open/close history is anomalous
 *
 * The log is chronological. A ticket is clean only if it is opened then closed
 * exactly once, by the same agent, with no action by that agent on any other
 * ticket in between. We sweep the log once, tracking which tickets are open,
 * which have ever been seen, and which ticket each agent is currently on, and
 * flag any ticket that breaks a rule.
 *
 * Key Concepts:
 * - opened: ticket -> agent for tickets currently open
 * - seen:   every ticket number ever opened (catches "opened twice")
 * - working: agent -> ticket they are mid-handling (catches "acted on another
 *   ticket in between")
 * - Invariant: working[agent] is set on a valid open and cleared on a valid
 *   close, so it never names a cleanly-closed ticket -- flagging it is always
 *   justified
 *
 * Time Complexity: O(N)
 *   - N = number of log entries. Each entry does a constant number of hash
 *     operations (O(1) average; agent-string hashing is O(L) for agent length
 *     L, treated as a small constant). The closing sweep over still-open
 *     tickets is O(N). Worst case O(N) per op only under adversarial hashing.
 *
 * Space Complexity: O(N)
 *   - The maps/sets hold at most one entry per ticket / agent, i.e. O(N).
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/// A single log line: the agent, the action ("open"/"close"), and the ticket.
struct Action {
  string agent;
  string action;
  int ticket_number;
  Action(string agent, string action, int ticket_number):agent{agent}, action {action}, ticket_number(ticket_number) {}
};

/**
 * @brief Return all ticket numbers that have an anomaly, in any order
 *
 * @param log Chronologically sorted list of actions
 * @return Ticket numbers that violate any clean-ticket rule
 *
 * Algorithm:
 * 1. If the acting agent is mid-handling a different ticket, flag that ticket
 *    (they did an action elsewhere before closing it).
 * 2. Skip entries for tickets already known to be anomalous.
 * 3. open: flag if the ticket was seen before; else record it as open.
 * 4. close: flag if the ticket isn't open or was opened by a different agent;
 *    else clear the open/working state.
 * 5. Any ticket still open at the end was never closed -> anomaly.
 */
//Time O(N)   (single pass; O(1) average hash ops per entry)
//Space O(N)  (one entry per ticket / agent across the maps and sets)
vector<int> action_log_anomalies(vector<Action>& log) {
  unordered_map<int,string> opened; // {ticket_number: agent}
  unordered_set <int> seen;
  unordered_map <string,int> working; // {agent: ticket}
  //anamoly
  unordered_set<int> anomalies;

  for (const auto& entry : log) {
    const string& agent = entry.agent;
    const string& action = entry.action;
    const int ticket = entry.ticket_number;

    // Check if agent is working on another ticket
    if (working.find(agent) != working.end() &&
        working[agent] != ticket) {
      anomalies.insert(working[agent]);
    }

    if (anomalies.find(ticket) != anomalies.end()) {
      continue;
    }

    if (action == "open") {
      if (seen.find(ticket) != seen.end()) {
        anomalies.insert(ticket);
        continue;
      }
      opened[ticket] = agent;
      working[agent] = ticket;
      seen.insert(ticket);
    } else {  // close
      if (opened.find(ticket) == opened.end() || opened[ticket] != agent) {
        anomalies.insert(ticket);
        continue;
      }
      working.erase(agent);
      opened.erase(ticket);
    }
  }
  for (const auto& [ticket, _] : opened) {
    anomalies.insert(ticket);
  }

  for (const auto& [ticket, agent] : opened) {
    anomalies.insert(ticket);
  }

  return vector<int>(anomalies.begin(), anomalies.end());
}

// To execute C++, please define "int main()"
int main() {
  vector<Action> log 
  {
    {"Dwight", "close", 2},
    {"Dwight", "open", 2},
    {"Drew", "open", 32},
    {"Drew", "close", 32},
    {"Drew", "open", 32},
    {"Drew", "close", 32},
    {"Susa", "open", 7},
    {"Jo", "close", 7},
    {"Susa", "open", 33},
    {"Jo", "open", 8},
    {"Jo", "open", 36},
    {"Jo", "close", 8},
    {"Susa", "close", 33}
  };
  for(auto& anomaly: action_log_anomalies(log)) cout<<anomaly<<" ";
  cout<<"\n";
  log = {{"Alice", "open", 1}, {"Alice", "close", 1}};
  for(auto& anomaly: action_log_anomalies(log)) cout<<anomaly<<" ";
  cout<<"\n";
  log = {{"Alice", "open", 1}, {"Alice", "open", 1}};
  for(auto& anomaly: action_log_anomalies(log)) cout<<anomaly<<" ";
  cout<<"\n";
  log = { 
    {"Drew", "open", 32}, 
    {"Drew", "close", 2}, 
    {"Drew", "close", 32}
  };
  for(auto& anomaly: action_log_anomalies(log)) cout<<anomaly<<" ";
  cout<<"\n";
  log = {
    {"Dwight", "close", 2},
    {"Dwight", "open", 2},
    {"Drew", "open", 32},
    {"Drew", "open", 2},
    {"Drew", "close", 32}};
  for(auto& anomaly: action_log_anomalies(log)) cout<<anomaly<<" ";
  cout<<"\n";
  return 0;
}

// # Action Log Anomalies

// You are given an action log, `log`, from a tech support system. Each entry is a tuple `[agent, action, ticket_number]`, where the ticket number is a positive integer, the agent is a string, and the action is `"open"` or `"close"`. The log is sorted chronologically.

// Your goal is to find all the tickets with _anomalies_, in any order. A ticket **doesn't** have anomalies if:

// - It is opened and closed once, in that order.
// - The opening and closing agent is the same.
// - The agent didn't do any action for a different ticket between opening and closing.

// Example 1: log = [
//     ["Dwight", "close", 2],
//     ["Dwight", "open", 2],
//     ["Drew", "open", 32],
//     ["Drew", "close", 32],
//     ["Drew", "open", 32],
//     ["Drew", "close", 32],
//     ["Susa", "open", 7],
//     ["Jo", "close", 7],
//     ["Susa", "open", 33],
//     ["Jo", "open", 8],
//     ["Jo", "open", 36],
//     ["Jo", "close", 8],
//     ["Susa", "close", 33]
// ]
// Output: [2, 32, 7, 8, 36]
// Explanation:
// - 2 was closed before it was opened.
// - 32 was opened multiple times.
// - 7 was opened and closed by different agents.
// - 8 was opened and closed, but the agent did something in between.
// - 36 was not closed.

// Example 2: log = [["Alice", "open", 1], ["Alice", "close", 1]]
// Output: []
// Explanation: The ticket was opened and closed once, in order, by the same agent.

// Example 3: log = [["Alice", "open", 1], ["Alice", "open", 1]]
// Output: [1]
// Explanation: The ticket was opened multiple times.

// Example 4: log = [
//     ["Drew", "open", 32],
//     ["Drew", "close", 2],
//     ["Drew", "close", 32]
// ]
// Output: [2, 32]
// Explanation:
// - 2 was closed without being opened
// - 32 was opened but Drew did another action (closing ticket 2) before closing it

// Example 5: log = [
//     ["Dwight", "close", 2],
//     ["Dwight", "open", 2],
//     ["Drew", "open", 32],
//     ["Drew", "open", 2],
//     ["Drew", "close", 32]
// ]
// Output: [2, 32]
// Explanation:
// - 2 was closed before being opened, and later opened by a different agent
// - 32 was opened but Drew did another action (opening ticket 2) before closing it


// Constraints:

// - `0 ≤ log.length ≤ 10^5`
// - Each `ticket_number` is a positive integer less than `10^6`
// - Each `agent` is a non-empty string
// - Each `action` is either `"open"` or `"close"`
// - The log is sorted chronologically

// Acknowledgements: Thanks to a reader for Examples 4 and 5.

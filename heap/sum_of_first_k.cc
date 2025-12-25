#include <functional>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int sum_first_k(vector<int>& primes,int k) {
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
  for(auto&x : primes) {
    pq.push({x,x});
  }
  int sum_primes=0;
  int counter=0;
  while(!pq.empty()) {
    auto p = pq.top();
    pq.pop();
    sum_primes += p.first;
    counter++;
    if(counter==k) return sum_primes;
    pq.push({p.first*p.second,p.second});
  }
  return sum_primes;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> primes {2}; int k=1;  
  cout<<sum_first_k(primes,k)<<"\n";
  primes = {5}; k=3;  
  cout<<sum_first_k(primes,k)<<"\n";
  primes = {2,3}; k=7;  
  cout<<sum_first_k(primes,k)<<"\n";
  return 0;
}

// # Sum Of First K Prime Powers

// Given a non-empty array, `primes`, of **distinct prime** numbers, and a positive number `k`, return the sum of the first `k` numbers that are a positive power of a number in `primes`.

// If the answer is larger than `10^9+7`, return it modulo `10^9+7`.

// Example 1: primes = [2], k = 1
// Output: 2
// The first positive power of 2 is 2^1 = 2.

// Example 2: primes = [5], k = 3
// Output: 155
// The first 3 positive powers of 5 are 5, 25, and 125.

// Example 3: primes = [2, 3], k = 7
// Output: 69
// The first 7 numbers that are a positive power of 2 or 3 are 2, 3, 4, 8, 9, 16, and 27.

// Constraints:

// - `1 <= primes.length <= 10^4`
// - Each element in `primes` is a distinct prime number
// - `0 <= k <= 10^6`

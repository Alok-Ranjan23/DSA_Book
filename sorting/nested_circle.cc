#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using circle = pair<pair<int,int>,int>;

bool contains(circle a, circle b) {
  auto centerA = a.first;
  auto radiusA = a.second;
  auto centerB = b.first;
  auto radiusB = b.second;
  double center_dist = sqrt((centerA.first-centerB.first) * (centerA.first-centerB.first) + (centerA.second-centerB.second) * (centerA.second-centerB.second));
  //cout<<center_dist<<" "<<radiusB<<" "<<radiusB<<"\n";

  return center_dist + radiusB <= radiusA;

}

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

// To execute C++, please define "int main()"
int main() {
  vector<circle> circles {
    {{4,4},5}, {{8,4},2}
  };
  std::cout << std::boolalpha;
  cout<<is_nested(circles)<<"\n";
  circles = {
    {{4,4},5}, {{5,3},3}, {{5,3},2}
  };
  std::cout << std::boolalpha;
  cout<<is_nested(circles)<<"\n";
  return 0;
}

// Your previous Plain Text content is preserved below:

// Hello! Your interview question is below. Write code in this pad just like you would normally – your AI Interviewer will be able to see it.

// # Nested Circles

// You are given a non-empty array of circles, `circles`, where each circle is specified by its center coordinates `(x, y)` and its radius `r`. Your task is to determine whether the circles are _nested_. For the circles to be considered nested, one of the following conditions must be met:

// 1. There is a single circle.
// 2. One circle completely surrounds all the others (without touching boundaries), and the other circles are themselves _nested_ (this is a recursive definition).

// Write a function that returns a boolean indicating whether the circles are nested.

// https://iio-beyond-ctci-images.s3.us-east-1.amazonaws.com/sorting-figure-5.png

// Example 1: circles = [
//     ((4, 4), 5),  # Circle with center (4, 4) and radius 5
//     ((8, 4), 2)   # Circle with center (8, 4) and radius 2
// ]
// Output: false. Neither circle is surrounded by the other.

// Example 2: circles = [
//     ((5, 3), 3),
//     ((5, 3), 2),
//     ((4, 4), 5)
// ]
// Output: true. The third circle contains all the first and second circles, and the first circle contains the second circle.

// Example 3: circles = [((5, 3), 3)]
// Output: true. A single circle is considered nested.

// Constraints:

// - The length of circles is at most 10^4
// - All coordinates and radii are integers between -10^4 and 10^4

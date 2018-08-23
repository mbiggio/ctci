#include <iostream>
#include <vector>
#include <cassert>
#include "helper.hpp"
using namespace std;


/*
 * Algorithm to rotate an NxN 2D matrix by 90 degrees clockwise.
 */

void rotate_matrix(vector<vector<int>> &matrix) {
  int kSize = matrix.size();
  for (int s=0; s<kSize/2; ++s) {
    for (int i=0; s+i<kSize-1-s; ++i) {
      int cur = matrix[s][s+i];
      swap(cur,matrix[s+i][kSize-1-s]);
      swap(cur,matrix[kSize-1-s][kSize-1-s-i]);
      swap(cur,matrix[kSize-1-s-i][s]);
      swap(cur,matrix[s][s+i]);
    }
  }
}

int main() {
  {
    vector<vector<int>> m = {{ 1, 2, 3, 4},
                             { 5, 6, 7, 8},
                             { 9,10,11,12},
                             {13,14,15,16}};
    print(m);
    rotate_matrix(m);
    print(m);
  }
  {
    vector<vector<int>> m = {{ 1, 2, 3},
                             { 4, 5, 6},
                             { 7, 8, 9}};
    print(m);
    rotate_matrix(m);
    print(m);
  }
  return 0;
}

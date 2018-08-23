#include <iostream>
#include <vector>
#include "helper.hpp"
using namespace std;

/*
 * In an MxN matrix of 0s and 1s,
 * nullify the rows and cols of the 0 elements
 */

bool first_row_has_zero(const vector<vector<int>> &m) {
  for (int j=0; j<m[0].size(); ++j) {
    if (m[0][j] == 0) return true;
  }
  return false;
}

bool first_col_has_zero(const vector<vector<int>> &m) {
  for (int i=0; i<m.size(); ++i) {
    if (m[i][0] == 0) return true;
  }
  return false;
}

void zero_out_col(int col, vector<vector<int>> &m) {
  for (int i=0; i<m.size(); ++i) {
    m[i][col] = 0;
  }
}

void zero_out_row(int row, vector<vector<int>> &m) {
  for (int j=0; j<m[0].size(); ++j) {
    m[row][j] = 0;
  }
}

void zero_out_matrix(bool zero_first_row, bool zero_first_col, vector<vector<int>> &m) {
  for (int i=1; i<m.size(); ++i) {
    if (m[i][0]==0) zero_out_row(i,m);
  }
  for (int j=1; j<m[0].size(); ++j) {
    if (m[0][j]==0) zero_out_col(j,m);
  }

  if (zero_first_row) zero_out_row(0,m);
  if (zero_first_col) zero_out_col(0,m);
}

void zero_matrix(vector<vector<int>> &m) {
  bool zero_first_col = first_col_has_zero(m);
  bool zero_first_row = first_row_has_zero(m);
  for (int i=1; i<m.size(); ++i) {
    for (int j=1; j<m[0].size(); ++j) {
      if (m[i][j] == 0) {
        m[i][0] = 0;
        m[0][j] = 0;
      }
    }
  }

  zero_out_matrix(zero_first_row, zero_first_col, m);
}

int main() {
  {
    vector<vector<int>> m = {{1,1,1},
                             {1,0,1},
                             {1,1,1},
                             {0,1,1}};

    print(m);
    zero_matrix(m);
    print(m);
  }
  return 0;
}

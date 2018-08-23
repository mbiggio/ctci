#ifndef __ARRAY_MATRIX__
#define __ARRAY_MATRIX__
#include <iostream>
#include <vector>

void print(const ::std::vector<::std::vector<int>> &m) {
  for (const auto &r : m) {
    for (const auto &c : r) {
      printf("%2d ", c);
    }
    ::std::cout << "\n";
  }
  ::std::cout << "\n";
}


#endif

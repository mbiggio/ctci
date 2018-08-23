#ifndef __HELPER__
#define __HELPER__
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

#include <iostream>
#include <bitset>
using namespace std;

/*
 * Checks if a string has unique characters 
 * by filling up a bitmap of occurrences for 
 * each character. As soon as we find a char 
 * with the bitmap set, we return false.
 * Otherwise, we return true.
 */

bool is_unique(const string &s) {
  static constexpr const int kAlphabetSize = 1<<8;
  if (s.size() > kAlphabetSize) return false;
  bitset<kAlphabetSize> b;
  for (char c : s) {
    if (b.test(c)) return false;
    b.set(c);
  }
  return true;
}

int main() {
  cout << is_unique("abcde") << endl;
  cout << is_unique("abcda") << endl;
  cout << is_unique("a") << endl;
  return 0;
}

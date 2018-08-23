#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/*
 * Compress a string by grouping together repeated characters.
 * If the resulting string after compression is bigger than the original,
 * return the original.
 */

string compress_string(const string &s) {
  stringstream result;
  for (int i=0; i<s.size(); ) {
    int count = 0;
    char cur = s[i];
    while(i<s.size() && s[i]==cur) {
      ++count;
      ++i;
    }
    result << cur << count;

  }
  return result.str().size()<s.size()?result.str():s;
}

int main() {
  cout << compress_string("aabcccccaaa") << endl;
  cout << compress_string("abca") << endl;
  return 0;
}

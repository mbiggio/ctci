#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/*
 * Algorithm to check if strings a and b are 
 * permutations of each other.
 * It builds a hash table of occurrences from
 * string a and matches them with the characters in string b.
 */

bool check_permutation(const string &a, const string &b) {
  if (a.size() != b.size()) return false;
  unordered_map<char,int> m;
  for (auto c : a) ++m[c];
  for (auto c : b) {
    auto it = m.find(c);
    if (it == m.end()) return false;
    if (--it->second == 0) m.erase(it);
  }
  return true;
}

int main() {
  cout << check_permutation("abca","aabc") << endl;
  cout << check_permutation("abca","adbc") << endl;
  return 0;
}

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

bool palindrome_permutation(const string &s) {
  unordered_set<char> m;
  for (char c : s) {
    if (c==' ') continue;
    auto it = m.find(tolower(c));
    if (it==m.end()) m.insert(tolower(c));
    else m.erase(it);
  }
  return m.size()<=1;
}

int main() {
  cout << palindrome_permutation("Tact Coa") << endl;
  cout << palindrome_permutation("TactCoa") << endl;
  cout << palindrome_permutation("TactCod") << endl;
  return 0;
}

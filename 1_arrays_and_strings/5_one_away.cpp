#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool check_replacement(const string &s1, const string &s2) {
  assert(s1.size() == s2.size());
  int diffs = 0;
  for (int i=0; i<s1.size(); ++i) {
    if (s1[i]!=s2[i] && ++diffs==2) return false;
  }
  return true;
}

bool check_insert(const string &s1, const string &s2) {
  assert(s2.size() == s1.size()+1);
  int diffs = 0;
  for (int i=0, j=0; i<s1.size(); ++i, ++j) {
    if (s1[i]!=s2[j]) {
      if (++diffs==2) return false;
      ++j;
    }
  }
  return true;
}


bool one_away(const string &s1, const string &s2) {
  int kSize1 = s1.size();
  int kSize2 = s2.size();
  if (kSize2 == kSize1) return check_replacement(s1,s2);
  else if (kSize2 == kSize1+1) return check_insert(s1,s2);
  else if (kSize2 == kSize1-1) return check_insert(s2,s1);
  else return false;
}


int main() {
  cout << one_away("pale", "ple") << endl;
  cout << one_away("pales", "pale") << endl;
  cout << one_away("pale", "bale") << endl;
  cout << one_away("pale", "bae") << endl;
  return 0;
}

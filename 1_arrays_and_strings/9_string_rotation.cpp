#include <iostream>
#include <string>
using namespace std;

/*
 * checks if a string s2 is a rotation of a string s1
 */
bool string_rotation(const string &s1, const string &s2) {
  if (s1.size() != s2.size()) return false;
  string s3 = s1+s1;
  auto idx = s3.find(s2);
  return idx!=string::npos;
}

int main() {
  cout << string_rotation("waterbottle", "erbottlewat") << endl;
  cout << string_rotation("waterbottle", "erbotrlewat") << endl;
  return 0;
}

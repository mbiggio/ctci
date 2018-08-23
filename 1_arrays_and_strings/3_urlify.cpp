#include <iostream>
#include <string>
#include <vector>
using namespace std;

void urlify(vector<char> &v, int size) {
  int read = size-1;
  int write = v.size()-1;
  while (read>=0) {
    if (v[read]!=' ') v[write--]=v[read];
    else {
      v[write--] = '0';
      v[write--] = '2';
      v[write--] = '%';
    }
    --read;
  }
}

int main() {
  {
    vector<char> v = {'M','r',' ','J','o','h','n',' ','S','m','i','t','h',' ',' ',' ',' '};
    urlify(v,13);
    cout << string(v.begin(),v.end()) << endl;
  }
  return 0;
}

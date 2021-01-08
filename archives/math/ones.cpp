#include <bits/stdc++.h>
using namespace std;

int ones(int n) {
  long count = 1;
  long num = 1;
  while (true) {
    if (num % n == 0) {
      return count;
    } else {
      count++;
      num = 10*num + 1;
      num %= n;
    }
  }
}

int main() {
  int i;
  while (cin >> i) {
    cout << ones(i) << endl;
  }
}

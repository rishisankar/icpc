#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;

void run() {
  int n; cin >> n;
  int x = -1;
  for (int i = 0; i < n; ++i) {
    int v; cin >> v;
    if (x == -1) x=v;
    else {
      if (v % x == 0) {
        cout << v << '\n'; x = -1;
      }
    }
  }
}
int main() {
  for (int i = 0; i  < 1; ++i) run();


}
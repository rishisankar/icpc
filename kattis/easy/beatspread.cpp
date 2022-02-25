#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;

void run() {
  int s,d; cin >> s >> d;
  if ((s+d)%2 != 0) {
    cout << "impossible\n"; return;
  }
  int a= (s+d)/ 2;
  int b = (s-a);
  if (a >= 0 && b >= 0) {
    cout << max(a,b) << ' ' << min(a,b) << '\n';
  } else {
    cout << "impossible\n";
  }
}
int main() {
  int n; cin >> n;
  for (int i = 0; i  < n; ++i) run();


}
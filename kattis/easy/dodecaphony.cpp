#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
void checkTrans(VI v1, VI v2) {
  // for (int i = 0; i < v2.size(); ++i) {
  //   cout << v1[i] << ' ';
  // } cout << '\n';
  // for (int i = 0; i < v2.size(); ++i) {
  //   cout << v2[i] << ' ';
  // } cout << '\n';
  for (int i = 1; i < v2.size(); ++i) {
    v2[i] = v2[i] - (v2[0] - v1[0]);
    v2[i] = (v2[i] + 36) % 12;
    // cout << "(" << v1[i] << "," << v2[i] << ")\n";
    if (v1[i] != v2[i]) return;
  }
  cout << "Transposition\n";
  exit(0);
}

void checkInv(VI v1, VI v2) {
  if (v1[0] != v2[0]) return;
  for (int i = 0; i < v2.size()-1; ++i) {
    int d1 = ((v1[i+1] - v1[i]) + 36) % 12;
    int d2 = ((v2[i] - v2[i+1]) + 36) % 12;
    if (d1 != d2) return;
  }
  cout << "Inversion\n";
  exit(0);
}

void checkRetro(VI v1, VI v2) {
  reverse(v2.begin(), v2.end());
  for (int i = 0; i < v2.size(); ++i) {
    if (v1[i] != v2[i]) return;
  }
  cout << "Retrograde\n";
  exit(0);
}

int main() {
  int n; cin >> n;
  unordered_map<string, int> m;
  m["C"] = 0;
  m["C#"] = 1;
  m["D"] = 2;
  m["D#"] = 3;
  m["E"] = 4;
  m["F"] = 5;
  m["F#"] = 6;
  m["G"] = 7;
  m["G#"] = 8;
  m["A"] = 9;
  m["A#"] = 10;
  m["B"] = 11;

  vector<int> v1(n);
  vector<int> v2(n);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s; v1[i] = m[s];
  }
  for (int i = 0; i < n; ++i) {
    string s; cin >> s; v2[i] = m[s];
  }
  checkTrans(v1,v2);
  checkInv(v1,v2);
  checkRetro(v1,v2);
  cout << "Nonsense\n";


}
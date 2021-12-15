#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> trees(n);
    for (int i = 0; i < n; ++i) {
        cin >> trees[i];
    }
    sort(trees.begin(), trees.end(), greater<int>());

    int m = INT_MIN;
    for (int i = 0; i < n; ++i) {
        trees[i] += i + 2;
        m = max(m, trees[i]);
    }
    cout << m << '\n';
}
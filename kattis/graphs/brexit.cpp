#include <bits/stdc++.h>
using namespace std;

int main() {
    int C,P,X,L;
    cin >> C >> P >> X >> L;

    queue<int> q;

    vector<vector<int>> neighbors(C+1);
    vector<int> total(C+1, 0);
    vector<int> remaining(C+1, 0);
    vector<bool> left(C+1, false);

    for (int i = 0; i < P; ++i) {
        int a,b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
        ++total[a]; ++remaining[a];
        ++total[b]; ++remaining[b];
    }

    remaining[L] = 0;
    q.push(L);
    while (!q.empty()) {
        int t = q.front();
        q.pop();

        if (left[t]) continue;

        if (remaining[t] <= total[t]/2) {
            left[t] = true;
            for (int n : neighbors[t]) {
                if (left[n]) continue;
                --remaining[n];
                q.push(n);
            }
        }

    }

    if (left[X]) cout << "leave\n"; else cout << "stay\n";
}
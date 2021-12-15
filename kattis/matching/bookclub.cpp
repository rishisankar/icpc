#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {

    int M;
    cin >> n >> M;
    k = n;

    g.resize(n);

    for (int i = 0; i < M; ++i) 
    {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;

        g[tmp1].push_back(tmp2);

    }

    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    int count = 0;

    for (int i = 0; i < k; ++i)
        if (mt[i] != -1)
            ++count;


    if (count == n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}

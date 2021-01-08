#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> dp(11, vector<vector<int>> (101, vector<int>(101, -1)));

// assume doesn't explode on numbers < first, does explode on numbers > last
int memo(int k, int first, int last) {
    
    if (first > last) {
        return 0;
    }
    if (dp[k][first][last] != -1) {
        return dp[k][first][last];
    }
    if (k == 1) {
        return dp[k][first][last] = ((first + last)*(last - first +1))/2;
    }

    int best = INT_MAX;
    for (int i = first; i <= last; ++i) {
        best = min(best, i + max(memo(k-1, first, i-1), memo(k, i + 1, last)));
    }
    return dp[k][first][last] = best;

}

int main() {

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int k, m;
        cin >> k >> m;
        cout << memo(k,1,m) << '\n';
    }

}
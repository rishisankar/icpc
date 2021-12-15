#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<vector<int>> dp(N+1, vector<int>(N+5,INT_MAX));

    vector<int> costs(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> costs[i];
    }

    dp[1][0] = 0;
    dp[2][1] = costs[2];
    queue<pair<int,int>> q;
    q.push({2,1});

    while (!q.empty()) {
        int square = q.front().first;
        int jumpsize = q.front().second;
        q.pop();

        if (square + jumpsize + 1 <= N) {
            int cur = dp[square+jumpsize+1][jumpsize+1];
            int newcost = dp[square][jumpsize] + costs[square+jumpsize+1];
            if (newcost < cur) {
                dp[square+jumpsize+1][jumpsize+1] = newcost;
                q.push({square+jumpsize+1, jumpsize+1});
            }
        }

        if (square - jumpsize >= 1) {
            int cur = dp[square-jumpsize][jumpsize];
            int newcost = dp[square][jumpsize] + costs[square-jumpsize];
            if (newcost < cur) {
                dp[square-jumpsize][jumpsize] = newcost;
                q.push({square-jumpsize, jumpsize});
            } 
        }
    }

    int output = INT_MAX;
    for (int i = 0; i < N+5; ++i) {
        output = min(output, dp[N][i]);
    }

    cout << output << '\n';
}
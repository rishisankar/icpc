#include <bits/stdc++.h>
using namespace std;

vector<int> values(2001);
vector<int> weights(2001);

int calc(int n, int c, vector<vector<int>>& memo) {
    if (n == 0) {
        return memo[n][c] = weights[n] <= c ? values[n] : 0;
    }

    if (memo[n][c] != -1) return memo[n][c];

    if (weights[n] > c) return memo[n][c] = calc(n-1,c,memo);

    return memo[n][c] = max(calc(n-1,c,memo), values[n] + calc(n-1,c-weights[n],memo));
}

int main() {

    int C, n;
    while (cin >> C) {
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> values[i] >> weights[i];
        }

        vector<vector<int>> memo(n+1, vector<int>(C+1, -1));

        calc(n-1, C, memo);

        vector<int> nums;
        int c = C;

        for (int i = n-1; i >= 1; --i) {

            if (memo[i][c] != memo[i-1][c]) {
                nums.push_back(i);
                c -= weights[i];
            }

        }
        if (memo[0][c]) nums.push_back(0);

        cout << nums.size() << '\n';
        for (int i = 0; i < nums.size(); ++i) {
            cout << nums[i] << ' ';
        }
        cout << '\n';

    }

}
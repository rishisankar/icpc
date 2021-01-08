#include <iostream>
#include <vector>
#include <string>
using namespace std;

int min(int i, int j) {
    return (i == 0 || i > j) ? j : i;
}

int max(int i, int j) {
    return i > j ? i : j;
}

int main() {
    int N, M, dists[40];
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> M;
        int dp[40][1001] = {0};
        for (int j = 0; j < M; ++j) {
            cin >> dists[j];
        }

        // base case
        dp[0][dists[0]] = dists[0];
        vector<int>* prevs_ptr;
        vector<int> prevs;
        prevs.push_back(dists[0]);
        prevs_ptr = &prevs;

        for (int j = 1; j < M; ++j) {
            int dist = dists[j];
            vector<int> tmp;
            for (int p : (*prevs_ptr)) {
                int maxH = p + dist;
                int minH = p - dist;
                if (minH >= 0) {
                    dp[j][minH] = min(dp[j][minH], dp[j-1][p]);
                    tmp.push_back(minH);
                }
                dp[j][maxH] = max(min(dp[j][maxH], dp[j-1][p]), maxH);
                tmp.push_back(maxH);
            }
            prevs_ptr = &tmp;
        }

        if (dp[M-1][0]) {
            int cur = 0;
            string s = "";
            for (int j = M-1; j >= 1; --j) {
                int dist = dists[j];
                if (cur < dist || dp[j-1][cur-dist] == 0 || dp[j-1][cur-dist] > dp[j][cur]) {
                    s = 'D' + s;
                } else {
                    s = 'U' + s;
                }
            }
            cout << 'U' << s << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
}
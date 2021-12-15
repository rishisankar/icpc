#include <iostream>
#include <string>

using namespace std;

int min(int i, int j) {
    return (i == 0 || i > j) ? j : i;
}

int max(int i, int j) {
    return i > j ? i : j;
}

int main() {
    int N;
    string stringsToPrint[101];
    cin >> N;
    int dists[40];
    for (int n = 0; n < N; ++n) {
        int M;
        cin >> M;
        int maxSum = 0;
        for (int i = 0; i < M; ++i) {
            cin >> dists[i];
            maxSum += dists[i];
        }

        int dp[40][1002] = {};

        dp[0][dists[0]] = dists[0];
        dp[0][maxSum + 1] = dists[0];

        for (int i = 1; i < M; ++i) {
            int curDist = dists[i];
            int maxDist;
            for (int j = 0; j <= dp[i-1][maxSum + 1]; ++j) {
                if (dp[i-1][j]) {
                    int minH = j - curDist;
                    int maxH = j + curDist;
                    if (minH >= 0) {
                        dp[i][minH] = min(dp[i][minH], dp[i-1][j]);
                    }
                    dp[i][maxH] = max(min(dp[i][maxH], dp[i-1][j]), maxH);
                    maxDist = maxH;
                } 
            }
            dp[i][maxSum + 1] = maxDist;
        }

        if (dp[M-1][0]) {
            string str = "D";
            int curLevel = dists[M - 1];
            for (int i = M - 2; i > 0; --i) {
                int minH = curLevel - dists[i];
                if (minH >= 0 && dp[i][curLevel] >= dp[i-1][minH] && dp[i-1][minH]) {
                    str = 'U' + str;
                    curLevel = minH;
                } else {
                    str = 'D' + str;
                    curLevel += dists[i];
                }
            }
            str = 'U' + str;

            stringsToPrint[n] = str;
        } else {
            stringsToPrint[n] = "IMPOSSIBLE";
        }
        //stringsToPrint[n] = "Optimal level for N=" + to_string(n) + ": " + to_string(dp[M-1][0]);
    }

    for (int i = 0; i < N; ++i) {
        cout << stringsToPrint[i] << endl;
    }
}
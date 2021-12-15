#include <bits/stdc++.h>
using namespace std;

// inclusive
int range(vector<vector<int>>& rangeSum, int a, int b, int c, int d) {
    if (a == 0 && b == 0) {
        return rangeSum[c][d];
    } else if (a == 0) {
        return rangeSum[c][d] - rangeSum[c][b-1];
    } else if (b == 0) {
        return rangeSum[c][d] - rangeSum[a-1][d];
    } else {
        return rangeSum[c][d] - rangeSum[c][b-1] - rangeSum[a-1][d] + rangeSum[a-1][b-1];
    }
}

int main() {

    int N, M;
    cin >> N >> M;

    vector<vector<bool>> hasCube(N, vector<bool>(N, false));
    for (int i = 0; i < M; ++i) {
        int x,y;
        cin >> x >> y;
        x -= 1; y -= 1; // shift to zero indexing

        hasCube[x][y] = true;
    }

    // sum of elts from (0,0) to (x,y)
    vector<vector<int>> rangeSum(N, vector<int>(N));

    // base cases
    rangeSum[0][0] = hasCube[0][0];
    for (int i = 1; i < N; ++i) {
        rangeSum[0][i] = rangeSum[0][i-1] + hasCube[0][i];
        rangeSum[i][0] = rangeSum[i-1][0] + hasCube[i][0];
    }

    // tabulate
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {                
            rangeSum[i][j] = hasCube[i][j] + rangeSum[i-1][j] + rangeSum[i][j-1] - rangeSum[i-1][j-1];
        }
    }

    int output = INT_MAX;
    // try all possible sub-rectangle
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = i; k < N; ++k) {
                for (int l = j; l < N; ++l) {
                    if ((k-i+1)*(l-j+1) != M) continue;
                    int count = range(rangeSum,i,j,k,l);
                    output = min(output, M - count);
                }
            }
        }
    }

    cout << output << '\n';

}
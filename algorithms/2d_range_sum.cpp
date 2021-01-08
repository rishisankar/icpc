// example: archives/dp/nered.cpp

// precomputation: O(N*M), query time: O(1)
// other options:
//  - segment tree: supports set of numbers changing, O(log n) query time, O(n log n) creation time
//  - sparse table: can't support numbers changing, O(log n) query time (but O(1) for RMQ instead of RSQ), O(n log n) creation

// both rangeSum and numbers should be N x M. rangeSum can then be used by range function. 
// Assumes N, M >= 1
int initRangeSum(vector<vector<int>>& rangeSum, vector<vector<int>>& numbers, int N, int M) {
    // base cases
    rangeSum[0][0] = hasCube[0][0];
    for (int i = 1; i < N; ++i) {
        rangeSum[i][0] = rangeSum[i-1][0] + hasCube[i][0];
    }
    for (int i = 1; i < M; ++i) {
        rangeSum[0][i] = rangeSum[0][i-1] + hasCube[0][i];
    }

    // tabulate
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < M; ++j) {                
            rangeSum[i][j] = hasCube[i][j] + rangeSum[i-1][j] + rangeSum[i][j-1] - rangeSum[i-1][j-1];
        }
    }
}

// inclusive O(1) calculation of sum of values between (a,b) and (c,d)
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

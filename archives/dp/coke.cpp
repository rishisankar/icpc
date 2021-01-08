#include <iostream>
using namespace std;

int memo[151][161][51];

int min(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return a > b ? b : a;
} 

int minCoins(int C, int n1, int n5, int n10);

int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; ++i) {

        int C, n1, n5, n10;
        cin >> C >> n1 >> n5 >> n10;

        for (int a = 0; a < 151; ++a) {
            for (int b = 0; b < 161; ++b) {
                for (int c = 0; c < 51; ++c) {
                    memo[a][b][c] = -1;
                }
            }
        }

        cout << minCoins(C, n1, n5, n10) << endl;
    }
}

int minCoins(int C, int n1, int n5, int n10) {
    if (n1 < 0 || n5 < 0 || n10 < 0) {
        return -1;
    }

    if (C <= 0) {
        return 0;
    }

    if (memo[C][n5][n10] != -1) {
        return memo[C][n5][n10];
    }

    // cases: 8 1s, 1 5 + 3 1s, 2 5s -> 2 1s, 1 10 -> 2 1s, 1 10 + 3 1s -> 1 5

    int minc = -1;
    if (n1 >= 8) minc = minCoins(C-1, n1-8, n5, n10) + 8;
    if (n1 >= 3 && n5 >= 1) {
        int tmp = minCoins(C-1, n1-3, n5-1, n10) + 4;
        minc = min(minc, tmp);
    }
    if (n5 >= 2) {
        int tmp = minCoins(C-1, n1+2, n5-2, n10) + 2;
        minc = min(minc, tmp);
    }
    if (n10 >= 1) {
        int tmp = minCoins(C-1, n1+2, n5, n10-1) + 1;
        minc = min(minc, tmp);
    }
    if (n10 >= 1 && n1 >= 3) {
        int tmp = minCoins(C-1, n1-3, n5+1, n10-1) + 4;
        minc = min(minc, tmp);
    }
    
    return memo[C][n5][n10] = minc;
}
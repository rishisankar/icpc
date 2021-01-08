#include <bits/stdc++.h>
using namespace std;

int main() {

    int H, W, N, M;
    cin >> H >> W >> N >> M;

    vector<vector<int>> arr(H,vector<int>(W,0));
    vector<int> kernel(N*M,0);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> arr[i][j];
        }
    }

    for (int i = M*N-1; i >= 0; --i) {
        cin >> kernel[i];
    }

    for (int i = 0; i < H-N+1; ++i) {
        for (int j = 0; j < W-M+1; ++j) {
            int var = 0;
            for (int k = 0; k < M*N; ++k) {
                var += kernel[k] * arr[i+k/M][j+k%M];
            }
            cout << var << " ";
        }
        cout << '\n';
    }

}
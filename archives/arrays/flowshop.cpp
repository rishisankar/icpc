#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, M;
    cin >> N >> M;

    vector<vector<int>> arr(N+1, vector<int>(M+1));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int tmp;
            cin >> tmp;

            if (i == 0 && j == 0) arr[0][0] = tmp;
            else if (i == 0) arr[0][j] = arr[0][j-1] + tmp;
            else if (j == 0) arr[i][0] = arr[i-1][0] + tmp;
            else {
                arr[i][j] = max(arr[i-1][j], arr[i][j-1]) + tmp;
            }


        }
    }

    cout << arr[0][M-1];
    for (int i = 1; i < N; ++i) {
        cout << ' ' << arr[i][M-1];
    }
    cout << endl;




}
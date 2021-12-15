#include <bits/stdc++.h>
using namespace std;

int main() {

    int R,S,K;
    cin >> R >> S >> K;

    vector<vector<bool>> arr(R, vector<bool>(S));

    for (int i = 0; i < R; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < S; ++j) {
            arr[i][j] = s.at(j) == '*';
        }
    }

    int maxcount = -1;
    int maxx, maxy;

    for (int i = 0; i <= R - K; ++i) {
        for (int j = 0; j <= S - K; ++j) {
            int count = 0;
            for (int k = i + 1; k < i + K - 1; ++k) {
                for (int l = j + 1; l < j + K - 1; ++l) {
                    if (arr[k][l]) ++count;
                }
            }
            if (count > maxcount) {
                maxcount = count;
                maxx = i;
                maxy = j;
            }
        }
    }

    cout << maxcount << '\n';
    for (int i = 0; i < R; ++i) {
        if (i == maxx || i == maxx + K - 1) {
            for (int j = 0; j < maxy; ++j) {
                if (arr[i][j]) {
                    cout << '*';
                } else {
                    cout << '.';
                }
            }
            cout << '+';
            for (int j = maxy+1; j < maxy+K-1; ++j) {
                cout << '-';
            }
            cout << '+';
            for (int j = maxy+K; j < S; ++j) {
                if (arr[i][j]) {
                    cout << '*';
                } else {
                    cout << '.';
                }
            }
        } else {
            for (int j = 0; j < S; ++j) {
                if ((j == maxy || j == maxy + K - 1) && (i > maxx && i < maxx+K-1)) {
                    cout << '|';
                } else if (arr[i][j]) {
                    cout << '*';
                } else {
                    cout << '.';
                }
            }
        }
        cout << '\n';
    }

}
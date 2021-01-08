#include <bits/stdc++.h>
using namespace std;

void brute(int r, int c, int k) {

    const int N = 160;

    bool arr[N][N][2] = {0};

    for (int i = 0; i < r; ++i) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < c; ++j) {
            char tmp2 = tmp.at(j);
            arr[i+60][j+60][0] = tmp2 == '#';
        }
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                arr[j][k][i%2] = false;
            }
        }
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (arr[j][k][(i+1) % 2]) {
                    for (int l = -1; l <= 1; ++l) {
                        for (int m = -1; m <= 1; ++m) {
                            arr[j+l][k+m][i%2] = true;
                        }
                    }
                }
            }
        }
    }

    long long count = 0;
    int type = k % 2;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            count += arr[i][j][type];
        }
    }

    cout << count << '\n';

}

int main() {

    int r, c, k;
    cin >> r >> c >> k;

    if (k <= 50) {
        brute(r,c,k);
        return 0;
    }

    vector<vector<bool>> vec(r, vector<bool>(c));

    vector<vector<int>> rowRange(r, vector<int>(2, -1));
    for (int i = 0; i < r; ++i) {
        rowRange[i][0] = INT_MAX;
    }

    int firstRow = -1;
    int lastRow = -1;
    int firstCol = INT_MAX;
    int lastCol = -1;

    for (int i = 0; i < r; ++i) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < c; ++j) {
            char tmp2 = tmp.at(j);
            vec[i][j] = tmp2 == '#';
            if (vec[i][j]) {
                if (firstRow == -1) firstRow = i;
                lastRow = i;
                firstCol = min(firstCol, j);
                lastCol = max(lastCol, j);
                if (rowRange[i][0] == INT_MAX) rowRange[i][0] = j;
                rowRange[i][1] = j;
            }
        }
    }

    if (firstRow == -1) {
        cout << "0\n";
        return 0;
    }

    int lefty, righty;

    for (int i = 0; i < r; ++i) {
        if (vec[i][firstCol]) {
            lefty = i;
        }
        if (vec[i][lastCol]) {
            righty = i;
        }
    }

    long long area = 0;

    int leftptr = rowRange[firstRow][0];
    for (int i = firstRow; i < lefty; ++i) {
        if (rowRange[i][0] < leftptr) {
            leftptr = rowRange[i][0];
        }
        area += leftptr - firstCol;
    }
    leftptr = rowRange[lastRow][0];
    for (int i = lastRow; i > lefty; --i) {
        if (rowRange[i][0] < leftptr) {
            leftptr = rowRange[i][0];
        }
        area += leftptr - firstCol;
    }

    int rightptr = rowRange[firstRow][1];
    for (int i = firstRow; i < righty; ++i) {
        if (rowRange[i][1] > rightptr) {
            rightptr = rowRange[i][1];
        }
        area += lastCol - rightptr;
    }
    rightptr = rowRange[lastRow][1];
    for (int i = lastRow; i > righty; --i) {
        if (rowRange[i][1] > rightptr) {
            rightptr = rowRange[i][1];
        }
        area += lastCol - rightptr;
    }

    long long width = 1 + lastCol - firstCol + (2*k);
    long long height = 1 + lastRow - firstRow + (2*k);
    long long totalArea = width * height;

    //printf("firstRow: %d, lastRow: %d, firstCol: %d, lastCol: %d, lefty: %d, righty: %d, area: %d\n", firstRow, lastRow, firstCol, lastCol, lefty, righty, area);

    cout << (totalArea - area) << '\n';

}
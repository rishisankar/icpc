#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

struct st
{
    int x;
    int y;
    int i;
};


int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m;
        cin >>n >> m;

        bool arr[501][501] = {0};

        int count = 0;
        queue<st> q;

        for (int j = 0; j < n; ++j) {
            string line;
            cin >> line;
            for (int k = 0; k < m; ++k) {
                arr[j][k] = line.at(k) == '*';
                if (arr[j][k]) {
                    count++;
                    st s;
                    s.x = j;
                    s.y = k;
                    s.i = 2;
                    q.push(s);
                }
            }
        }

        //cout << q.size() << " ";

        while (!q.empty()) {
            st s = q.front();
            q.pop();

            bool success = true;

            for (int j = s.y - s.i + 1; j <= s.y + s.i - 1; ++j) {
                int xIndex = s.x + s.i - 1;
                if (xIndex >= 0 && xIndex < n && j >= 0 && j < m) {
                    if (!arr[xIndex][j]) {
                        success = false;
                        break;
                    }
                } else {
                    success = false;
                    break;
                }
            }

            if (success) {
                count++;
                s.i++;
                q.push(s);
            }

        }

        cout << count << '\n';

    }
}   
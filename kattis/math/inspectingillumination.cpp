#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;

    vector<vector<int>> res(n+1, vector<int>(5, -1));

    vector<int> nums { 2, 3, 5, 7, 11 };

    for (int i = 0; i < 5; ++i) {

        int k = nums[i];
        for (int j = 0; j < k; ++j) {

            int count = 0;

            for (int l = 1; l <= n; ++l) {
                if (l % k == j) {
                    ++count;
                }
            }
            if (count == 0) continue;
            cout << "ASK " << count;
            for (int l = 1; l <= n; ++l) {
                if (l % k == j) {
                    cout << ' ' << l;
                }
            }
            cout << '\n';
            cout.flush();

            int ans;
            for (int l = 0; l < count; ++l) {
                cin >> ans;
                res[ans][i] = j;
            }

        }

    }

    cout << "ANSWER";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            bool works = true;
            for (int k = 0; k < 5; ++k) {
                if (j % nums[k] != res[i][k]) {
                    works = false;
                    break;
                }
            }
            if (works) {
                cout << " " << j;
                break;
            }
        }
    }
    cout << '\n';

}
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; ++i) {
        int S; cin >> S;
        vector<int> red;
        vector<int> blue;
        for (int j = 0; j < S; ++j) {
            string L; cin >> L;
            char c = L[L.size() - 1];
            L = L.substr(0, L.size() - 1);
            int tmp = stoi(L);
            if (c == 'R') {
                red.push_back(tmp);
            } else {
                blue.push_back(tmp);
            }
        }
        sort(red.begin(), red.end());
        sort(blue.begin(), blue.end());
        int m = min(red.size(), blue.size());
        int count = 0;
        for (int j = 0; j < m; ++j) {
            count += red[red.size()-1-j]-1;
            count += blue[blue.size()-1-j]-1;
        }
        cout << "Case #" << i+1 << ": " << count << '\n';
    }

}
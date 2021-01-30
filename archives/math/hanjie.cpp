#include <bits/stdc++.h>
using namespace std;

int r,c;

vector<vector<bool>> all(vector<int>& clue, int n) {

    vector<vector<bool>> possible;

    if (n == 0) {
        vector<bool> tmp(c, false);
        possible.push_back(tmp);
    } else if (n == 1) {
        for (int i = 0; i <= c-clue[0]; ++i) {
            vector<bool> tmp(c, false);
            for (int a = i; a < i+clue[0]; ++a) tmp[a] = true;
            possible.push_back(tmp);
        }
    } else if (n == 2) {
        for (int i = 0; i <= c-clue[0]; ++i) {
            for (int j = i+clue[0]+1; j <= c-clue[1]; ++j) {
                vector<bool> tmp(c, false);
                for (int a = i; a < i+clue[0]; ++a) tmp[a] = true;
                for (int a = j; a < j+clue[1]; ++a) tmp[a] = true;
                possible.push_back(tmp);
            }
        }
    } else {
        for (int i = 0; i <= c-clue[0]; ++i) {
            for (int j = i+clue[0]+1; j <= c-clue[1]; ++j) {
                for (int k = j+clue[1]+1; k <= c-clue[2]; ++k) {
                    vector<bool> tmp(c, false);
                    for (int a = i; a < i+clue[0]; ++a) tmp[a] = true;
                    for (int a = j; a < j+clue[1]; ++a) tmp[a] = true;
                    for (int a = k; a < k+clue[2]; ++a) tmp[a] = true;
                    possible.push_back(tmp);
                }
            }
        }
    }

    return possible;

}

int main() {

    cin >> r >> c;
    
    vector<vector<int>> horizontal(6);
    for (int i = 0; i < r; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int tmp; cin >> tmp;
            horizontal[i].push_back(tmp);
        }
    }
    r = 6;
    
    vector<vector<int>> vertical(c);
    for (int i = 0; i < c; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int tmp; cin >> tmp;
            vertical[i].push_back(tmp);
        }
    }

    int count = 0;
    for (vector<bool> r1 : all(horizontal[0], horizontal[0].size())) {
        for (vector<bool> r2 : all(horizontal[1], horizontal[1].size())) {
            for (vector<bool> r3 : all(horizontal[2], horizontal[2].size())) {
                for (vector<bool> r4 : all(horizontal[3], horizontal[3].size())) {
                    for (vector<bool> r5 : all(horizontal[4], horizontal[4].size())) {
                        for (vector<bool> r6 : all(horizontal[5], horizontal[5].size())) {
                            vector<vector<bool>> grid { r1, r2, r3, r4, r5, r6 };
                            bool ok = true;
                            for (int i = 0; i < c; ++i) {
                                vector<int> curv;
                                int curc = 0;
                                for (int j = 0; j < r; ++j) {
                                    if ((!grid[j][i]) && curc != 0) {
                                        curv.push_back(curc);
                                        curc = 0;
                                    } else if (grid[j][i]) {
                                        ++curc;
                                    }
                                }
                                if (curc != 0) curv.push_back(curc);

                                if (curv.size() != vertical[i].size()) { ok = false; break; }
                                for (int j = 0; j < curv.size(); ++j) {
                                    if (curv[j] != vertical[i][j]) { ok = false; break;}
                                }
                                if (!ok) break;
                            }
                            if (ok) ++count;
                        }
                    }
                }
            }
        }
    }

    cout << count << '\n';

}
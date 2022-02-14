#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {

    int tests; cin >> tests;
    for (int t = 0; t < tests; ++t) {

        int n; cin >> n;
        unordered_map<string, vector<int>> l1, l2;
        for (int i = 0; i < n; ++i) {
            string trash; cin >> trash;
            for (int j = 0; j < 2; ++j) {
                int x; cin >> x;
                for (int ing = 0; ing < x; ++ ing ){
                    string s; cin >> s; 
                    if (j == 0) l1[s].push_back(i);
                    else l2[s].push_back(i);
                }
            }
        }

        vector<pair<string,string>> ans;

        for (auto it : l1) {
            for (auto it2 : l2) {
                if (it.second.size() != it2.second.size()) continue;
                bool failed = false;
                for (int i = 0; i < it.second.size(); ++i) {
                    if (it.second[i] != it2.second[i]) {
                        failed = true;
                        break;
                    }
                }
                if (!failed) {
                    ans.push_back({it.first, it2.first});
                }
            }
        }
        sort(ans.begin(), ans.end());
        for (pair<string,string> p : ans) {
            cout << '(' << p.first << ", " << p.second << ")\n";
        }
        if (t != tests-1)
        cout << '\n';

    }
    

}
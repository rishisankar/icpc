#include <bits/stdc++.h>
using namespace std;

struct s {
    long long val;
    long long thres;
    string prefix;
    s() {}

    s(string c) {
        prefix = c;
        string tmp(c);
        for (int i = c.size(); i < 10; ++i) {
            tmp += '0';
        }
        val = stoll(tmp);
        thres = val + powl(10, 10 - c.size());
    }
};

bool compare(s s1, s s2)
{
    return (s1.val < s2.val);
}

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        int n; cin >> n;
        vector<s> tmp(n);
        for (int j = 0; j < n; ++j) {
            string asdf;
            cin >> asdf;
            tmp[j] = s(asdf);
        }
        sort(tmp.begin(), tmp.end(), compare);

        bool suc = true;
        for (int j = 0; j < tmp.size() - 1; ++j) {
            if (tmp[j].thres > tmp[j+1].val) {
                suc = false;
                break;
            }
        }
        if (suc) cout << "YES\n";
        else cout << "NO\n";
    }

}
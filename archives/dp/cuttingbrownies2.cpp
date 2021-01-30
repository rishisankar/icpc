#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    for (int tests = 0; tests < t; ++tests) {
        int m,n;
        cin >> m >> n;
        string person; cin >> person;
        if (person == "Harry") {
            int tmp = m;
            m = n;
            n = tmp;
        }
        bool loses = false;

        if (n == m) loses = true;
        else if (abs(n-m) == 1 && min(n,m)%2 == 0) loses = true;
        else if (m > n && person == "Harry") loses = true;
        else if (m < n && person == "Vicky") loses = true;

        cout << person;
        if (loses) {
            cout << " cannot win\n";
        } else {
            cout << " can win\n";
        }

    }

}
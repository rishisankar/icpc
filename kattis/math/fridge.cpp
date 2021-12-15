#include <bits/stdc++.h>
using namespace std;

int main() {

    string s;

    getline(cin, s);

    // # of digits
    vector<int> counts(10, 0);

    for (int i = 0; i < s.size(); ++i) {
        int tmp = s.at(i) - '0';
        ++counts[tmp];
    }
    
    int mindigit = 1;
    for (int i = 2; i <= 10; ++i) {
        if (counts[mindigit] > counts[i % 10]) {
            mindigit = i % 10;
        }
    }

    if (mindigit == 0) {
        cout << '1';
    }

    for (int i = 0; i <= counts[mindigit]; ++i) {
        cout << mindigit;
    }

    cout << '\n';

}
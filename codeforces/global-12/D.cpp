#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        cin >>n;

        vector<int> vec(n);
        for (int j = 0; j < n; ++j) {
            cin >> vec[j];
        }

        stack<int> s1;
        stack<int> s2;

        int lb = 0, rb = n-1;
        for (int j = 1; j <= n; ++j) {
            if (vec[lb] == j) {
                ++lb;
                s1.push(j);
            } else if (vec[rb] == j) {
                --rb;
                s2.push(j);
            } else {
                
            }
        }
    }
}   
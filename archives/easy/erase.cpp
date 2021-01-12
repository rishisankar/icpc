#include <bits/stdc++.h>
using namespace std;

void success() {
    cout << "Deletion succeeded\n";
    exit(0);
}

void fail() {
    cout << "Deletion failed\n";
    exit(0);
}

int main() {
    int n;
    string s1;
    string s2;
    cin >> n >> s1 >> s2;

    if (s1.size() != s2.size()) fail();

    for (int i = 0; i < s1.size(); ++i) {
        if ((s1.at(i) == s2.at(i) && n%2 == 1) || (s1.at(i) != s2.at(i) && n%2 == 0)) fail();
    }
    
    success();
}
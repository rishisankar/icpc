#include <bits/stdc++.h>
using namespace std;

int main() {

    int a1,b1,a2,b2;
    int c1,d1,c2,d2;
    cin >> a1 >> b1 >> a2 >> b2 >> c1 >> d1 >> c2 >> d2;

    int s1 = a1+b1+a2+b2;
    int s2 = c1+d1+c2+d2;

    if (s1 == s2) {
        cout << "Tie\n";
    } else if (s1 > s2) {
        cout << "Gunnar\n";
    } else {
        cout << "Emma\n";
    }

}
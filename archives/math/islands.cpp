#include <bits/stdc++.h>
using namespace std;

int main() {

    int p; cin >> p;

    while(p--) {

        int test; cin >> test;
        vector<int> seq(12);
        for (int j = 0; j < 12; ++j) {
            cin >> seq[j];
        }

        int count = 0;
        for (int i = 1; i <= 10; ++i) {
            for (int j = 1; j < 12 - i; ++j) {
                int m = *min_element(seq.begin()+j, seq.begin()+j+i);
                if (m > seq[j-1] && m > seq[j+i]) ++count;
            }
        }

        cout << test << ' ' << count << '\n';

    }

}
#include <bits/stdc++.h>
using namespace std;

int main() {

    int N, t;
    cin >> N >> t;

    vector<int> v(N);

    for (int i = 0; i < N; ++i){
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    if (t == 1) {
        unordered_set<int> s;
        for (int i = 0; i < N; ++i) {
            s.insert(v[i]);
            if (s.find(7777-v[i]) != s.end()) {
                cout << "Yes" << endl;
                return 0;
            }

        }
        cout << "No" << endl;
    } else if (t == 2) {
        int prev = v[0];
        for (int i = 1; i < N; ++i) {
            if (v[i] == prev) {
                cout << "Contains duplicate" << endl;
                return 0;
            }
            prev = v[i];
        }
        cout << "Unique" << endl;
    } else if (t == 3) {
        int count = 1;
        int prev = v[0];
        if (count > N/2) {
            cout << prev << endl;
            return 0;
        }
        for (int i = 1; i < N; ++i) {
            if (v[i] == prev) {
                count++;
                if (count > N/2) {
                    cout << prev << endl;
                    return 0;
                } 
            } else {
                count = 1;
                prev = 1;
            }
        }
        cout << -1 << endl;
    } else if (t == 4) {
        if (N % 2 == 0) {
            cout << v[N/2-1] << " " << v[N/2] << endl;
        } else {
            cout << v[N/2] << endl;
        }
    } else {
        bool first = true;
        for (int i = 0; i < N; ++i) {
            if (v[i] >= 100 && v[i] <= 999) {
                if (first) {
                    first = false;
                } else {
                    cout << " ";
                }
                cout << v[i];
            }
        }
        cout << endl;
    }

}
#include <bits/stdc++.h>
using namespace std;

struct s {
    long long val;
    int key;
    s() {}
    s(long long v, int k) {
        val = v;
        key = k;
    }
};

bool compare (s s1, s s2) {
    return s1.val > s2.val;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<s> a(N);
    vector<s> d(N);
    vector<s> h(N);
    for (int i = 0; i < N; ++i) {
        long long A,D,H;
        cin >> A >> D >> H;
        a[i] = s(A, i);
        d[i] = s(D, i);
        h[i] = s(H, i);
    }

    sort(a.begin(), a.end(), compare);
    sort(d.begin(), d.end(), compare);
    sort(h.begin(), h.end(), compare);
    
    vector<bool> counter(N, false);
    int count = 0;
    for (int i = 0; i < K; ++i) {
        int k = a[i].key;
        if (!counter[k]) {
            counter[k] = true;
            count++;
        }
    }
    for (int i = 0; i < K; ++i) {
        int k = d[i].key;
        if (!counter[k]) {
            counter[k] = true;
            count++;
        }
    }
    for (int i = 0; i < K; ++i) {
        int k = h[i].key;
        if (!counter[k]) {
            counter[k] = true;
            count++;
        }
    }
    cout << count << '\n';
}
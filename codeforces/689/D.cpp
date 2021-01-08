#include <bits/stdc++.h>
using namespace std;

// COMPILER: GNU C++17	

struct st
{
    int l;
    int r;
};

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, Q;
        cin >> n >> Q;

        vector<long long> vec(n);
        unordered_set<long long> ans_set;
        for (int j = 0; j < n; ++j) {
            cin >> vec[j];
        }

        sort(vec.begin(), vec.end());

        vector<long long> sums(n);
        sums[0] = vec[0];
        for (int j = 1; j < n; ++j) {
            sums[j] = vec[j] + sums[j-1];
        }

        queue<st> q;
        st start;
        start.l = 0;
        start.r = n - 1;
        q.push(start);

        while (!q.empty()) {
            st top = q.front();
            q.pop();

            int l = top.l;
            int r = top.r;

            long long sum = l == 0 ? sums[r] : sums[r] - sums[l-1];
            ans_set.insert(sum);

            if (l == r) {
                continue;
            } else {
                long long mid = (vec[l] + vec[r])/2;
                if (vec[r] <= mid) {
                    continue;
                }
                int tl = l;
                int tr = r;
                int tmid;
                while (tl < tr) {
                    tmid = (tl + tr)/2;
                    if (vec[tmid] <= mid && vec[tmid+1] > mid) {
                        break;
                    } else if (vec[tmid] <= mid) {
                        tl = tmid + 1;
                    } else {
                        tr = tmid;
                    }
                }
                st beginning;
                st ending;
                beginning.l = l;
                beginning.r = tmid;
                ending.l = tmid + 1;
                ending.r = r;
                q.push(beginning);
                q.push(ending);
            }

        }

        for (int j = 0; j < Q; ++j) {
            long long cur;
            cin >> cur;
            if (ans_set.find(cur) != ans_set.end()) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }

    }
}   
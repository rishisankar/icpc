// may be doable w/o binary search?

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct su {
    ll sum;
    int type; // 1 = bb, 2 = bn, 3 = be, 4 = nn, 5 = ne, 6 = ee
};

bool compare(su s1, su s2) {
    return s1.sum < s2.sum;
}

ll b,n,e,sb,sn,se,m;
vector<ll> kayaks;
vector<su> sums(6);

ll bl, nl, el;

bool can(int type) {
    if (type == 1) {
        return bl >= 2;
    } else if (type == 2) {
        return bl >= 1 && nl >= 1;
    } else if (type == 3) {
        return bl >= 1 && el >= 1;
    } else if (type == 4) {
        return nl >= 2;
    } else if (type == 5) {
        return nl >= 1 && el >= 1;
    } else {
        return el >= 2;
    }
}

void sub(int type) {
    if (type == 1) {
        bl -= 2;
    } else if (type == 2) {
        bl--; nl--;
    } else if (type == 3) {
        bl--; el--;
    } else if (type == 4) {
        nl -= 2;
    } else if (type == 5) {
        nl--; el--;
    } else {
        el -= 2;
    }
}

bool works(ll speed) {
    bl = b;
    nl = n;
    el = e;
    for (ll c : kayaks) {
        bool found = false;
        for (su s : sums) {
            if (can(s.type) && s.sum * c >= speed) {
                sub(s.type);
                found = true;
                break;
            }
        } 
        if (!found) return false;
    }
    return true;
}

int main() {

    cin >> b >> n >> e;
    cin >> sb >> sn >> se;
    m = (b+n+e)/2;
    kayaks.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> kayaks[i];
    }
    sort(kayaks.begin(), kayaks.end(), greater<int>());

    sums[0].sum = sb+sb;
    sums[0].type = 1;
    sums[1].sum = sb+sn;
    sums[1].type = 2;
    sums[2].sum = sb+se;
    sums[2].type = 3;
    sums[3].sum = sn+sn;
    sums[3].type = 4;
    sums[4].sum = sn+se;
    sums[4].type = 5;
    sums[5].sum = se+se;
    sums[5].type = 6;
    sort(sums.begin(), sums.end(), compare);

    ll best = 0;
    ll lo = 0;
    ll hi = 10000000000LL;

    while (lo <= hi) {
        ll mid = (lo+hi)/2;

        if (works(mid)) {
            best = mid;
            lo = mid+1;
        } else {
            hi = mid-1;
        }
    }

    cout << best << '\n';

}
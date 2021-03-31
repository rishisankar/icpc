// doesn't work!

#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if ((a - b) % g == 0) {
	    x = (b - a) % n * x % n / g * m + a;
	    return x < 0 ? x + m*n/g : x;
    } else {
        return -1;
    }
}

void permutations(VI& permSize, VVI& result, int i) {
    if (i == 0) {
        REP(j, permSize[0]) {
            VI tmp;
            tmp.PB(j);
            result.PB(tmp);
        }
    } else {
        int n = result.size();
        REP(k,n) {
            for (int j = 0; j < permSize[i]; ++j) {
                if (j == permSize[i]-1) {
                    result[k].PB(j);
                } else {
                    VI asdf = result[k];
                    asdf.PB(j);
                    result.PB(asdf);
                }
            }
        }
    }
    if (i < permSize.size() - 1) {
        permutations(permSize, result, i+1);
    }
}

struct S{
    ll p;
    vector<pair<ll, ll>> vals;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    map<ll, map<ll, ll>> data;
    int n; cin >> n;
    REP(i, n) {
        ll x,d;
        cin >> x >> d;
        //x %= d;
        if (data.find(d) == data.end()) {
            map<ll, ll> tmp;
            data[d] = tmp;
        }
        if (data[d].find(x) == data[d].end()) {
            data[d][x] = 1;
        } else {
            data[d][x] += 1;
        }
    }

    VI permSize(data.size());
    auto it = data.begin();
    int i = 0;
    while (it != data.end()) {
        permSize[i] = it->second.size();
        ++it;
        ++i;
    }

    VVI perms;
    permutations(permSize, perms, 0);

    vector<S> data2;
    for(auto it = data.begin(); it != data.end(); ++it) {
        S stmp;
        stmp.p = it->first;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            stmp.vals.PB({it2->first, it2->second});
        }
        data2.PB(stmp);
    }

    // cout << "DATAAA\n";
    // for (S s : data2) {
    //     cout << s.p;
    //     for (pair<ll,ll> pll : s.vals) {
    //         cout << " (" << pll.first << "," << pll.second << ")";
    //     }
    //     cout << "\n";
    // }
    // cout << "DATAAA\n";

    ll best = 0;
    ll x = LLONG_MAX;

    for (VI perm : perms) {
        ll ct = 0;
        REP(j, perm.size()) {
            ct += data2[j].vals[perm[j]].second;
        }
        if (ct >= best) {
            
            ll a = data2[0].vals[perm[0]].first;
            ll m = data2[0].p;
            for (int k = 1; k < data2.size(); ++k) {
                ll b = data2[k].vals[perm[k]].first;
                ll n = data2[k].p;
                a = crt(a,m,b,n);
                m *= n;
            }
            ll cx = a;
            for (int k = 0; k < data2.size(); ++k) {
                ll tx = data2[k].vals[perm[k]].first;
                while (cx < tx) {
                    cx += m;
                }
            }

            //printV(perm);
            //cout << ":) " <<  ct << " " << cx << '\n';

            if (ct > best || cx < x) {
                best = ct;
                x = cx;
            }
        }
    }

    cout << x << ' ' << best << '\n';

}
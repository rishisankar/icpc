
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

void solve() {
    int m,n; cin >> m >> n;
    vector<bitset<26>> tran(26);
    rep(i,0,26) tran[i][i] = 1;
    rep(i,0,m) {
        char a,b; cin >> a >> b;
        tran[a-'a'][b-'a'] = 1;
    }
    rep(i,0,30) {
        rep(j,0,26) {
            rep(k,0,26) {
                if (tran[j][k]) {
                    tran[j] |= tran[k];
                }
            }
        }
    }
    rep(i,0,n) {
        string a,b; cin >> a >> b;
        if (sz(a) != sz(b)) {
            cout << "no\n";
            continue;
        }
        bool ok = true;
        rep(j,0,sz(a)) {
            if (!tran[a[j]-'a'][b[j]-'a']) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "no\n";
            continue;
        }
        cout << "yes\n";
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}

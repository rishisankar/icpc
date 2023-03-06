#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

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
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, start = -1, end = -1, nmatches = 0;
        map<int,int> next;
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
            if (!N[n].next.count(c-first)) N[n].next[c-first] = -1;
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1) {
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back();
        rep(i,0,26) {
            N.back().next[i]=0;
        }

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
                int y = N[prev].next.count(i) ? N[prev].next[i] : -1;
                if (!N[n].next.count(i)) N[n].next[i] = y;
                else {
				    int &ed = N[n].next[i];
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word) {
			n = N[n].next.count(c-first) ? N[n].next[c-first] : -1;
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i,0,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};

pair<int,string> removeVowels(string s) {
    string ans = "";
    int ct = 0;
    rep(i,0,s.size()) {
        if (s[i] != 'A' && s[i] != 'E' && s[i] != 'I' && s[i] != 'O' && s[i] != 'U') {
            ans += s[i];
        } else {
            ct++;
        }
    }
    return {ct,ans};
}

void run() {
    int n; cin >> n;
    map<string, pair<string,int>> word_map; // no vowels -> {orig, # vowels}
    rep(i,0,n) {
        string s; cin >> s;
        pair<int,string> p = removeVowels(s);
        if (word_map.count(p.S)) {
            if (word_map[p.S].S < p.F) word_map[p.S] = {s,p.F};
        } else {
            word_map[p.S] = {s,p.F};
        }
    }
    
    vector<string> patterns(word_map.size());
    vector<int> patSize(word_map.size());
    vector<string> orig(word_map.size());
    vector<int> numVowels(word_map.size());
    int ct = 0;
    for (auto p : word_map) {
        patterns[ct]=p.F;
        patSize[ct] = p.F.size();
        orig[ct] = p.S.F;
        numVowels[ct] = p.S.S;
        ++ct;
    }
    map<string, pair<string,int>>().swap(word_map); // clear memory from original word map

    string s; cin >> s;
    int m = s.size();

    AhoCorasick ac(patterns);
    vector<vi> vv = ac.findAll(patterns, s);
    vector<string>().swap(patterns); // deallocate patterns
    VVI matches(m, vector<int>(0));
    rep(i,0,vv.size()) {
        for (int j : vv[i]) {
            // there is a match of pattern j at location i in s
            matches[i+patSize[j]-1].pb(j);
        }
    }

    vector<pair<ll,int>> dp(m, {-1,-1});
    rep(i,0,m) {
        ll bst = -1;
        int bstP = -1;
        for (int j : matches[i]) {
            int nv = numVowels[j];
            int k = i - patSize[j];
            if (k < 0) {
                if (nv > bst) {
                    bst = nv;
                    bstP = j;
                }
            } else if (dp[k].F != -1) {
                if (nv + dp[k].F > bst) {
                    bst = nv+dp[k].F;
                    bstP = j;
                }
            }
        }
        dp[i] = {bst,bstP};
    }

    vector<int> soln;
    int cur = m-1;
    while (cur >= 0) {
        soln.pb(dp[cur].S);
        cur -= patSize[dp[cur].S];
    }
    reverse(all(soln));
    for (int i : soln) {
        cout << orig[i] << ' ';
        cout.flush();
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}
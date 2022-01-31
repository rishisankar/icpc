#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
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
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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

int n;
unordered_map<string, ll> tones;
unordered_map<ll, bool> tonesR;

pair<ll,ll> spl(string& s) {
    string note, oct;
    if (s[1] == '#') {
        note = s.substr(0,2);
        oct = s.substr(2, s.size()-2);
    } else {
        note = s.substr(0,1);
        oct = s.substr(1, s.size()-1);
    }
    return {tones[note], stoll(oct)};
}

ll gval2(pair<ll,ll>& pl) {
    return 12*pl.S + pl.F;
}

ll gval(string& s) {
    pair<ll,ll> pl = spl(s);
    return gval2(pl);
}

// return note after translating
ll move(ll tr, pair<ll,ll>& pr) {
    ll x = (((pr.F + tr) % 12) + 12) % 12;
    return x;
}

pair<ll,ll> getNote(ll val) {
    return {val%12,val/12};
}


void run() {
    cin >> n;
    tones["C"] = 0;
    tones["C#"] = 1;
    tones["D"] = 2;
    tones["D#"] = 3;
    tones["E"] = 4;
    tones["F"] = 5;
    tones["F#"] = 6;
    tones["G"] = 7;
    tones["G#"] = 8;
    tones["A"] = 9;
    tones["A#"] = 10;
    tones["B"] = 11;
    for (auto pr : tones) {
        tonesR[pr.S] =  (pr.F.size() > 1);
    }

    string loS, hiS; cin >> loS >> hiS;
    ll lo = gval(loS);
    ll hi = gval(hiS);
    pair<ll,ll> mnn, mxn;
    ll mnv = LLONG_MAX, mxv = LLONG_MIN;
    vector<pair<ll,ll>> notes(n);
    REP(i, n) {
        string notesi; cin >> notesi;
        notes[i] = spl(notesi);
        ll x = gval2(notes[i]);
        if (x < mnv) {
            mnn = notes[i];
            mnv = x;
        }
        if (x > mxv) {
            mxn = notes[i];
            mxv = x;
        }
    }
    ll minAcc = LLONG_MAX;
    vector<ll> start(12, 0);
    for (int i = 0; i < 12; ++i) {
        ll transp = i-mnn.F;
        transp += 24;
        REP(j, notes.size()) {
            ll x = move(transp, notes[j]);
            if (tonesR[x]) {
                ++start[i];
            }
        }
    }
    for (ll x : start) {
        minAcc = min(minAcc, x);
    }
    unordered_set<ll> ok;
    REP(i,12) {
        if (start[i] == minAcc) ok.insert(i);
    }

    ll mxVal = mnv + gval(hiS) - mxv;
    pair<ll,ll> mxValN = getNote(mxVal);
    pair<ll,ll> mnValN = spl(loS);

    ll ct = 0;

    // simulate while starting note not matching mxValN. then scale.

    pair<ll,ll> ugh1 = {mxValN.F, mnValN.S};
    pair<ll,ll> ugh2 = {mxValN.F, mnValN.S+1};
    ll v1 = gval2(ugh1);
    ll v2 = gval2(ugh2);
    ll str = gval2(mnValN);
    ll end = (v1 >= str) ? v1 : v2;

    // dbg(gval2(mnValN), gval2(mxValN));
    // dbg("vv",v1,v2);
    // dbg("asdf",str,end);
    assert(str+ 25 >= end);
    vector<ll> vals;
    for (int i = str; i <= end; ++i) {
        ll transp = (getNote(i).F - mnn.F) + 24;
        ll cttt = 0;
        REP(j, notes.size()) {
            ll x = move(transp, notes[j]);
            if (tonesR[x]) {
                ++cttt;
            }
        }
        vals.PB(cttt);
    }

    ll minsim = LLONG_MAX;
    for (ll x : vals) minsim=min(minsim,x);

    ll oct1 = getNote(end).S;
    ll oct2 = mxValN.S;
    if (oct1 != oct2) {
        ll resf = 0;
        for (ll x : vals) {
            if (x == minAcc) ++resf;
        }
        resf += (oct2-oct1) * ok.size();
        print(minAcc,resf);
    } else {
        ll resf = 0;
        for (ll x : vals) {
            if (x == minsim) ++resf;
        } 
        print(minsim,resf);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}
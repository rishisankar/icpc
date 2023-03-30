#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p)
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T)
{ cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(_VA_ARGS_)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

ll fastpow(ll b, ll e, ll m) {
    ll ans = 1;
    while(e) {
        if(e&1) {
            ans *= b, ans %= m;
        }
        b *= b, b %= m;
        e >>= 1;
    }
    return ans;
}

struct mint {
    ll n;
    ll mod;
    mint(ll c_n = 0, ll c_mod = 1e9+7) : n(c_n), mod(c_mod) {}
    mint operator+(mint m) { return {(n + m.n) % mod, mod}; }
    mint operator+=(mint m) { return (*this) = (*this)+m; }
    mint operator-(mint m) { return {(n - m.n + mod) % mod, mod}; }
    mint operator-=(mint m) { return (*this) = (*this)-m; }
    mint operator*(mint m) { return {(n * m.n) % mod, mod}; }
    mint operator*=(mint m) { return (*this) = (*this)*m; }
    mint operator/(mint m) { return {n*fastpow(m.n, mod-2, mod)%mod, mod}; }
    mint operator/=(mint m) { return (*this) = (*this)/m; }
};

ostream& operator<<(ostream &os, const mint &m)
{ return os << m.n; }


struct H
{
    mint f;
    mint s;
    int size;
    H() : f(0, 1e9+9), s(0, 1e9+7), size(0) {}
    H(mint cf, mint cs, int cz) : f(cf), s(cs), size(cz) {}
};

ostream& operator<<(ostream &os, const H &h)
{ return os << '(' << h.f << ", " << h.s << ')'; }

bool operator<(H const& h1, H const& h2) {
    if(h1.f.n != h2.f.n) return h1.f.n < h2.f.n;
    return h1.s.n < h2.s.n;
}

bool operator==(H const& h1, H const& h2) {
    return h1.f.n == h2.f.n && h1.s.n && h2.s.n;
}

H compute(string const& s) {
    const int p1 = 31;
    const int p2 = 37;
    const int m1 = 1e9 + 9;
    const int m2 = 1e9 + 7;
    mint h1{0, m1};
    mint h2{0, m2};
    mint p_pow1{1, m1};
    mint p_pow2{1, m2};
    for (char c : s) {
        h1 += p_pow1 * (tolower(c) - 'a' + 1);
        h2 += p_pow2 * (tolower(c) - 'a' + 1);
        p_pow1 *= p1;
        p_pow2 *= p2;
    }
    return H(h1, h2, s.size());
}

vector<mint> p_pow1(101), p_pow2(101), inv_pow1(101), inv_pow2(101);
void precompute() {
    const int p1 = 31;
    const int p2 = 37;
    const int m1 = 1e9 + 9;
    const int m2 = 1e9 + 7;
    p_pow1[0] = {1, m1};
    p_pow2[0] = {1, m2};
    inv_pow1[0] = {1, m1};
    inv_pow2[0] = {1, m2};
    rep(i, 1, 101) {
        p_pow1[i] = p_pow1[i-1]*p1;
        p_pow2[i] = p_pow2[i-1]*p2;
        inv_pow1[i] = inv_pow1[0]/p_pow1[i];
        inv_pow2[i] = inv_pow2[0]/p_pow2[i];
    }
}

H combine(H h1, H h2) {
    const int p1 = 31;
    const int p2 = 37;
    mint p_pow = p_pow1[h1.size];
    mint hash1 = h1.f + p_pow*3 + p_pow*p1*h2.f;
    p_pow = p_pow2[h1.size];
    mint hash2 = h1.s + p_pow*3 + p_pow*p2*h2.s;
    return H(hash1, hash2, h1.size+h2.size+1);
}

H strip(H h1, H h12) {
    mint p_pow = p_pow1[h1.size];
    mint hash1 = h12.f-h1.f-p_pow*3;
    hash1 *= inv_pow1[h1.size+1];
    p_pow = p_pow2[h1.size];
    mint hash2 = h12.s-h1.s-p_pow*3;
    hash2 *= inv_pow2[h1.size+1];
    return H(hash1, hash2, h12.size-h1.size-1);
}

void solve(int n) {
    unordered_set<string> delim = {".", ",", ":", ";", "?", "!"};
    string s;
    set<H> words;
    set<H> subs[n];
    cin >> s;
    while(s != "*") {
        vector<string> sentence;
        while(!delim.count(s)) {
            sentence.pb(s);
            cin >> s;
        }
        vector<H> hs;
        H rolling[n];
        rep(i, 0, sz(sentence)) {
            H h = compute(sentence[i]);
            words.insert(h);
            hs.pb(h);
            rep(j, 0, n) {
                if(i < j+1) {
                    rolling[j] = combine(rolling[j], h);
                }
                else {
                    rolling[j] = combine(strip(hs[i-j-1], rolling[j]), h);
                }
                if(i >= j) {
                    subs[j].insert(rolling[j]);
                }
            }
        }
        cin >> s;
    }
    cin >> s;
    while(s != "#") {
        vector<string> sentence;
        bool recognize = true;
        while(!delim.count(s)) {
            sentence.pb(s);
            cin >> s;
        }
        vector<H> hs;
        H rolling[n];
        rep(i, 0, sz(sentence)) {
            H h = compute(sentence[i]);
            if(!words.count(h)) {
                cout << "What does the word \"" << sentence[i] << "\" mean?\n";
            }
            hs.pb(h);
            if(!recognize) continue;
            rep(j, 0, n) {
                if(i < j+1) {
                    rolling[j] = combine(rolling[j], h);
                }
                else {
                    rolling[j] = combine(strip(hs[i-j-1], rolling[j]), h);
                }
                if(i >= j) {
                    if(!subs[j].count(rolling[j])) {
                        recognize = false;
                        subs[j].insert(rolling[j]);
                    }
                }
            }
        }
        for(H h: hs) {
            words.insert(h);
        }
        string sstr;
        if(!recognize) {
            cout << "What does the sentence \"";
            rep(i, 0, sz(sentence)) {
                cout << sentence[i];
                if(i != sz(sentence)-1) cout << ' ';
            }
            cout << "\" mean?\n"; 
        }
        cin >> s;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    precompute();
    int n;
    while(cin >> n) {
        solve(n);
    }
}
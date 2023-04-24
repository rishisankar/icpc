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
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

inline
list<string>::iterator back3(list<string>::iterator it, list<string> &cards) {
    rep(i, 0, 3) {
        if(it == cards.begin()) return cards.end();
        --it;
    }
    return it;
}

void cascade(list<string> &cards) {
    if(cards.size() < 4) return;
    auto it = cards.end();
    --it;
    auto b = back3(it, cards);
    auto iit(it);
    --iit;
    auto bb = back3(iit, cards);
    auto iiit(iit);
    --iiit;
    auto bbb = back3(iiit, cards);
    if(b != cards.end() && b->at(0) == it->at(0)) {
        cards.erase(b, cards.end());
        cascade(cards);
        return;
    }
    if(bb != cards.end() && bb->at(0) == iit->at(0)) {
        cards.erase(bb, it);
        cascade(cards);
        return;
    }
    if(bbb != cards.end() && bbb->at(0) == iiit->at(0)) {
        cards.erase(bbb, iit);
        cascade(cards);
        return;
    }
    if(b != cards.end() && b->at(1) == it->at(1)) {
        cards.erase(it);
        cards.erase(b);
        cascade(cards);
        return;
    }
    if(bb != cards.end() && bb->at(1) == iit->at(1)) {
        cards.erase(iit);
        cards.erase(bb);
        cascade(cards);
        return;
    }
    if(bbb != cards.end() && bbb->at(1) == iiit->at(1)) {
        cards.erase(iiit);
        cards.erase(bbb);
        cascade(cards);
        return;
    }
}


void solve() {
    list<string> cards;
    rep(i, 0, 52) {
        string s;
        cin >> s;
        cards.pb(s);
        cascade(cards);
    }
    cout << cards.size();
    trav(a, cards) {
        cout << ' ' << a;
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}

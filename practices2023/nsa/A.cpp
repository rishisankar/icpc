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
	int k,x;
	cin>>k>>x;
	vi v2(k-x);
	vi v1(x);
	rep(i,0,x) v1[i]=i;
	rep(i,0,k-x) v2[i]=x+i;

	vector<string> res;
	do{
		do{
			string t;
			rep(i,0,x) t+='0'+v1[i];
			rep(i,0,k-x) t+='0'+v2[i];

			// reverse(all(t));
						res.pb(t);
	}while(next_permutation(all(v2)));

	}while(next_permutation(all(v1)));

	trav(a,res)
	cout<<a<<"\n";

}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
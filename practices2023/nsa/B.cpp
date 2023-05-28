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
string chars="0123456789abcdef";
string s;


int n; // number of bytes, so len/2

bool ok(int x)
{
	return ((x>='A' && x<='Z') || (x>='a' && x<='z') || (x>='0' && x<='9'));
}

void dfs(int idx, int l, string &t, set<string> &ans)
{
	if(idx==2*l) // check string
	{
		// vector<int> key;
		// rep(i,0,l)
		// {
		// 	int bt=stoi(t.substr(2*i,2),0,16);
		// 	key.pb(bt);
		// }
		// bool good=true;
		// rep(i,0,n)
		// {
		// 	// input byte
		// 	int bt=stoi(s.substr(2*i,2),0,16);
		// 	int ot=bt^key[i%l];
		// 	if(!ok(ot))
		// 	{
		// 		good=false;
		// 		break;
		// 	}
		// }
		// if(good)
		ans.insert(t);
		return;
	}

	trav(a,chars) trav(b,chars)
	{
		// do some pruningS
		string kk;kk.pb(a);kk.pb(b);
		int kkk=stoi(kk,0,16);
		bool good=true;

		int cur=idx;
		while(cur+1<2*n)
		{
			int bt=stoi(s.substr(cur,2),0,16);
			int ot=bt^kkk;
			if(!ok(ot))
			{
				good=false;
				break;
			}
			cur+=2*l;
		}
		if(!good) continue;
		t.pb(a);
		t.pb(b);
		dfs(idx+2,l,t,ans);
		t.pop_back();
		t.pop_back();
	}
	
}

void solve() {
	cin>>s;

	n=sz(s)/2;
	int l=0;
	while(true)
	{
		l++;
		// if(n%l!=0) continue;
		set<string> ans;
		string t;
		dfs(0,l,t,ans);
		if(sz(ans)!=0)
		{
			trav(a,ans)
			cout<<"0x"<<a<<"\n";
			return;
		}
	}

}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
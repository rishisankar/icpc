#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n; cin >> n;
    unordered_map<string,int> m;
    int count = 0;
    VVI adj(2*n+1);
    VI deg(2*n+1, 0);
    REP(i, n) {
        string s1, s2;
        cin >> s1 >> s2;
        int i1,i2;
        if (m.find(s1) != m.end()) {
            i1 = m.find(s1)->second;
        } else {
            m.insert({s1, count});
            i1 = count;
            ++count;
        }
        if (m.find(s2) != m.end()) {
            i2 = m.find(s2)->second;
        } else {
            m.insert({s2, count});
            i2 = count;
            ++count;
        }
        adj[i2].push_back(i1);
        ++deg[i1];
    }
    n = count;
    adj.resize(n);
    deg.resize(n);

    VB safe(n, true);

    VVI zero(2);
    int mod = 0;

    REP(i, n) if (deg[i] == 0) zero[0].push_back(i);

    while (!zero[mod].empty()) {
        int next = (mod+1)%2;
        zero[next].clear();
        for (int i : zero[mod]) {
            safe[i] = false;
            for (int j : adj[i]) {
                --deg[j];
                if (deg[j] == 0) {
                    zero[next].push_back(j);
                }
            }
        }
        mod = next;
    }

    string city;
    while (cin >> city) {
        int a = m.find(city)->second;

        if (!safe[a]) {
            cout << city << " trapped\n";
        } else {
            cout << city << " safe\n";
        }
    }

}
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair

typedef long long ll;
typedef pair<int,int> pii;

vector<pii> dirs{mp(0,-1),mp(1,0),mp(0,1),mp(-1,0)};
typedef tuple<int,int,int,int> T;

const int MN = 51;
vector<pii> dist(MN*MN*MN*MN+5, {INT_MAX,INT_MAX});
vector<bool> vis(MN*MN*MN*MN+5, 0);

inline int geti(T& t) {
    return get<0>(t) + MN*get<1>(t) + MN*MN*get<2>(t) + MN*MN*MN*get<3>(t);
}
void run() {
    map<char,int> mpd; mpd['S'] = 0; mpd['E'] = 1; mpd['N'] = 2; mpd['W'] = 3;
    int c, r, e; cin >> c >> r >> e; --e;
    int c1, r1, c2, r2;
    char d1c,d2c;
    cin >> c1 >> r1 >> d1c >> c2 >> r2 >> d2c;
    int d1 = mpd[d1c], d2 = mpd[d2c];
    int dd = (d2-d1+8)%4;
    --c1; --r1; --c2; --r2;
    vector<vector<vector<bool>>> adj(c, vector<vector<bool>>(r, vector<bool>(4, 1)));
    int n; cin >> n;
    rep(i,0,n) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a][b][2] = 0;
        adj[a][b+1][0] = 0;
    }
    cin >> n;
    rep(i,0,n) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a][b][1] = 0;
        adj[a+1][b][3] = 0;
    }
    vector<T> que;
    vector<T> qnxt;
    que.pb({c1,r1,c2,r2});
    dist[geti(que.front())] = {0,0};
    vis[geti(que.front())] = 1;
    while (!que.empty()) {
        T t = que.back();
        que.pop_back();
        int tid = geti(t);
        if (get<0>(t) == MN-1 && get<2>(t) == MN-1) {
            cout << dist[tid].F << ' ' << dist[tid].S << '\n';
            return;
        }
        rep(rot,0,4) {
            int nd1 = (rot)%4;
            int nd2 = (rot+dd)%4;
            int nx1 = get<0>(t), ny1 = get<1>(t), nx2 = get<2>(t), ny2 = get<3>(t);
            int nbp = 0;
            if (nx1 != MN-1) {
                if (nx1 == e && ny1 == 0 && nd1 == 0) {
                    nx1 = MN-1, ny1 = MN-1;
                } else if (adj[nx1][ny1][nd1]) {
                    int nx1p = nx1 + dirs[nd1].F, ny1p = ny1 + dirs[nd1].S;
                    if (nx1p >= 0 && ny1p >= 0 && nx1p < c && ny1p < r) {
                        nx1 = nx1p, ny1 = ny1p;
                    } else nbp++;
                } else {
                    nbp++;
                }
            }
            if (nx2 != MN-1) {
                if (nx2 == e && ny2 == 0 && nd2 == 0) {
                        nx2 = MN-1, ny2 = MN-1;
                } else if ( adj[nx2][ny2][nd2]) {
                    int nx2p = nx2 + dirs[nd2].F, ny2p = ny2 + dirs[nd2].S;
                    if (nx2p >= 0 && ny2p >= 0 && nx2p < c && ny2p < r) {
                        nx2 = nx2p, ny2 = ny2p;
                    } else nbp++;
                } else nbp++;
            }
            if (nx1 == nx2 && ny1 == ny2 && nx1 != MN-1) {
                continue;
            }
            T tnew = {nx1,ny1,nx2,ny2};
            int tidnew = geti(tnew);
            if (!vis[tidnew]) {
                vis[tidnew] = 1;
                qnxt.pb(tnew);
            }
            dist[tidnew] = min(dist[tidnew], {dist[tid].F+1, dist[tid].S+nbp});
        }
        if (que.empty()) swap(que,qnxt);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    run();
}
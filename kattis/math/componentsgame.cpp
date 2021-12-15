// can be done WAY cleaner using DSU

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

int N,M;

bool outOfBounds(int i, int j) {
    if (i < 0 || j < 0) return true;
    if (i >= N || j >= M) return true;
    return false;
}

void computeComponents(VVB& grid, VI& nums) {
    int cur = 0;
    VVI comps(N, VI(2, -1));
    // base
    REP(i, N) {
        if (grid[i][0]) {
            if (i > 0 && grid[i-1][0]) comps[i][0] = cur-1;
            else { comps[i][0] = cur; ++cur; }
        }
    }

    nums[0] = cur;

    for (int i = 1; i < M; ++i) {
        int mod = i % 2;
        int old = (i + 1) % 2;
        VVI adj(cur);
        VB visited(N, false);
        VB adj_visited(cur, false);

        REP(j, N) {
            if (grid[j][i] && grid[j][i-1]) {

                adj[comps[j][old]].push_back(j);

            } else if (!grid[j][i]) visited[j] = true;
        }

        int newcur = 0;
        int isol = 0;
        REP(j, N) {
            if (visited[j]) continue;
            stack<int> s;
            s.push(j);
            bool willbeisol = true;

            while(!s.empty()) {

                int t = s.top();
                s.pop();
                if (visited[t]) continue;
                visited[t] = true;
                comps[t][mod] = newcur;
                if (t > 0 && grid[t-1][i]) s.push(t-1);
                if (t < N-1 && grid[t+1][i]) s.push(t+1);
                if (grid[t][i-1]) {
                    willbeisol=false;
                    if (!adj_visited[comps[t][old]]) {
                        for (int var : adj[comps[t][old]]) {
                            s.push(var);
                        }
                        adj_visited[comps[t][old]] = true;
                    }
                }
            }

            ++newcur;
            if (willbeisol) ++isol;
        }
        
        int nonisol = 0;
        for (VI viii : adj) {
            if (viii.size() == 0) {
                ++nonisol;
            }
        }
        nums[i] = nums[i-1] + newcur - (cur - nonisol);
        cur = newcur;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    cin >> N >> M;

    VVB grid(N, VB(M)); // true for white, false otherwise
    VVB rgrid(N, VB(M)); // true for white, false otherwise
    VVI connected(N, VI(M, -1));

    REP(i, N) {
        string tmp; cin >> tmp;
        REP(j, M) {
            grid[i][j] = (tmp.at(j) == '0');   
            rgrid[i][M-j-1] = (tmp.at(j) == '0');   
        }
    }

    int count = 0;
    int totalBlacks = 0;

    REP(i, N) {
        REP(j, M) {
            if (connected[i][j] != -1) continue;
            if (!grid[i][j]) ++totalBlacks;
            queue<pair<int,int>> q;
            q.push({i,j});
            while (!q.empty()) {
                int l = q.front().first;
                int r = q.front().second;
                q.pop();
                if (connected[l][r] != -1) continue;
                connected[l][r] = count;
                if (!outOfBounds(l-1,r) && grid[l][r] == grid[l-1][r]) q.push({l-1,r});
                if (!outOfBounds(l+1,r) && grid[l][r] == grid[l+1][r]) q.push({l+1,r});
                if (!outOfBounds(l,r-1) && grid[l][r] == grid[l][r-1]) q.push({l,r-1});
                if (!outOfBounds(l,r+1) && grid[l][r] == grid[l][r+1]) q.push({l,r+1});
            }
            ++count;
        }
    }

    vector<int> lc(M);
    vector<int> rc(M);
    computeComponents(grid, lc);
    computeComponents(rgrid, rc);

    int bestW = -1;
    int bestT = -1;

    REP(i, M) {

        int lwhites = (i == 0 ? 0 : lc[i-1]);
        int rwhites = (i == M-1 ? 0 : rc[M-2-i]);
        int whites = lwhites + rwhites;
        
        unordered_set<int> blackSet;
        REP(j, N) {
            if (i > 0) {
                if (!grid[j][i-1]) {
                    blackSet.insert(connected[j][i-1]);
                }
            }
            if (i < M-1) {
                if (!grid[j][i+1]) {
                    blackSet.insert(connected[j][i+1]);
                }
            }
            if (!grid[j][i]) {
                blackSet.insert(connected[j][i]);
            }
        }
        int blacks = totalBlacks - blackSet.size() + 1;

        if (whites + blacks > bestT) {
            bestW = whites;
            bestT = whites+blacks;
        } else if (whites+blacks == bestT && whites > bestW) {
            bestW = whites;
        }

    }

    cout << bestW << ' ' << (bestT - bestW) << '\n';

}

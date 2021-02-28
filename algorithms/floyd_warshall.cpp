/**
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/FloydWarshall.h
 * 
 * Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input: adj matrix m, where m[i][j] = inf if i and j are not adjacent
 * Output: m[i][j] is set to the shortest distance between i and j; inf if no path; -inf if negative-weight cycle.
 * Time: O(N^3)
 * Example: regionals/ridehailing.cpp
 */
const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>>& m) {
	int n = sz(m);
	FOR(i,0,n) m[i][i] = min(m[i][i], 0LL);
	FOR(k,0,n) FOR(i,0,n) FOR(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) {
			auto newDist = max(m[i][k] + m[k][j], -inf);
			m[i][j] = min(m[i][j], newDist);
		}
	FOR(k,0,n) if (m[k][k] < 0) FOR(i,0,n) FOR(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}

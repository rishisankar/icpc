/*
Knuth-Morris-Pratt string matching
Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/KMP.h
Time: O(n)
Returns all start indices of matching patterns in a string
*/

// pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
vi pi(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

// returns vector of start indices of matched patterns
vi kmp(const string& s, const string& pat) {
	vi p = pi(pat + '\0' + s), res;
	rep(i,sz(p)-sz(s),sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

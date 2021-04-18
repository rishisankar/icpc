/*
Min cyclic shift of a string
https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/MinRotation.h
Time: O(n)
*/
int minRotation(string s) {
	int a=0, N=sz(s); s += s;
	rep(b,0,N) rep(k,0,N) {
		if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}


/*
Full Lyndon Factorization:
https://cp-algorithms.com/string/lyndon_factorization.html
Time: O(n)
*/
vector<string> duval(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

/*
Application: smallest cyclic shift in O(n) - tested on leetcode (use above for better version though)
Example: https://leetcode.com/problems/orderly-queue/
*/
string min_cyclic_string(string s) {
    int n = s.size();
    s += s;
    vector<string> fac = duval(s);
    int i = 0;
    for (string s : fac) {
        if (i + s.size() >= n) break;
        i += s.size();
    }
    return s.substr(i, n);
}

// vector<ull> factor(ull n);
// time: O(n^{1/4})
// factors are not sorted!

ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

/*
Factor numbers from 1-n using prime sieve
O(n log(logn)) sieve preprocessing
O(log n) per query (all queries must be <= MAXN)
Source: https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/
Example: cses/math/counting_divisors
*/
void precompute_spf(vector<int>& spf, int MAXN) {
	MAXN++;
	spf.assign(MAXN, 0);
  spf[1] = 1;
	for (int i=2; i<MAXN; i++) spf[i] = i;
	for (int i=4; i<MAXN; i+=2) spf[i] = 2; // process powers of 2
	for (int i=3; i*i<MAXN; i++) {
		// checking if i is prime
    if (spf[i] == i) {
			// marking SPF for all numbers divisible by i
			for (int j=i*i; j<MAXN; j+=i) {  
				// marking spf[j] if it is not previously marked
				if (spf[j]==j) spf[j] = i;
      }
    }
	}
}
  
// return prime factorization in O(logn)
vector<int> factor(int x, VI& spf) {
  vector<int> ret;
  while (x != 1) {
		ret.push_back(spf[x]);
      x = x / spf[x];
    }
    return ret;
}


/*
Convert list of prime factors to list of divisors
Note that # of divisors is approx btwn O(n^(1/3)) and O(n^(1/2))
Tested, but easier approach is to just iterate from 1-->sqrt(n)
*/
vector<int> divisors(VI factors) {
    vector<pii> factor_counts;
    unordered_map<int,int> facs; // factor -> ind in factor_counts
    for (int i : factors) {
        if (facs.count(i)) {
            factor_counts[facs[i]].S++;
        } else {
            facs[i] = factor_counts.size();
            factor_counts.pb({i,1});
        }
    }
    VI divisors;
    stack<pii> s; // {unprocessed ind, cur val}
    s.push({0,1});
    while (!s.empty()) {
        pii t = s.top(); s.pop();
        if (t.F == factor_counts.size()) {
            divisors.pb(t.S);
            continue;
        }
        int scale = 1;
        rep(i,0,factor_counts[t.F].S+1) {
            s.push({t.F+1, t.S*scale});
            scale *= factor_counts[t.F].F;
        }
    }
    return divisors;
}
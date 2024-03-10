// works with dups

struct FT {
vector<ll> s;
FT(int n) : s(n) {}
void update(int pos, ll dif) { // a[pos] += dif
for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
}
ll query(int pos) { // sum of values in [0, pos)
ll res = 0;
for (; pos > 0; pos &= pos - 1) res += s[pos-1];
return res;
}
};


ll inv(vector<int> &v)
{
int MX=500;
FT ft(MX);
ll ans=0;
rep(i,0,sz(v))
{
ans+=ft.query(MX)-ft.query(v[i]+1);
ft.update(v[i],1);
}
return ans;
}


/**
 * count number of inversions in O(nlogn)
 * inversions = number of pairs (i,j) s.t. a[i] > a[j]
 * ll numInversions(vector<T>& arr);
 * example: math/camels.cpp
 * DOES NOT WORK WITH DUPLICATE VALS IN a
 */

typedef int T;

long long numInversions(vector<T>& a) {
  if (a.size() == 1) return 0;
  vector<T> left = vector<T>(a.begin(), a.begin() + a.size() / 2);
  vector<T> right = vector<T>(a.begin() + a.size() / 2, a.end());
  long long swaps = numInversions(left) + numInversions(right);
  a.clear();
  int i=0, j=0;
  while (i < left.size() && j < right.size()) {
    if (left[i] < right[j]) {
      a.push_back(left[i++]);
    } else {
      a.push_back(right[j++]);
      swaps += left.size() - i;
    }
  }
  while (i < left.size()) {
    a.push_back(left[i++]);
  }
  while (j < right.size()) {
    a.push_back(right[j++]);
  }
  return swaps;
}

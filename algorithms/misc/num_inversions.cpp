/**
 * count number of inversions in O(nlogn)
 * inversions = number of pairs (i,j) s.t. a[i] > a[j]
 * ll numInversions(vector<T>& arr);
 * example: math/camels.cpp
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

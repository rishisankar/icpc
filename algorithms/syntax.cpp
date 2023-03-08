cout << setprecision(10) << "...";

// do something for all permutations of s! (Starts sorted)
do {
  std::cout << s << '\n';
} while(std::next_permutation(s.begin(), s.end()));

lower_bound(all(v),val); // iter to first elt >= val
upper_bound(all(v),val); // iter to first elt > val

const int mod1 = 1000000007; // 1e9+7
const int mod2 = 998244353;

getline(cin, x); // (getline clears \n from buffer, cin doesn't)
cin.ignore(10000, '\n'); //after cin, before getline!
while (getline(cin, x)) // to read all lines
while (cin >> x) // to read all tokens

// count bits
__builtin_popcount() // integers
__builtin_popcountll() // ll/ull

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // add the useful ones
#pragma GCC optimize("O3") // can help
#pragma GCC optimize("Ofast") // can help sometimes

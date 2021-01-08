#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

#define PI 3.1415926535897932384626433832795

int main() {
    long long n, k, d;
    cin >> n >> k >> d;
    bool favored[61] = {false};
    long long base = 2;
    long long start = pow(base, n+1) - 2;
    start -= d;
    for (int i = 0; i < k; ++i) {
        int a;
        cin >> a;
        favored[a] = true;
        start -= pow(base, a-1);
    }
    if (start < 0) {
        cout << 0 << endl;
        return 0;
    }
    else {
        cout << pow(base, k) << endl;
        return 0;
    }

}
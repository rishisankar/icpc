#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int houses[200001] = {0};
    int houses2[200001] = {0};

    for (int i = 0; i < n; ++i) {
        cin >> houses[i];
        houses2[n-1-i] = houses[i];
    }

    long long sum = 0;
    long long sum2 = 0;
    if (n % 2 == 0) {
        int len = n/2;
        for (int i = 0; i < len; ++i) {
            sum += houses[i];
            sum2 += houses2[i];
        }
        long long m = max(sum, sum2);
        sum = sum - houses[0] + houses[n/2];
        sum2 = sum2 - houses2[0] + houses2[n/2];
        m = max(m, max(sum, sum2));
        for (int i = 3; i < n/2; i += 2) {
            len--;
            sum = sum - houses[i - 1] - houses[i - 2] + houses[i+len-1];
            sum2 = sum2 - houses2[i - 1] - houses2[i - 2] + houses2[i+len-1];
            m = max(m, max(sum, sum2));
        }
        cout << m << endl;
        return 0;
    } else {
        int len = n/2 + 1;
        for (int i = 0; i < len; ++i) {
            sum += houses[i];
            sum2 += houses2[i];
        }
        long long m = max(sum, sum2);
        for (int i = 2; i < n/2+1; i += 2) {
            len--;
            sum = sum - houses[i - 1] - houses[i - 2] + houses[i+len-1];
            sum2 = sum2 - houses2[i - 1] - houses2[i - 2] + houses2[i+len-1];
            m = max(m, max(sum, sum2));
        }
        cout << m << endl;
        return 0;
    }
}
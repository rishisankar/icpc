#include <bits/stdc++.h>
using namespace std;

void addOne(vector<int> &digits, int n) {

    for (int i = n-1; i >= 0; --i) {
        if (digits[i] < 9) {
            ++digits[i];
            return;
        } else {
            digits[i] = 0;
        }
    }

}

int main() {

    string s; cin >> s;
    vector<int> digits;

    for (int i = 0; i < 10; ++i) {
        digits.push_back(0);
    }

    for (int i = 0; i < s.size(); ++i) {
        int tmp = s.at(i) - '0';
        digits.push_back(tmp);
    }

    int n = digits.size();

    long long count = 0;

    for (int i = n-1; i >= 0; --i) {
        
        int digit = digits[i];
        if (0 <= digit && digit <= 4) {
            count += digit;
        } else if (digit == 5) {
            count += digit;
            if (5 <= digits[i-1] && digits[i-1] <= 9) {
                addOne(digits, i);
            }
        } else {
            addOne(digits, i);
            count += (10 - digit);
        }

    }

    cout << count << '\n';


    
}
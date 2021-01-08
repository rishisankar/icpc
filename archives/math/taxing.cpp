#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

ld scale(vector<vector<ld>> &bands, ld P, ld start) {

    ld scaled = 0.0;

    bool broken = false;
    ld prev = 0.0;
    // 500 * 1/(1-20/100)
    for (vector<ld> band : bands) {

        ld range = band[0] - prev;
        //prev = band[0];
        ld percent = 1.0;
        percent -= band[1]/100.0;
        ld scaledRange = range*percent;

        ld scaleFactor = 1.0 / percent;
        if (start <= scaledRange) {
            scaled += start * scaleFactor;
            broken = true;
            break;
        } else {
            scaled += range;
            start -= scaledRange;
        }


    }

    if (!broken) {
        ld scaleFactor = 1.0;
        ld percent = 1.0;
        percent -= P/100.0;
        scaleFactor /= percent;
        scaled += start * scaleFactor;
    }

    return scaled;



}

void calc(vector<vector<ld>> &bands, ld P, ld start, ld add) {

    cout << scale(bands, P, start + add) - scale(bands, P, start) << '\n';

}

int main() {

    cout.setf(ios::fixed);
    cout.precision(7);

    int B;
    cin >> B;

    vector<vector<ld>> bands(B, vector<ld>(2));

    for (int i = 0; i < B; ++i) {
        cin >> bands[i][0] >> bands[i][1];
    }

    ld P;
    cin >> P;

    int F;
    cin >> F;

    vector<vector<ld>> friends(F, vector<ld>(2));

    for (int i = 0; i < F; ++i) {
        cin >> friends[i][0] >> friends[i][1];
    }

    for (int i = 0; i < F; ++i) {
        calc(bands, P, friends[i][0], friends[i][1]);
    }

}
#include <iostream>

using namespace std;

int main() {
    int dog_sums[100002] = {};
    int bun_sums[100002] = {};
    int H, B;
    
    cin >> H;
    for (int i = 0; i < H; ++i) {
        int num;
        cin >> num;
        for (int j = 100001; j >= num; --j) {
            if (dog_sums[j-num] != 0 && (dog_sums[j] == 0 || dog_sums[j-num] < dog_sums[j]))
                dog_sums[j] = dog_sums[j-num] + 1;
        }
        dog_sums[num] = 1;
    }

    cin >> B;
    for (int i = 0; i < B; ++i) {
        int num;
        cin >> num;
        for (int j = 100001; j >= num; --j) {
            if (bun_sums[j-num] != 0 && (bun_sums[j] == 0 || bun_sums[j-num] < bun_sums[j]))
                bun_sums[j] = bun_sums[j-num] + 1;
        }
        bun_sums[num] = 1;
    }

    int min = -1;
    for (int i = 0; i < 100002; ++i) {
        int i1 = dog_sums[i];
        int i2 = bun_sums[i];
        if (i1 == 0 || i2 == 0) continue;
        if (min == -1 || i1 + i2 < min)
            min = i1 + i2;
    }
    if (min == -1)
        cout << "impossible" << endl;
    else
        cout << min << endl;
}
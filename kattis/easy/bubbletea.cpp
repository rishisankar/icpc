#include <iostream>

using namespace std;

int main() {
    int tea[1001];
    int toppings[1001];
    int N, M;
    long money;
    long cheapest = 10000000000;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> tea[i];
    }
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> toppings[i];
    }
    for (int i = 0; i < N; ++i) {
        int num_pairs;
        cin >> num_pairs;
        for (int j = 0; j < num_pairs; ++j) {
            long tmp;
            cin >> tmp;
            long cost = toppings[tmp - 1] + tea[i];
            if (cost < cheapest) {
                cheapest = cost;
            }
        }
    }
    cin >> money;
    long val = money / cheapest - 1;
    if (val < 0) val = 0;
    cout << val << endl;
}
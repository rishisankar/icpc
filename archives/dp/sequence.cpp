#include <iostream>

using namespace std;

struct stru {
    int len;
    int arr[202];
    stru() {
        len = 0;
    }
};

int main() {
    int n, tmp;
    while (true) {
        cin >> n;
        if (n == 0) break;

        stru dp[202];
        stru first;
        first.len = 1;
        cin >> first.arr[0];
        dp[1] = first;
        for (int i = 2; i <= n; ++i) {
            int new_num;
            cin >> new_num;
            int min_index = 0;
            int max_val = 0;
            for (int j = 1; j < i; ++j) {
                if (dp[j].arr[dp[j].len - 1] < new_num) {
                    if (dp[j].len > max_val) {
                        max_val = dp[j].len;
                        min_index = j;
                    } else if (dp[j].len == max_val) {
                        int* oldarr = dp[min_index].arr;
                        int* tryarr = dp[j].arr;
                        for (int i = 0; i < max_val; ++i) {
                            if (oldarr[i] == tryarr[i]) continue;
                            else if (oldarr[i] < tryarr[i]) break;
                            else {
                                max_val = dp[j].len;
                                min_index = j;
                                break;
                            }
                        }
                    }
                }
            }
            stru next;
            next.len = max_val + 1;
            if (next.len == 1) {
                next.arr[0] = new_num;
            } else {
                for (int j = 0; j < dp[min_index].len; ++j) {
                    next.arr[j] = dp[min_index].arr[j];
                }
                next.arr[next.len - 1] = new_num;
            }
            dp[i] = next;
        }

        int answer_index = 1;
        for (int i = 2; i <= n; ++i) {
            if (dp[i].len > dp[answer_index].len || (dp[i].len == dp[answer_index].len && dp[i].arr[dp[i].len-1] < dp[answer_index].arr[dp[i].len-1]))
                answer_index = i;
        }
        stru answer = dp[answer_index];
        cout << answer.len;
        for (int i = 0; i < answer.len; ++i) {
            cout << " " << answer.arr[i];
        }
        cout << endl;
    }
}
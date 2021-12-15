#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    int arr[7];

    arr[0] = (n/1000000) % 10;
    arr[1] = (n/100000) % 10;
    arr[2] = (n/10000) % 10;
    arr[3] = (n/1000) % 10;
    arr[4] = (n/100) % 10;
    arr[5] = (n/10) % 10;
    arr[6] = n % 10;

    int newarr[7];
    newarr[0] = arr[0];
    for (int i = 1; i < 7; ++i) {
        newarr[i] = (arr[i] + 10 - arr[i-1]) % 10;
    }

    for (int i = 0; i < 7; ++i) {
        cout << newarr[i];
    }

    cout << endl;
    
    
}
#include <bits/stdc++.h>
using namespace std;

char decode(char key, char cipher) {

// A,S -> S
    int k = key - 'A';
    int c = cipher - 'A';

    int tmp = (c - k + 26) % 26;
    char tmp2 = 'A' + tmp;
    return tmp2;

}

int main() {
    string cipher;
    string key;
    cin >> cipher >> key;

    char buf[1000] = {0};
    for (int i = 0; i < key.size(); ++i) {
        buf[i] = key.at(i);
    }

    for (int i = 0; i < cipher.size(); ++i) {
        buf[i+key.size()] = decode(buf[i], cipher.at(i));
    }

    cout << buf + key.size() << '\n';
}
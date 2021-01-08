#include <iostream>
using namespace std;

int main() {
    string line;
    cin >> line;

    int pol1 = 0;
    int pol2 = 0;
    int pol3 = 0;
    
    char prev = line.at(0);

    if (line.size() == 1) {
        cout << "0 0 0" << endl;
        return 0;
    }

    char temp = line.at(1);
    if (prev == 'D') {
        pol1++;
        if (temp == 'U') {
            pol2 += 2;
        }
    } else {
        if (temp == 'D') {
            pol1 += 2;
        }
        pol2++;
    }

    for (int i = 2; i < line.size(); ++i) {
        char c = line.at(i);
        if (c == 'D') {
            pol1 += 2;
        } else {
            pol2 += 2;
        }
    }
    for (int i = 1; i < line.size(); ++i) {
        char c = line.at(i);
        if (prev != c) {
            pol3++;
        }
        prev = c;
    }

    cout << pol1 << " " << pol2 << " " << pol3 << endl;
}
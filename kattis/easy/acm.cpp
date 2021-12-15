#include <iostream>
#include <string>
using namespace std;

int main() {
    int min;
    char letter;
    string correct;

    int mins[200] = {};

    int totalSolved = 0;
    int numMinutes = 0;

    while (true) {
        cin >> min;
        if (min == -1) break;
        
        cin >> letter;
        cin >> correct;

        if (correct.compare("right") == 0) {
            totalSolved++;
            numMinutes += min;
            numMinutes += mins[letter];
        } else {
            mins[letter] += 20;
        }
    }

    cout << totalSolved << " " << numMinutes << endl;
}
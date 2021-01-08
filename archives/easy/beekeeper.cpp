#include <iostream>
#include <string>

using namespace std;

int main() {
    int numWords;
    while (true) {
        cin >> numWords;
        cin.ignore(10000,'\n');
        if (numWords == 0) break;

        string favoriteWord;
        int best = -1;
        string word;
        for (int i = 0; i < numWords; ++i) {
            getline(cin, word);
            char prev = word[0];
            int repeats = 0;
            for (int j = 1; j < word.size(); ++j) {
                if (word[j] == prev) {
                    if (prev == 'a' || prev == 'e' || prev == 'i' || prev == 'o' || prev == 'u' || prev =='y')
                        ++repeats;
                }
                prev = word[j];
            }
            if (repeats > best) {
                favoriteWord = word;
                best = repeats;
            }
        }

        cout << favoriteWord << endl;

    }
}
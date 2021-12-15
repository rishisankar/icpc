#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()
#define PB push_back

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

struct entry {
    string name;
    string email;
    string email_lower;
};

void split(string s, string delim, vector<string>& result) {
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)
    {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }

    result.push_back(s.substr(start, end));
}

bool comp(entry& e1, entry& e2) {
    return e1.email_lower < e2.email_lower;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    string del = "\t";

    unordered_set<string> namesI, emailsI, namesO, emailsO;
    vector<entry> nI, nO;

    string line;
    while (true) {
        getline(cin, line);
        if (line == "") {
            break;
        }

        vector<string> res;
        split(line, del, res);
        string name = res[1] + " " + res[0];
        string email = res[2];
        entry tmp;
        tmp.name = name; tmp.email = email;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        tmp.email_lower = email;
        nI.PB(tmp);
        namesI.insert(name);
        emailsI.insert(email);
    }

    while (!cin.eof()) {
        getline(cin, line);
        if (line == "") break;
        vector<string> res;
        split(line, del, res);
        string name = res[1] + " " + res[0];
        string email = res[2];
        entry tmp;
        tmp.name = name; tmp.email = email;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        tmp.email_lower = email;
        nO.PB(tmp);
        namesO.insert(name);
        emailsO.insert(email);
    }

    sort(nO.begin(), nO.end(), comp);
    sort(nI.begin(), nI.end(), comp);

    vector<string> outputLines;

    for (int i = 0; i < nI.size(); ++i) {
        string name = nI[i].name;
        string email = nI[i].email;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        if (namesO.find(name) == namesO.end() && emailsO.find(email) == emailsO.end()) {
            string tmp = "I " + nI[i].email + " " + nI[i].name + "\n";
            outputLines.PB(tmp);
        }
    }

    for (int i = 0; i < nO.size(); ++i) {
        string name = nO[i].name;
        string email = nO[i].email;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        if (namesI.find(name) == namesI.end() && emailsI.find(email) == emailsI.end()) {
            string tmp = "O " + nO[i].email + " " + nO[i].name + "\n";
            outputLines.PB(tmp);
        }
    }

    if (outputLines.size() == 0) {
        cout << "No mismatches.\n";
    } else {
        for (string s : outputLines) {
            cout << s;
        }
    }
}
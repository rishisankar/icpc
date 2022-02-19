#include <bits/stdc++.h>
using namespace std;

map<pair<string,int>, vector<vector<string>>> db;

bool isvalid(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == ',' || c == '(' || c == ')';
}

int compute(string fc, vector<string>& args) {
  if (!(db.count({fc, args.size()}))) return 0;

  vector<vector<string>> matches = db[{fc, args.size()}];

  int ct = 0;
  for (vector<string> match : matches) {

    unordered_map<string, string> vars;
    bool valid = true;
    for (int i = 0; i < args.size(); ++i) {
      if (args[i] == "_") continue;
      else if (args[i][0] == '_') {
        if (vars.count(args[i])) {
          if (vars[args[i]] != match[i]) {
            valid = false;
            break;
          }
        } else {
          vars[args[i]] = match[i];
        }
      } else {
        if (match[i] != args[i]) {
          valid = false;
          break;
        }
      }
    }
    if (valid) ++ct;
  }

  return ct;
}

int main() 
{
  string s;
  bool facts = true;
  while (getline(cin, s)) {
    if (s == "") {
      facts = false;
      continue;
    }

    if (facts) {
      bool ra = false;
      string fc = "";
      string v = "";
      vector<string> args;
      for (int i = 0; i < s.size(); ++i) {
        if (!isvalid(s[i])) continue;

        if (!ra) {
          if (s[i] != '(') {
            fc += s[i];
          } else {
            ra = true;
          }
        } else {
          if (s[i] != ')' && s[i] != ',') {
            v += s[i];
          } else {
            args.push_back(v);
            v = "";
            if (s[i] == ')') {
              ra = false;
              db[{fc,args.size()}].push_back(args);
              fc = "";
              v = "";
              args.clear();
            }
          }
        }
      }
    } else {
      bool ra = false;
      string fc = "";
      string v = "";
      vector<string> args;
      for (int i = 0; i < s.size(); ++i) {
        if (!isvalid(s[i])) continue;

        if (!ra) {
          if (s[i] != '(') {
            fc += s[i];
          } else {
            ra = true;
          }
        } else {
          if (s[i] != ')' && s[i] != ',') {
            v += s[i];
          } else {
            args.push_back(v);
            v = "";
            if (s[i] == ')') {
              ra = false;
              cout << compute(fc, args) << '\n';
              fc = "";
              v = "";
              args.clear();
            }
          }
        }
      }
    }
  }

  // for (auto it : db) {
  //   cout << it.first.first << ' ' << it.first.second << ' ' << it.second.size() << '\n';
  //   for (vector<string> a : it.second) {
  //     for (string st : a) cout << ' ' << st;
  //     cout << '\n';
  //   }
  //   cout << '\n';
  // }


}
#include <iostream>
using namespace std;
int main ()
{
 int n;
 cin >> n; // seed read
 while(!cin.eof()) { // eof() valid only after attempted read
 cout << n;
 cout << ' ';
 while (n > 1) {
 cout << '1';
 n--;
 }
 cout << "0\n"; // the newline character, \n, emits ASCII 0x0A
 cin >> n;
 }
 return 0; // indicate normal program termination
}
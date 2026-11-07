// AMPPZ 2021 H - Hasła, O(total length)
// shifting twice by d gives the same word only for 2d = 0 mod 26, and d = 13 is the only shift that changes it
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        string s;
        cin >> s;
        for (char& ch : s) ch = char('a' + (ch - 'a' + 13) % 26);   // rot13
        cout << s << "\n";                                           // the answer NIE never happens
    }
    return 0;
}

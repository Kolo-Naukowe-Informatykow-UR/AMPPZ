// AMPPZ 2022 C - Ctrl+C Ctrl+V, O(length) per data set
// greedy: change the last letter of every occurrence found from the left
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    string s;
    while (z--) {
        cin >> s;
        int changes = 0;
        for (int i = 0; i + 4 <= (int)s.size(); i++) {
            if (s.compare(i, 4, "ania") == 0) {
                s[i + 3] = '#';                    // '#' is in no occurrence, so nothing new appears
                changes++;
            }
        }
        cout << changes << "\n";
    }
    return 0;
}

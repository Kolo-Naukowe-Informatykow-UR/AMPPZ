// AMPPZ 2023 J - Juliet Unifies Ones, O(n^3) with n <= 50
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    int best = INT_MAX;
    // the kept ones form the block [l, r): remove zeros inside it and ones outside it
    for (int l = 0; l <= n; l++)
        for (int r = l; r <= n; r++) {
            int cost = 0;
            for (int i = 0; i < n; i++) {
                bool inside = (l <= i && i < r);
                if (inside && s[i] == '0') cost++;
                if (!inside && s[i] == '1') cost++;
            }
            best = min(best, cost);
        }

    cout << best << "\n";
    return 0;
}

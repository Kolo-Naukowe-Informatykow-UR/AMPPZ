// AMPPZ 2024 K - Kwadracik, O(1) per test case
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;

        // c lies directly below a, so the row length is fixed
        long long w = c - a;

        // b right of a, d right of c, w at least 2, a not in the last column
        if (b == a + 1 && d == c + 1 && w >= 2 && a % w != 0) {
            long long h = (a - 1) / w + 2;  // row of a, plus the row below it
            cout << h << " " << w << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
    return 0;
}

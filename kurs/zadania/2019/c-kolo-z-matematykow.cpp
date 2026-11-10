// AMPPZ 2019 C - Kolo (z) Matematykow, O(n log n) per data set
// a polygon exists iff there are at least 3 sides and the longest is shorter than the sum of the rest
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<ll> len(n);
        ll total = 0;
        for (auto& x : len) cin >> x, total += x;
        sort(len.begin(), len.end());

        // the longest side that fails can be in no polygon, so it goes away
        int cnt = n;
        while (cnt >= 3 && len[cnt - 1] >= total - len[cnt - 1]) {
            total -= len[cnt - 1];
            cnt--;
        }
        cout << (cnt >= 3 ? total : 0) << "\n";
    }
    return 0;
}

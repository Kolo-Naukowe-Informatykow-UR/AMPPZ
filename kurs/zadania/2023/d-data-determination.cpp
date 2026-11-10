// AMPPZ 2023 D - Data Determination, O(n log n) per scenario
// split the results into below m, equal to m and above m; the middle of the chosen k must be m
// (two copies of m when k is even), or for even k a pair a < m < b with a + b = 2m
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool possible(vector<ll> a, int k, ll m) {
    sort(a.begin(), a.end());
    int n = a.size();
    int below = lower_bound(a.begin(), a.end(), m) - a.begin();
    int equal = upper_bound(a.begin(), a.end(), m) - a.begin() - below;
    int above = n - below - equal;
    int h = (k - 1) / 2;                           // at most h chosen values below the middle and h above it

    // the middle (both middles for even k) equal to m; k - 2h copies of m are forced
    if (min(below, h) + min(above, h) + equal >= k) return true;
    if (k % 2 == 1) return false;

    // even k: middles a < m < b with a + b = 2m; the largest such a is the best one
    int i = below - 1, j = below + equal;
    while (i >= 0 && j < n) {
        ll s = a[i] + a[j];
        if (s < 2 * m) j++;
        else if (s > 2 * m) i--;
        else {
            int le = upper_bound(a.begin(), a.end(), a[i]) - a.begin();       // values <= a
            int ge = n - (lower_bound(a.begin(), a.end(), a[j]) - a.begin());  // values >= b
            return le - 1 >= h && ge - 1 >= h;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        ll m;
        cin >> n >> k >> m;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        cout << (possible(a, k, m) ? "TAK" : "NIE") << "\n";
    }
    return 0;
}

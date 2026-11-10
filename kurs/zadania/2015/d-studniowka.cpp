// AMPPZ 2015 D - Studniówka, O((n + m) log(n + m))
// sort both lists; for each girl the fitting boys form a window that only moves right
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<ll> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll pairs = 0;
    int lo = 0, hi = 0;                            // boys in [lo, hi) fit the current girl
    for (int i = 0; i < n; i++) {
        while (lo < m && b[lo] < a[i] - k) lo++;   // too short for this girl and every next one
        while (hi < m && b[hi] <= a[i] + k) hi++;  // tall enough to fit
        pairs += hi - lo;
    }
    cout << pairs << "\n";
    return 0;
}

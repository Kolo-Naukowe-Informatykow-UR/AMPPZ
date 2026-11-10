// AMPPZ 2018 J - Jednakowe szaliki, O(n log n)
// sort; the best group is a window, its cheapest common length is the median;
// the cost of a window comes from prefix sums, the window moves with two pointers
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    vector<ll> pre(n + 1, 0);                      // pre[i] = a[0] + ... + a[i - 1]
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];

    // moments needed to bring a[l..r] to the length of its median
    auto cost = [&](int l, int r) {
        int md = (l + r) / 2;
        ll left = a[md] * (md - l) - (pre[md] - pre[l]);
        ll right = (pre[r + 1] - pre[md + 1]) - a[md] * (r - md);
        return left + right;
    };

    int best = 0, l = 0;
    for (int r = 0; r < n; r++) {
        while (cost(l, r) > k) l++;                // a shorter window never costs more
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
    return 0;
}

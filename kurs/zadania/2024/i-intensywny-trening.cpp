// AMPPZ 2024 I - Intensywny trening, O(n log n)
// after sorting, the best match is the k largest against the k smallest; only the boundary
// values have a choice: top = k-th largest value, bot = k-th smallest value;
// count = C(#top, k - #greater) * C(#bot, k - #smaller), with the boundary players shared when
// top == bot; if all levels are equal, every match has difference 0: C(n, k) * C(n - k, k) / 2
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long power(long long a, long long e) {
    long long r = 1;
    for (a %= MOD; e > 0; e >>= 1, a = a * a % MOD)
        if (e & 1) r = r * a % MOD;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());

    vector<long long> fact(n + 1, 1), inv(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    inv[n] = power(fact[n], MOD - 2);
    for (int i = n; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;
    auto C = [&](int m, int t) { return (t < 0 || t > m) ? 0 : fact[m] * inv[t] % MOD * inv[m - t] % MOD; };

    long long diff = 0;
    for (int i = 0; i < k; i++) diff += a[n - 1 - i] - a[i];

    long long ways;
    if (a[0] == a[n - 1]) {
        ways = C(n, k) * C(n - k, k) % MOD * power(2, MOD - 2) % MOD;   // unordered pair of teams
    } else {
        long long top = a[n - k], bot = a[k - 1];
        int greater = a.end() - upper_bound(a.begin(), a.end(), top);
        int cntTop = upper_bound(a.begin(), a.end(), top) - lower_bound(a.begin(), a.end(), top);
        int smaller = lower_bound(a.begin(), a.end(), bot) - a.begin();
        int cntBot = upper_bound(a.begin(), a.end(), bot) - lower_bound(a.begin(), a.end(), bot);
        int x = k - greater, y = k - smaller;  // boundary players each team still needs
        if (top != bot) ways = C(cntTop, x) * C(cntBot, y) % MOD;
        else ways = C(cntTop, x) * C(cntTop - x, y) % MOD;    // both teams pick from one value
    }
    cout << diff << " " << ways << "\n";
}

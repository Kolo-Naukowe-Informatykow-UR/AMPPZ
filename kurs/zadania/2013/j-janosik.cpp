// AMPPZ 2013 J - Janosik, O(log n)
// boxes do not interact; in a box of i bags halving doubles the number of boxes and taking one bag
// out does not, so exactly 2^floor(log2 i) bags are given away and i - 2^floor(log2 i) stay in the pocket
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll n) {
    ll kept = n * (n + 1) / 2;                     // all bags, up to 5 * 10^17
    for (ll p = 1; p <= n; p *= 2) {               // boxes p..2p-1 give away p bags each
        ll last = min(2 * p - 1, n);
        kept -= (last - p + 1) * p;
    }
    return kept;
}

int main() {
    ll n;
    cin >> n;
    cout << solve(n) << "\n";
    return 0;
}

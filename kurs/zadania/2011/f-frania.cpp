// AMPPZ 2011 F - Frania
// greedy from the largest d: one colour with >= 5d if any, else colours >= 3d and >= 2d; always the smallest fitting
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    for (auto &x : d) cin >> x;
    multiset<int> pegs;
    for (int i = 0; i < k; i++) { int l; cin >> l; pegs.insert(l); }
    sort(d.rbegin(), d.rend());                // largest demand first

    // removes the smallest colour with at least need pegs; false if there is none
    auto take = [&](long long need) {
        auto it = pegs.lower_bound((int)min(need, (long long)INT_MAX));
        if (it == pegs.end()) return false;
        pegs.erase(it);
        return true;
    };

    long long colours = 0;
    for (int x : d) {
        if (take(5LL * x)) { colours += 1; continue; }   // socks and shirts on one colour
        if (!take(3LL * x) || !take(2LL * x)) { puts("NIE"); return 0; }
        colours += 2;
    }
    printf("%lld\n", colours);
}

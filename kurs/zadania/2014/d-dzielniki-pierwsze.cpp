// AMPPZ 2014 D - Dzielniki, variant O(n + M log log M)
// div[v] = how many elements are divisible by v; it is a sum over multiples, built prime by prime
// (like the sieve); each element a_j is then counted once for every element a_i dividing it
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0;
    for (auto& x : a) {
        cin >> x;
        mx = max(mx, x);
    }
    vector<int> cnt(mx + 1, 0);
    for (int x : a) cnt[x]++;

    vector<int> div(cnt);                          // after the loop: sum of cnt[w] over multiples w of v
    vector<bool> composite(mx + 1, false);
    for (int p = 2; p <= mx; p++) {
        if (composite[p]) continue;
        for (ll q = (ll)p * p; q <= mx; q += p) composite[q] = true;
        for (int v = mx / p; v >= 1; v--) div[v] += div[v * p];   // downwards: div[v * p] is already full
    }

    ll pairs = 0;
    for (int v = 1; v <= mx; v++) pairs += (ll)cnt[v] * div[v];
    pairs -= n;                                    // every element was paired with itself
    cout << pairs << "\n";
    return 0;
}

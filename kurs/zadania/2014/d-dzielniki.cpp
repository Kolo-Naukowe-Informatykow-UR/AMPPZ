// AMPPZ 2014 D - Dzielniki, O(n + M log M) for values up to M
// count every value; a value v pairs with each copy of v and of its multiples 2v, 3v, ...;
// walking the multiples of all v costs M/1 + M/2 + ... + M/M = O(M log M)
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
    vector<int> cnt(mx + 1, 0);                    // cnt[v] = how many times v occurs
    for (int x : a) cnt[x]++;

    ll pairs = 0;
    for (int v = 1; v <= mx; v++) {
        if (cnt[v] == 0) continue;                 // absent divisors add nothing
        pairs += (ll)cnt[v] * (cnt[v] - 1);        // equal values, ordered, i != j
        ll multiples = 0;
        for (int w = 2 * v; w <= mx; w += v) multiples += cnt[w];
        pairs += cnt[v] * multiples;
    }
    cout << pairs << "\n";
    return 0;
}

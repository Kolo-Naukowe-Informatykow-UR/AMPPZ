// AMPPZ 2011 E - Eksterminacja swistakow
// holes sorted in an array, players in a set; a player only matters between its two neighbours
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 4e18;
vector<ll> x;                                  // hole positions, sorted
set<ll> z;                                     // player positions
ll l;

// number of holes in [lo, hi], two binary searches
ll holes(ll lo, ll hi) {
    if (lo > hi) return 0;
    return upper_bound(x.begin(), x.end(), hi) - lower_bound(x.begin(), x.end(), lo);
}

// holes covered by the player at *it and by no other player
ll own(set<ll>::iterator it) {
    ll q = *it, lo = q - l, hi = q + l;
    if (it != z.begin()) lo = max(lo, *prev(it) + l + 1);   // left neighbour covers up to its pos + l
    if (next(it) != z.end()) hi = min(hi, *next(it) - l - 1);
    return holes(lo, hi);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, d;
    cin >> n >> m >> d >> l;
    x.assign(n, 0);
    for (int i = 1; i < n; i++) cin >> x[i];
    ll covered = 0;
    for (int i = 0; i < m; i++) {
        ll q; cin >> q;
        covered += own(z.insert(z.end(), q));  // input is sorted: no right neighbour yet, insertion at the end is O(1)
    }
    string out;
    out += to_string(covered) + '\n';
    for (int i = 0; i < d; i++) {
        ll p, r; cin >> p >> r;
        auto it = z.find(p);
        covered -= own(it);
        z.erase(it);
        covered += own(z.insert(r).first);
        out += to_string(covered) + '\n';
    }
    fputs(out.c_str(), stdout);
}

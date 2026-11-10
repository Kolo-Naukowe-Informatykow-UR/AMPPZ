// AMPPZ 2013 D - Demonstracje, O(n log n)
// sweep over sorted ends: time covered by exactly one demonstration is its own gain,
// time covered by exactly two is a shared gain of that pair; best of top two singles and all pairs
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<ll, int>> ev;                      // (time, +id start or -id end), ids from 1
    ev.reserve(2 * n);
    for (int i = 1; i <= n; i++) {
        ll a, b;
        cin >> a >> b;
        ev.push_back({a, i});
        ev.push_back({b, -i});
    }
    sort(ev.begin(), ev.end());

    vector<ll> solo(n + 1, 0);                     // time when only i is active
    vector<tuple<int, int, ll>> shared;            // (i, j, time when only i and j are active)
    vector<int> act, where(n + 1);                 // active ids, position of each id in act

    for (size_t e = 0; e < ev.size();) {
        ll t = ev[e].first;
        for (; e < ev.size() && ev[e].first == t; e++) {
            int id = ev[e].second;
            if (id > 0) {
                where[id] = act.size();
                act.push_back(id);
            } else {                               // remove in O(1): move the last one into the hole
                id = -id;
                int last = act.back();
                act[where[id]] = last;
                where[last] = where[id];
                act.pop_back();
            }
        }
        if (e == ev.size()) break;
        ll len = ev[e].first - t;                  // the active set is constant until the next time
        if (act.size() == 1) solo[act[0]] += len;
        else if (act.size() == 2) shared.push_back({min(act[0], act[1]), max(act[0], act[1]), len});
    }

    // two best singles (removing them saves at least their own times)
    vector<ll> top = solo;
    sort(top.rbegin(), top.rend());
    ll best = top[0] + top[1];

    // pairs with shared time: merge equal pairs, then own times plus shared time
    sort(shared.begin(), shared.end());
    for (size_t s = 0; s < shared.size();) {
        auto [i, j, len] = shared[s];
        ll both = 0;
        for (; s < shared.size() && get<0>(shared[s]) == i && get<1>(shared[s]) == j; s++)
            both += get<2>(shared[s]);
        best = max(best, solo[i] + solo[j] + both);
    }
    cout << best << "\n";
    return 0;
}

// AMPPZ 2012 J - Jutro, O(n log n)
// do tasks by deadline (earliest first); schedule them backwards from the latest deadline
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<ll, ll>> tasks(n);                 // (deadline t, duration d)
    for (auto& [t, d] : tasks) cin >> d >> t;
    sort(tasks.begin(), tasks.end());

    // walk from the latest deadline down: each task ends as late as possible
    ll start = LLONG_MAX;                          // start of the block already planned
    for (int i = n - 1; i >= 0; i--) {
        auto [t, d] = tasks[i];
        start = min(start, t) - d;
    }
    cout << start << "\n";                         // days of rest before the first task
    return 0;
}

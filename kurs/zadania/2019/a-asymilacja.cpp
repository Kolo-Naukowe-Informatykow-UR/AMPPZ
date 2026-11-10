// AMPPZ 2019 A - Asymilacja, O(n log n) per data set
// a mobilized planet with m people gives +m ships in total, so mobilize first,
// always the largest planet we can afford, until the ships cover all other planets
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        ll ships;
        cin >> n >> ships;
        vector<ll> a(n);
        ll rest = 0;                               // people on planets not mobilized yet
        for (auto& x : a) cin >> x, rest += x;
        sort(a.begin(), a.end());

        priority_queue<ll> affordable;             // the largest affordable planet on top
        int next = 0, mobilizations = 0;
        bool ok = true;
        while (ships < rest) {
            while (next < n && a[next] <= ships) affordable.push(a[next++]);
            if (affordable.empty()) { ok = false; break; }
            ll m = affordable.top();
            affordable.pop();
            ships += m;                            // pay m, get back 2m
            rest -= m;
            mobilizations++;
        }
        cout << (ok ? mobilizations : -1) << "\n";
    }
    return 0;
}

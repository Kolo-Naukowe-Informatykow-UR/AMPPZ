// AMPPZ 2012 C - Ciag, O(n)
// two neighbouring windows differ by a[i] and a[i + k], so all windows are even iff a[i] and a[i + k]
// always have the same parity and the first window is even: every class i mod k gets one parity,
// and the number of odd classes must be even
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> odd(k, 0), total(k, 0);
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        odd[i % k] += a % 2;
        total[i % k]++;
    }

    ll changes = 0;
    int oddClasses = 0, fix = INT_MAX;
    for (int r = 0; r < k; r++) {
        int o = odd[r], e = total[r] - odd[r];
        changes += min(o, e);                      // make the class all odd or all even, cheaper way
        if (o > e) oddClasses++;
        fix = min(fix, abs(o - e));                // extra cost of choosing the other parity here
    }
    if (oddClasses % 2 == 1) changes += fix;       // the first window must hold an even number of odd values
    cout << changes << "\n";
    return 0;
}

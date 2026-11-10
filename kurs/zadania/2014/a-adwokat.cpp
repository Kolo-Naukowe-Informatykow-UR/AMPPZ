// AMPPZ 2014 A - Adwokat, O(n + m)
// a good pair exists on a day iff the latest start is after the earliest end
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // per day: meeting with the earliest end and meeting with the latest start
    vector<int> minEnd(m + 1, INT_MAX), minEndId(m + 1, -1);
    vector<int> maxStart(m + 1, INT_MIN), maxStartId(m + 1, -1);
    for (int i = 1; i <= n; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        if (b < minEnd[d]) minEnd[d] = b, minEndId[d] = i;
        if (a > maxStart[d]) maxStart[d] = a, maxStartId[d] = i;
    }

    string out;
    for (int d = 1; d <= m; d++) {
        // a meeting never starts after its own end, so the two ids differ when this holds
        if (minEndId[d] != -1 && maxStart[d] > minEnd[d])
            out += "TAK " + to_string(minEndId[d]) + " " + to_string(maxStartId[d]) + "\n";
        else
            out += "NIE\n";
    }
    cout << out;
    return 0;
}

// AMPPZ 2002 H - Sloneczne wczasy, O(n) per test
// p[i] = (sunny - cloudy) among the first i days; a term (j, i] is sunny when p[j] < p[i];
// dp[i] = best profit from the first i days = max(dp[i - 1], i + max(dp[j] - j) over j < i with p[j] < p[i]);
// dp[j] - j never grows (dp[j] <= dp[j - 1] + 1), so the best j is the first one with p[j] < p[i]:
// j = 0 when p[i] > 0, otherwise the first index where p reached p[i] - 1
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C;
    cin >> C;
    while (C--) {
        int n;
        string s;
        cin >> n >> s;
        vector<int> dp(n + 1, 0);
        vector<int> first(n + 2, -1);          // first[v] = first index with p = -v, v >= 1
        int p = 0;
        for (int i = 1; i <= n; i++) {
            p += (s[i - 1] == '1') ? 1 : -1;
            if (p < 0 && first[-p] == -1) first[-p] = i;
            dp[i] = dp[i - 1];                 // day i is in no term
            int j = -1;
            if (p > 0) j = 0;
            else if (first[-p + 1] != -1 && first[-p + 1] < i) j = first[-p + 1];
            if (j >= 0) dp[i] = max(dp[i], dp[j] + (i - j));   // last term is (j, i]
        }
        cout << dp[n] << "\n";
    }
}

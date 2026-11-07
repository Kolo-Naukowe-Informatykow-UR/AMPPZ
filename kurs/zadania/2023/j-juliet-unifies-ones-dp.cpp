// AMPPZ 2023 J - Juliet Unifies Ones, O(n) dp over three states
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    const int INF = 1e9;
    // state 0: before the block of ones, 1: inside it, 2: after it
    array<int, 3> dp = {0, INF, INF};
    for (char c : s) {
        array<int, 3> nxt = {INF, INF, INF};
        for (int st = 0; st < 3; st++) {
            if (dp[st] == INF) continue;
            // remove the character: pay 1, state stays
            nxt[st] = min(nxt[st], dp[st] + 1);
            // keep the character: the state moves forward
            int to;
            if (c == '1') to = (st == 2 ? -1 : 1);  // a one after the block is forbidden
            else to = (st == 0 ? 0 : 2);            // a zero closes an open block
            if (to != -1) nxt[to] = min(nxt[to], dp[st]);
        }
        dp = nxt;
    }

    cout << min({dp[0], dp[1], dp[2]}) << "\n";
    return 0;
}

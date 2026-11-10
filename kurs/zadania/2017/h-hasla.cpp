// AMPPZ 2017 H - Hasla
// greedy: always take the smallest column that breaks no unresolved neighbour pair
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto &w : s) cin >> w;

    // bad[c] = unresolved pairs (i, i + 1) with s[i][c] > s[i + 1][c]
    vector<int> bad(m, 0);
    for (int i = 0; i + 1 < n; i++)
        for (int c = 0; c < m; c++)
            if (s[i][c] > s[i + 1][c]) bad[c]++;
    vector<char> resolved(max(n - 1, 0), 0);
    priority_queue<int, vector<int>, greater<int>> ready;   // usable columns, smallest first
    for (int c = 0; c < m; c++) if (bad[c] == 0) ready.push(c);

    vector<int> perm;
    while (!ready.empty()) {
        int c = ready.top(); ready.pop();
        perm.push_back(c);
        for (int i = 0; i + 1 < n; i++) {
            if (resolved[i] || s[i][c] >= s[i + 1][c]) continue;
            resolved[i] = 1;                   // the pair is ordered by column c for good
            for (int c2 = 0; c2 < m; c2++)
                if (s[i][c2] > s[i + 1][c2] && --bad[c2] == 0) ready.push(c2);
        }
    }
    if ((int)perm.size() < m) { puts("NIE"); return 0; }
    string out;
    for (int c : perm) out += to_string(c + 1) + ' ';
    out.back() = '\n';
    fputs(out.c_str(), stdout);
}

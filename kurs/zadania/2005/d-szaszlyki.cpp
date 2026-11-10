// AMPPZ 2005 D - Szaszlyki, O(n * p^3) per test
// state = the last two pieces, because a forbidden triple looks back two steps:
// ways[a][b] = number of good kebabs of the current length ending with a, b;
// append c when bc is allowed and abc is allowed
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    while (z--) {
        int m, n, p, k;
        cin >> m >> n >> p >> k;
        vector<vector<char>> badPair(p, vector<char>(p, 0));
        vector<char> badTriple(p * p * p, 0);
        for (int i = 0; i < k; i++) {
            string s;
            cin >> s;
            if (s.size() == 2) badPair[s[0] - 'a'][s[1] - 'a'] = 1;
            else badTriple[((s[0] - 'a') * p + (s[1] - 'a')) * p + (s[2] - 'a')] = 1;
        }
        if (n == 1) { cout << p % m << "\n"; continue; }
        vector<vector<int>> ways(p, vector<int>(p, 0)), next(p, vector<int>(p, 0));
        for (int a = 0; a < p; a++)
            for (int b = 0; b < p; b++)
                ways[a][b] = badPair[a][b] ? 0 : 1 % m;      // length 2
        for (int len = 3; len <= n; len++) {
            for (auto& row : next) fill(row.begin(), row.end(), 0);
            for (int a = 0; a < p; a++)
                for (int b = 0; b < p; b++) {
                    if (ways[a][b] == 0) continue;
                    for (int c = 0; c < p; c++)
                        if (!badPair[b][c] && !badTriple[(a * p + b) * p + c])
                            next[b][c] = (next[b][c] + ways[a][b]) % m;
                }
            swap(ways, next);
        }
        int total = 0;
        for (int a = 0; a < p; a++)
            for (int b = 0; b < p; b++) total = (total + ways[a][b]) % m;
        cout << total << "\n";
    }
}

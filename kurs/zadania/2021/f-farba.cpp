// AMPPZ 2021 F - Farba, O(n + sum of a) per test
// for height b only boards longer than b give more than one picket (at most sum/b of them);
// a run of short boards gives one picket each, so its painted part is a sum over every
// second board, read from prefix sums split by index parity
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    string out;
    while (z--) {
        int n;
        cin >> n;
        vector<int> a(n + 2, 0);
        int M = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            M = max(M, a[i]);
        }

        // par[p][i] = sum of a[j] for j < i with j % 2 == p
        vector<ll> par[2] = {vector<ll>(n + 2, 0), vector<ll>(n + 2, 0)};
        for (int i = 1; i <= n + 1; i++)
            for (int p = 0; p < 2; p++)
                par[p][i] = par[p][i - 1] + (((i - 1) % 2 == p) ? a[i - 1] : 0);
        auto parSum = [&](int p, int l, int r) {   // boards l..r with index parity p
            return l > r ? 0LL : par[p][r + 1] - par[p][l];
        };

        // linked list of long boards (a > b), sentinels 0 and n + 1
        vector<int> nxt(n + 2), prv(n + 2);
        for (int i = 0; i <= n + 1; i++) nxt[i] = i + 1, prv[i] = i - 1;
        vector<vector<int>> byLen(M + 1);
        for (int i = 1; i <= n; i++) byLen[a[i]].push_back(i);

        for (int b = 1; b <= M; b++) {
            for (int i : byLen[b]) {               // a[i] == b: from now on a short board
                nxt[prv[i]] = nxt[i];
                prv[nxt[i]] = prv[i];
            }
            ll paint = 0, cur = 1;                 // cur = number of the next picket, odd ones are white
            int last = 0;
            for (int i = nxt[0];; i = nxt[i]) {
                // short boards last+1..i-1: board j gets picket cur + (j - last - 1)
                int l = last + 1, r = i - 1;
                if (l <= r) {
                    int p = ((l + (cur % 2 == 1 ? 0 : 1)) % 2);  // parity of indices with odd pickets
                    paint += parSum(p, l, r);
                    cur += r - l + 1;
                }
                if (i == n + 1) break;
                ll full = (a[i] - 1) / b;          // pickets of length b, then one rest in [1, b]
                paint += (cur % 2 == 1 ? (full + 1) / 2 : full / 2) * b;
                if ((cur + full) % 2 == 1) paint += a[i] - full * b;
                cur += full + 1;
                last = i;
            }
            out += to_string(paint);
            out += '\n';
        }
    }
    cout << out;
    return 0;
}

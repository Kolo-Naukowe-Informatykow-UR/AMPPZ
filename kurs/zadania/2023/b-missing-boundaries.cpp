// AMPPZ 2023 B - Missing Boundaries, O(N log N) per test
// every interval with a known end occupies at least that end ([a, -1] can grow right,
// [-1, b] can grow left); sorted by that position they must not overlap; each gap of g free
// numbers takes from 0 (a neighbour can grow into it) or 1 (nobody can) up to g fully hidden
// intervals, so the answer is TAK iff the number K of [-1, -1] lies between the two sums
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long L;
        cin >> N >> L;
        // item: (left, right, kind) with kind 0 = both ends known, 1 = [a, -1], 2 = [-1, b]
        vector<array<long long, 3>> items;
        long long K = 0;
        for (int i = 0; i < N; i++) {
            long long a, b;
            cin >> a >> b;
            if (a == -1 && b == -1) K++;
            else if (b == -1) items.push_back({a, a, 1});
            else if (a == -1) items.push_back({b, b, 2});
            else items.push_back({a, b, 0});
        }
        sort(items.begin(), items.end());
        bool ok = true;
        long long lo = 0, hi = 0, cur = 1;    // cur = first number not yet covered
        int prevKind = -1;                     // -1 = left border of [1, L]
        auto gap = [&](long long g, bool canGrow) {
            if (g <= 0) return;
            hi += g;                           // at most one hidden interval per number
            if (!canGrow) lo += 1;             // somebody must cover the gap
        };
        for (auto [l, r, kind] : items) {
            if (l < cur) { ok = false; break; }    // overlaps the previous item
            gap(l - cur, prevKind == 1 || kind == 2);
            cur = r + 1;
            prevKind = kind;
        }
        if (ok) gap(L - cur + 1, prevKind == 1);
        cout << (ok && lo <= K && K <= hi ? "TAK" : "NIE") << "\n";
    }
}

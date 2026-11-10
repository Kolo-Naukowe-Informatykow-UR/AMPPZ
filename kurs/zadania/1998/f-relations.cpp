// AMPPZ 1998 F - Relations, O(n + m) per data set
// vertices joined by '=' get one number, so they become one component (bfs); a strict edge inside
// a component or a cycle of strict edges between components makes labeling impossible; otherwise
// the smallest k is the number of edges on the longest path in the dag of components
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    cin >> d;
    while (d--) {
        int n, m;
        cin >> n >> m;
        vector<int> u(m), v(m), rel(m);
        vector<vector<int>> eq(n + 1);
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i] >> rel[i];
            if (rel[i] == 0) { eq[u[i]].push_back(v[i]); eq[v[i]].push_back(u[i]); }
        }

        vector<int> comp(n + 1, -1);               // component of '=' edges
        int C = 0;
        for (int s = 1; s <= n; s++) {
            if (comp[s] != -1) continue;
            vector<int> q = {s};
            comp[s] = C;
            for (size_t h = 0; h < q.size(); h++)
                for (int w : eq[q[h]])
                    if (comp[w] == -1) { comp[w] = C; q.push_back(w); }
            C++;
        }

        vector<vector<int>> up(C);                 // edge x -> y: number of x < number of y
        vector<int> indeg(C, 0);
        bool ok = true;
        for (int i = 0; i < m; i++) {
            if (rel[i] == 0) continue;
            int lo = comp[u[i]], hi = comp[v[i]];
            if (rel[i] == 1) swap(lo, hi);         // '>' : the end is smaller
            if (lo == hi) { ok = false; break; }   // x < x
            up[lo].push_back(hi);
            indeg[hi]++;
        }

        int k = 0;
        if (ok) {
            vector<int> q, len(C, 0);              // len = edges on the longest path ending here
            for (int c = 0; c < C; c++) if (indeg[c] == 0) q.push_back(c);
            for (size_t h = 0; h < q.size(); h++) {
                int x = q[h];
                k = max(k, len[x]);
                for (int y : up[x]) {
                    len[y] = max(len[y], len[x] + 1);
                    if (--indeg[y] == 0) q.push_back(y);
                }
            }
            if ((int)q.size() < C) ok = false;     // a cycle of strict edges
        }
        if (ok) cout << k << "\n";
        else cout << "NO\n";
    }
    return 0;
}

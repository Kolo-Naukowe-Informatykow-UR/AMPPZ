// AMPPZ 2015 B - Bogacze, O(n + m)
// vertices are the 2n literals x_i and -x_i; s_i x_i + s_j x_j > 0 means s_i x_i > -s_j x_j and
// s_j x_j > -s_i x_i, an edge from the smaller literal to the larger one for each; the system has
// a solution iff this graph has no cycle (kahn's algorithm removes every vertex)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int V = 2 * n;                                 // literal +x_i is 2i, -x_i is 2i + 1, negation is ^1
    vector<int> from(2 * m), to(2 * m);
    for (int e = 0; e < m; e++) {
        char si, sj;
        int i, j;
        cin >> si >> i >> sj >> j;
        int li = 2 * (i - 1) + (si == '-'), lj = 2 * (j - 1) + (sj == '-');
        from[2 * e] = lj ^ 1; to[2 * e] = li;      // -lj < li
        from[2 * e + 1] = li ^ 1; to[2 * e + 1] = lj;  // -li < lj
    }

    // adjacency lists in one array (counting sort by source)
    vector<int> start(V + 1, 0), adj(2 * m), indeg(V, 0);
    for (int e = 0; e < 2 * m; e++) { start[from[e] + 1]++; indeg[to[e]]++; }
    for (int v = 0; v < V; v++) start[v + 1] += start[v];
    vector<int> pos(start.begin(), start.end() - 1);
    for (int e = 0; e < 2 * m; e++) adj[pos[from[e]]++] = to[e];

    vector<int> q;                                 // vertices with no incoming edge left
    q.reserve(V);
    for (int v = 0; v < V; v++) if (indeg[v] == 0) q.push_back(v);
    for (size_t head = 0; head < q.size(); head++) {
        int v = q[head];
        for (int p = start[v]; p < start[v + 1]; p++)
            if (--indeg[adj[p]] == 0) q.push_back(adj[p]);
    }
    cout << ((int)q.size() == V ? "TAK" : "NIE") << "\n";   // a cycle keeps its vertices out
    return 0;
}

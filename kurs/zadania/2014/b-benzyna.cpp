// AMPPZ 2014 B - Benzyna, O((n + m) log n + q log q)
// d[v] = distance from v to the nearest station (dijkstra from all stations at once);
// a truck with tank b can use road (u, v) iff d[u] + len + d[v] <= b, and two stations are
// reachable iff such roads connect them; offline: queries sorted by b, roads by that weight,
// roads joined in find-union in this order (as in kruskal's algorithm)
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int v) {
        int r = v;
        while (p[r] != r) r = p[r];
        while (p[v] != r) { int nx = p[v]; p[v] = r; v = nx; }   // path compression
        return r;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);         // union by size
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s, m;
    cin >> n >> s >> m;
    vector<long long> d(n + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    for (int i = 0; i < s; i++) {
        int c;
        cin >> c;
        d[c] = 0;                              // every station is a source
        pq.push({0, c});
    }
    vector<array<int, 3>> roads(m);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& [u, v, len] : roads) {
        cin >> u >> v >> len;
        adj[u].push_back({v, len});
        adj[v].push_back({u, len});
    }
    while (!pq.empty()) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (dv != d[v]) continue;
        for (auto [w, len] : adj[v])
            if (dv + len < d[w]) {
                d[w] = dv + len;
                pq.push({d[w], w});
            }
    }

    // roads that touch an unreachable vertex never help
    vector<pair<long long, int>> byWeight;
    for (int i = 0; i < m; i++) {
        auto [u, v, len] = roads[i];
        if (d[u] == LLONG_MAX || d[v] == LLONG_MAX) continue;
        byWeight.push_back({d[u] + len + d[v], i});
    }
    sort(byWeight.begin(), byWeight.end());

    int q;
    cin >> q;
    vector<array<long long, 3>> qs(q);         // b, x, y
    for (auto& [b, x, y] : qs) cin >> x >> y >> b;
    vector<int> qord(q);
    iota(qord.begin(), qord.end(), 0);
    sort(qord.begin(), qord.end(), [&](int a, int b) { return qs[a][0] < qs[b][0]; });

    DSU dsu(n + 1);
    vector<char> ans(q);
    size_t e = 0;
    for (int i : qord) {
        auto [b, x, y] = qs[i];
        while (e < byWeight.size() && byWeight[e].first <= b) {   // roads usable with tank b
            auto [u, v, len] = roads[byWeight[e].second];
            dsu.unite(u, v);
            e++;
        }
        ans[i] = dsu.find(x) == dsu.find(y);
    }
    for (int i = 0; i < q; i++) cout << (ans[i] ? "TAK\n" : "NIE\n");
}

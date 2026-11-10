// AMPPZ 2004 I - Obóz Babilon, O((n + m) log n) per test
// waiting in a base is allowed, so reaching a base earlier is never worse (leaving later
// never arrives earlier); dijkstra on arrival times, where a road is taken at the first
// safe moment not earlier than the arrival
#include <bits/stdc++.h>
using namespace std;

struct Road { int to, w, t, a, l; };

// first moment >= T at which leaving by road r is safe
long long depart(long long T, const Road& r) {
    if (r.t == 0) return T;                    // t = a = l = 0: always safe
    long long k = ((T - r.a) % r.t + r.t) % r.t;   // position of T inside the period
    if (k < r.l) return T;                     // inside [it + a, it + a + l)
    return T + (r.t - k);                      // start of the next window
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    cin >> d;
    while (d--) {
        int n, m;
        cin >> n >> m;
        vector<vector<Road>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u;
            Road r;
            cin >> u >> r.to >> r.w >> r.t >> r.a >> r.l;
            adj[u].push_back(r);
        }
        vector<long long> dist(n + 1, LLONG_MAX);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        dist[1] = 0;
        pq.push({0, 1});
        while (!pq.empty()) {
            auto [T, v] = pq.top();
            pq.pop();
            if (T != dist[v]) continue;        // stale entry
            for (const Road& r : adj[v]) {
                long long arr = depart(T, r) + r.w;
                if (arr < dist[r.to]) {
                    dist[r.to] = arr;
                    pq.push({arr, r.to});
                }
            }
        }
        if (dist[n] == LLONG_MAX) cout << "NIE\n";
        else cout << dist[n] << "\n";
    }
}

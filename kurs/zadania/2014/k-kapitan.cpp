// AMPPZ 2014 K - Kapitan, O(n log n)
// on a leg between two islands the captain steers one axis only, so a direct leg costs
// min(|dx|, |dy|); a leg that costs |dx| can stop at every island between the two in x order
// without paying more, so legs to the neighbours in x order and in y order are enough;
// on this graph with at most 4n edges dijkstra gives the answer
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    auto cost = [&](int a, int b) { return min(llabs(x[a] - x[b]), llabs(y[a] - y[b])); };
    vector<vector<pair<int, long long>>> adj(n);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    for (int axis = 0; axis < 2; axis++) {
        const vector<long long>& c = (axis == 0 ? x : y);
        sort(ord.begin(), ord.end(), [&](int a, int b) { return c[a] < c[b]; });
        for (int k = 0; k + 1 < n; k++) {      // neighbours in this order
            int a = ord[k], b = ord[k + 1];
            adj[a].push_back({b, cost(a, b)});
            adj[b].push_back({a, cost(a, b)});
        }
    }

    // dijkstra from island 1 (index 0)
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;            // stale entry, v was improved later
        for (auto [w, c] : adj[v])
            if (d + c < dist[w]) {
                dist[w] = d + c;
                pq.push({dist[w], w});
            }
    }
    cout << dist[n - 1] << "\n";
}

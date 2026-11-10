// AMPPZ 2012 H - Hydra, O(n log n + R), R = sum of r_i
// cost[i] = min(z_i, u_i + sum of cost[j] over the heads j that grow back after a cut);
// dijkstra-like order: the unfinished head with the smallest known value is final, because
// any cut that needs an unfinished head costs more (u_i >= 1); a head gets its cut value
// once every head on its list is final
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> u(n), best(n);
    vector<int> need(n), owner, item;          // occurrence k: head owner[k] regrows head item[k]
    for (int i = 0; i < n; i++) {
        long long z;
        int r;
        cin >> u[i] >> z >> r;
        best[i] = z;                           // massacre is always possible
        need[i] = r;
        for (int k = 0; k < r; k++) {
            int g;
            cin >> g;
            owner.push_back(i);
            item.push_back(g - 1);
        }
    }

    // reverse lists in one array: for head j, the heads whose list contains j (with repeats)
    int R = item.size();
    vector<int> start(n + 1, 0), rev(R);
    for (int k = 0; k < R; k++) start[item[k] + 1]++;
    for (int j = 0; j < n; j++) start[j + 1] += start[j];
    vector<int> pos(start.begin(), start.end() - 1);
    for (int k = 0; k < R; k++) rev[pos[item[k]]++] = owner[k];

    vector<long long> sum(n, 0);
    vector<char> done(n, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    for (int i = 0; i < n; i++) pq.push({best[i], i});
    while (!pq.empty()) {
        auto [c, j] = pq.top();
        pq.pop();
        if (done[j] || c != best[j]) continue; // stale entry
        done[j] = 1;                           // cost[j] = best[j] is final
        for (int p = start[j]; p < start[j + 1]; p++) {
            int i = rev[p];
            if (done[i]) continue;             // also skips j growing back on itself
            sum[i] += best[j];
            if (--need[i] == 0 && u[i] + sum[i] < best[i]) {
                best[i] = u[i] + sum[i];       // the cut option is known now
                pq.push({best[i], i});
            }
        }
    }
    cout << best[0] << "\n";
}

// AMPPZ 2005 G - Skarb, O(w k) per map
// bfs from the treasure gives every cell its distance to the treasure; walking from the start,
// the smallest letter (D < G < L < P) that leads to a cell one step closer builds the answer
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    // moves in alphabetical order of their letters: down, up, left, right
    const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, -1, 1};
    const char letter[4] = {'D', 'G', 'L', 'P'};
    while (z--) {
        int w, k;
        cin >> w >> k;
        vector<string> g(w);
        for (auto& row : g) cin >> row;
        int start = -1, goal = -1;
        for (int r = 0; r < w; r++)
            for (int c = 0; c < k; c++) {
                if (g[r][c] == 'S') start = r * k + c;
                if (g[r][c] == '*') goal = r * k + c;
            }

        vector<int> dist(w * k, -1);               // distance to the treasure, -1 = unreachable
        vector<int> q;                             // bfs queue as a plain array
        q.reserve(w * k);
        dist[goal] = 0;
        q.push_back(goal);
        for (size_t head = 0; head < q.size(); head++) {
            int r = q[head] / k, c = q[head] % k;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= w || nc < 0 || nc >= k || g[nr][nc] == 'X') continue;
                if (dist[nr * k + nc] != -1) continue;
                dist[nr * k + nc] = dist[q[head]] + 1;
                q.push_back(nr * k + nc);
            }
        }

        if (dist[start] == -1) { cout << "BRAK\n"; continue; }
        string path;
        int cur = start;
        while (cur != goal) {                      // every step goes one closer to the treasure
            int r = cur / k, c = cur % k;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= w || nc < 0 || nc >= k) continue;
                if (dist[nr * k + nc] == dist[cur] - 1) {  // walls have -1, never equal
                    path += letter[d];
                    cur = nr * k + nc;
                    break;
                }
            }
        }
        cout << path << "\n";
    }
    return 0;
}

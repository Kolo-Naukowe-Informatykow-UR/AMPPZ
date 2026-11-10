// AMPPZ 1996 C - Shapes, O(M N)
// flood fill (bfs) over the 8 neighbours of the same letter counts the shapes of every colour;
// two different letters touching in any of the 8 directions make the colours neighbours
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cols, rows;
    cin >> cols >> rows;
    vector<string> g(rows);
    for (auto& row : g) cin >> row;

    vector<char> seen(rows * cols, 0);
    long long shapes[26] = {};
    int neighbours[26] = {};                       // bit d set: colour 'A' + d touches this colour
    vector<int> q;
    for (int r0 = 0; r0 < rows; r0++)
        for (int c0 = 0; c0 < cols; c0++) {
            char ch = g[r0][c0];
            if (ch == '.' || seen[r0 * cols + c0]) continue;
            shapes[ch - 'A']++;                    // a new shape: fill all of it
            q.assign(1, r0 * cols + c0);
            seen[r0 * cols + c0] = 1;
            for (size_t head = 0; head < q.size(); head++) {
                int r = q[head] / cols, c = q[head] % cols;
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                        char other = g[nr][nc];
                        if (other == '.') continue;
                        if (other != ch) { neighbours[ch - 'A'] |= 1 << (other - 'A'); continue; }
                        if (!seen[nr * cols + nc]) { seen[nr * cols + nc] = 1; q.push_back(nr * cols + nc); }
                    }
            }
        }

    cout << "Results :\n---------\n";
    for (int d = 0; d < 26; d++) {
        if (shapes[d] == 0) continue;
        cout << "Color " << char('A' + d) << " - " << shapes[d] << "\tNeighbours:";
        for (int e = 0; e < 26; e++) if (neighbours[d] >> e & 1) cout << ' ' << char('A' + e);
        cout << "\n";
    }
    return 0;
}

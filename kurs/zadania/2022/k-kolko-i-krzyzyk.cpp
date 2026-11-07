// AMPPZ 2022 K - Kółko i Krzyżyk, O(n^2 * k) per board
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<string> g;

// directions: right, down, down-right, down-left
const int dr[4] = {0, 1, 1, 1};
const int dc[4] = {1, 0, 1, -1};

// all segments of k equal symbols s, each as a list of cells
vector<vector<pair<int, int>>> segments(char s) {
    vector<vector<pair<int, int>>> res;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            for (int d = 0; d < 4; d++) {
                int er = r + dr[d] * (k - 1), ec = c + dc[d] * (k - 1);
                if (er < 0 || er >= n || ec < 0 || ec >= n) continue;
                vector<pair<int, int>> seg;
                for (int i = 0; i < k; i++) seg.push_back({r + dr[d] * i, c + dc[d] * i});
                bool all = true;
                for (auto [x, y] : seg) all = all && g[x][y] == s;
                if (all) res.push_back(seg);
            }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        cin >> n >> k;
        g.assign(n, "");
        for (auto& row : g) cin >> row;

        vector<pair<int, int>> cells[2];                    // 0: x, 1: o
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                if (g[r][c] == 'x') cells[0].push_back({r, c});
                if (g[r][c] == 'o') cells[1].push_back({r, c});
            }
        int cx = cells[0].size(), co = cells[1].size();
        auto segX = segments('x'), segO = segments('o');

        // first: player who moves first, last: the cell of the final move (or none for a draw)
        int first = -1;
        pair<int, int> lastCell = {-1, -1};
        int winner = segX.empty() ? (segO.empty() ? -1 : 1) : (segO.empty() ? 0 : 2);

        if (abs(cx - co) <= 1 && winner != 2) {
            if (winner == -1) {
                // draw: the board must be full, any order is fine
                if (cx + co == n * n) first = cx >= co ? 0 : 1;
            } else {
                int w = winner, l = 1 - winner;
                auto& seg = (w == 0) ? segX : segO;
                // the winner made the last move, so he has at least as many symbols
                if ((int)cells[w].size() >= (int)cells[l].size()) {
                    // the last cell must lie on every winning segment
                    map<pair<int, int>, int> onSeg;
                    for (auto& s : seg)
                        for (auto p : s) onSeg[p]++;
                    for (auto [p, cnt] : onSeg)
                        if (cnt == (int)seg.size()) lastCell = p;
                    if (lastCell.first != -1) first = cells[w].size() > cells[l].size() ? w : l;
                }
            }
        }

        if (first == -1) {
            cout << "NIE\n";
            continue;
        }
        cout << "TAK\n";
        // put the last cell at the end of its player's list, then alternate
        if (lastCell.first != -1) {
            auto& v = cells[winner];
            v.erase(find(v.begin(), v.end(), lastCell));
            v.push_back(lastCell);
        }
        size_t i[2] = {0, 0};
        for (int p = first; i[p] < cells[p].size(); p = 1 - p) {
            cout << cells[p][i[p]].first + 1 << " " << cells[p][i[p]].second + 1 << "\n";
            i[p]++;
        }
    }
    return 0;
}

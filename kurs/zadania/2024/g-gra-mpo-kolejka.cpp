// AMPPZ 2024 G - Gra MPO, closure with a queue, O(n^2)
// gains never drop, so the final board does not depend on the order of moves
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> board;

const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inside(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

char partner(char s) {
    if (s == 'M') return 'P';
    if (s == 'P') return 'M';
    return 'O';
}

bool isBuilt(char s) { return s == 'M' || s == 'P' || s == 'O'; }
bool isFree(char s) { return s == 'm' || s == 'p' || s == 'o'; }

// free cell with at least one built partner around: the move gives 2 or more points
bool allowed(int r, int c) {
    if (!isFree(board[r][c])) return false;
    char want = partner(toupper(board[r][c]));
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inside(nr, nc) && board[nr][nc] == want) return true;
    }
    return false;
}

int score() {
    int pts = 0, oceanEnds = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            if (!isBuilt(board[r][c])) continue;
            pts++;
            for (int d = 0; d < 8; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (!inside(nr, nc)) continue;
                if (board[r][c] == 'M' && board[nr][nc] == 'P') pts++;
                if (board[r][c] == 'O' && board[nr][nc] == 'O') oceanEnds++;
            }
        }
    return pts + oceanEnds / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    board.resize(n);
    for (auto& row : board) cin >> row;

    int start = score();

    // every built cell may unlock its neighbours, each cell is built at most once
    queue<pair<int, int>> q;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (allowed(r, c)) {
                board[r][c] = toupper(board[r][c]);
                q.push({r, c});
            }
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (inside(nr, nc) && allowed(nr, nc)) {
                board[nr][nc] = toupper(board[nr][nc]);
                q.push({nr, nc});
            }
        }
    }

    cout << start << " " << score() << "\n";
    for (const auto& row : board) cout << row << "\n";
    return 0;
}

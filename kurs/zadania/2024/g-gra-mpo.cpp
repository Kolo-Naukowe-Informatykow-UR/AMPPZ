// AMPPZ 2024 G - Gra MPO, direct simulation, O(n^4) for n <= 10
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> board;

// 8 neighbours: side or corner
const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inside(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

// structure that pairs with s: M with P, P with M, O with O
char partner(char s) {
    if (s == 'M') return 'P';
    if (s == 'P') return 'M';
    return 'O';
}

// built neighbours of (r, c) that pair with structure s
int pairsAround(int r, int c, char s) {
    int cnt = 0;
    for (int d = 0; d < 8; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (inside(nr, nc) && board[nr][nc] == partner(s)) cnt++;
    }
    return cnt;
}

int score() {
    int pts = 0, oceanEnds = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            char s = board[r][c];
            if (s != 'M' && s != 'P' && s != 'O') continue;
            pts++;                                         // the structure itself
            if (s == 'M') pts += pairsAround(r, c, 'M');   // each city-park pair once, from the city
            if (s == 'O') oceanEnds += pairsAround(r, c, 'O');
        }
    return pts + oceanEnds / 2;                            // each ocean pair was seen from both ends
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    board.resize(n);
    for (auto& row : board) cin >> row;

    int start = score(), total = start;
    while (true) {
        // find the move with the largest gain
        int bestGain = 0, br = -1, bc = -1;
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                char s = board[r][c];
                if (s != 'm' && s != 'p' && s != 'o') continue;
                int gain = 1 + pairsAround(r, c, toupper(s));
                if (gain > bestGain) bestGain = gain, br = r, bc = c;
            }
        if (bestGain < 2) break;                           // only +1 moves left, they are forbidden
        board[br][bc] = toupper(board[br][bc]);
        total += bestGain;
    }

    cout << start << " " << total << "\n";
    for (const auto& row : board) cout << row << "\n";
    return 0;
}

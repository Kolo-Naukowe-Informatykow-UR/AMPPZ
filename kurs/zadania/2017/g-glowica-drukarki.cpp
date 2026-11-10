// AMPPZ 2017 G - Głowica drukarki, O(n)
// one pass prints heights h, h-1, ... at positions that go one way, so walk the heights
// from n down and cut the list of positions into the fewest monotone runs, each as long as possible
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        pos[h] = i;
    }

    int passes = 1, dir = 0;                       // dir of the current run: 0 unknown, +1 right, -1 left
    for (int h = n - 1; h >= 1; h--) {
        int d = pos[h] > pos[h + 1] ? 1 : -1;
        if (dir == 0) dir = d;                     // second height fixes the direction
        else if (d != dir) passes++, dir = 0;      // h starts a new pass
    }
    cout << passes << "\n";
    return 0;
}

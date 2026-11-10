// AMPPZ 2012 I - Inwersje, O(n)
// a component ends at position i exactly when the prefix maximum equals i,
// so components are blocks of positions holding consecutive values
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> blocks;                 // [first, last] value of each component
    int mx = 0, start = 1;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx = max(mx, x);
        if (mx == i) {                             // prefix holds exactly 1..i
            blocks.push_back({start, i});
            start = i + 1;
        }
    }

    // up to 2 * 10^6 numbers: build the output in one string
    string out = to_string(blocks.size()) + "\n";
    out.reserve(8 * n + 16);
    for (auto [l, r] : blocks) {
        out += to_string(r - l + 1);
        for (int v = l; v <= r; v++) {
            out += ' ';
            out += to_string(v);
        }
        out += '\n';
    }
    cout << out;
    return 0;
}

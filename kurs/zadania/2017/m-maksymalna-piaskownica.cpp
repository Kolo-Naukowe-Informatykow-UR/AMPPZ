// AMPPZ 2017 M - Maksymalna piaskownica, O(n + 100)
// count boards of each length; take the two longest pairs (a length used 4 times gives two pairs)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> cnt(101, 0);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    vector<int> sides;                             // pair lengths, longest first
    for (int len = 100; len >= 1 && sides.size() < 2; len--)
        for (int p = 0; p < cnt[len] / 2 && sides.size() < 2; p++) sides.push_back(len);

    if (sides.size() < 2) cout << "NIE\n";
    else cout << sides[0] * sides[1] << "\n";
    return 0;
}

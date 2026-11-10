// AMPPZ 1998 B - Cross-country, O(|A| * |T|) per card of Tom
// meetings form a common subsequence of the two cards, so the answer is the longest common
// subsequence (lcs) of Agnes' card and Tom's card, maximised over Tom's cards;
// a route is read up to its 0, and an empty route (a lone 0) ends the data set
#include <bits/stdc++.h>
using namespace std;

vector<int> readRoute() {
    vector<int> r;
    int x;
    while (cin >> x && x != 0) r.push_back(x);
    return r;
}

int lcs(const vector<int>& a, const vector<int>& b) {
    vector<int> prev(b.size() + 1, 0), cur(b.size() + 1, 0);   // rows i - 1 and i of the table
    for (size_t i = 1; i <= a.size(); i++) {
        for (size_t j = 1; j <= b.size(); j++)
            cur[j] = (a[i - 1] == b[j - 1]) ? prev[j - 1] + 1 : max(prev[j], cur[j - 1]);
        swap(prev, cur);
    }
    return prev[b.size()];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    cin >> d;
    while (d--) {
        vector<int> agnes = readRoute();
        int best = 0;
        while (true) {
            vector<int> tom = readRoute();
            if (tom.empty()) break;            // 0 at the start of a line: end of the data set
            best = max(best, lcs(agnes, tom));
        }
        cout << best << "\n";
    }
}

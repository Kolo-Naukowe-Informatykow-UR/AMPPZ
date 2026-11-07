// AMPPZ 2024 A - Akronim, O(n * L), L <= 8
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n);
    for (auto& w : words) cin >> w;

    // for every letter remember one word that starts with it
    vector<string> starts(26, "");
    for (const auto& w : words)
        if (starts[w[0] - 'A'].empty()) starts[w[0] - 'A'] = w;

    // a word works as the acronym when every letter of it starts some word
    for (const auto& acronym : words) {
        bool ok = true;
        for (char c : acronym)
            if (starts[c - 'A'].empty()) {
                ok = false;
                break;
            }
        if (!ok) continue;

        cout << acronym.size() << "\n";
        for (size_t i = 0; i < acronym.size(); i++)
            cout << starts[acronym[i] - 'A'] << (i + 1 < acronym.size() ? ' ' : '\n');
        return 0;
    }

    cout << -1 << "\n";
    return 0;
}

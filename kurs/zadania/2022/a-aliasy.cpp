// AMPPZ 2022 A - Aliasy, O(28 * n log n) per data set
// a = b = 0, c = 6 always works (10^6 > 200000 people), so the answer has a + b + c <= 6
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<string> first(n), last(n);
        for (int i = 0; i < n; i++) cin >> first[i] >> last[i];

        int bestSum = INT_MAX, ba = 0, bb = 0, bc = 0;
        vector<ll> keys(n);
        for (int a = 0; a <= 6; a++)
            for (int b = 0; a + b <= 6; b++) {
                // the letter part of the alias as a number in base 27 (letters are digits 1..26)
                for (int i = 0; i < n; i++) {
                    ll key = 0;
                    for (int j = 0; j < a && j < (int)first[i].size(); j++) key = key * 27 + (first[i][j] - 'a' + 1);
                    for (int j = 0; j < b && j < (int)last[i].size(); j++) key = key * 27 + (last[i][j] - 'a' + 1);
                    keys[i] = key;
                }
                // largest group of people with the same letter part
                sort(keys.begin(), keys.end());
                int largest = 0;
                for (int i = 0, j = 0; i < n; i = j) {
                    while (j < n && keys[j] == keys[i]) j++;
                    largest = max(largest, j - i);
                }
                // c digits give 10^c different endings; the alias must not be empty
                int c = 0;
                ll endings = 1;
                while (endings < largest) endings *= 10, c++;
                if (a + b == 0) c = max(c, 1);
                if (a + b + c < bestSum) bestSum = a + b + c, ba = a, bb = b, bc = c;
            }
        cout << ba << " " << bb << " " << bc << "\n";
    }
    return 0;
}

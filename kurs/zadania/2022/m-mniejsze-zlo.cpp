// AMPPZ 2022 M - Mniejsze zło, O(n + k) per test
// people who are not enemies never need to die, so they are always alive; an enemy killed on day i
// can still be a killer on every earlier day, so going from the last day back, kill each enemy on
// the latest day whose killer is alive "from then on" (a non-enemy or an enemy killed later)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(k), b(k);
        for (int i = 0; i < k; i++) cin >> a[i] >> b[i];
        int s;
        cin >> s;
        vector<char> enemy(n + 1, 0), killed(n + 1, 0), alive(n + 1, 1);
        for (int j = 0; j < s; j++) { int v; cin >> v; enemy[v] = 1; alive[v] = 0; }
        // alive[v]: v is still alive on the day being processed (going backwards)
        string plan(k, 'N');
        int left = s;
        for (int i = k - 1; i >= 0; i--) {
            if (enemy[b[i]] && !killed[b[i]] && alive[a[i]]) {
                plan[i] = 'T';                     // the latest possible day for b[i]
                killed[b[i]] = 1;
                alive[b[i]] = 1;                   // before day i b[i] is alive and can kill
                left--;
            }
        }
        if (left == 0) cout << "TAK\n" << plan << "\n";
        else cout << "NIE\n";
    }
    return 0;
}

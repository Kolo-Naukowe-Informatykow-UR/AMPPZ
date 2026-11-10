// AMPPZ 2011 H - Herbata z mlekiem, O(n)
// the last refill is never drunk; with h tea and m milk refills before it, tea drunk is
// (h + 1) / 2 minus the tea left at the end (less than 1/2), the same for milk; on a tie the
// refill before the last one (1/4 of the cup at the end) decides
#include <bits/stdc++.h>
using namespace std;

string solve(const string& s) {
    int n = s.size();
    if (n == 1) return "HM";                       // drank 1/4 of each
    int h = 0, m = 0;
    for (int i = 0; i + 1 < n; i++) (s[i] == 'H' ? h : m)++;
    if (h != m) return h > m ? "H" : "M";
    return s[n - 2] == 'H' ? "M" : "H";            // more tea left in the cup, so less drunk
}

int main() {
    int n;
    string s;
    cin >> n >> s;
    cout << solve(s) << "\n";
    return 0;
}

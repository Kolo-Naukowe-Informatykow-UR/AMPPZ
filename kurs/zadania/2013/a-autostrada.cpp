// AMPPZ 2013 A - Autostrada
// entry j needs b0 + (j-1)l <= a[j] <= b0 + jl; eliminate b0: lower bounds and upper bounds on l
// each bound family is monotone in l, so two binary searches on reals
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

int n;
vector<ld> a;                                  // shifted so that a[1] = 0, 1-indexed

// l is at least the smallest spacing: a[j] - j*l <= a[i] - (i-1)*l for all i <= j
bool bigEnough(ld l) {
    ld best = 1e30;                            // min over i <= j of a[i] - (i-1)*l
    for (int j = 1; j <= n; j++) {
        best = min(best, a[j] - (j - 1) * l);
        if (a[j] - j * l > best) return false;
    }
    return true;
}

// l is at most the largest spacing: a[j] - j*l <= a[i] - (i-1)*l for all j <= i - 2
bool smallEnough(ld l) {
    ld best = -1e30;                           // max over j <= i - 2 of a[j] - j*l
    for (int i = 3; i <= n; i++) {
        best = max(best, a[i - 2] - (i - 2) * l);
        if (best > a[i] - (i - 1) * l) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.assign(n + 1, 0);
    long long first = 0;
    for (int i = 1; i <= n; i++) {
        long long v; cin >> v;
        if (i == 1) first = v;
        a[i] = v - first;                      // smaller numbers, smaller rounding errors
    }
    ld lo = 0, hi = 1e9;                       // smallest spacing: bigEnough(hi) holds
    for (int it = 0; it < 100; it++) {
        ld mid = (lo + hi) / 2;
        if (bigEnough(mid)) hi = mid; else lo = mid;
    }
    ld lmin = hi;
    lo = 0, hi = 1e9 + 1;                      // largest spacing: smallEnough(lo) holds
    for (int it = 0; it < 100; it++) {
        ld mid = (lo + hi) / 2;
        if (smallEnough(mid)) lo = mid; else hi = mid;
    }
    printf("%.12f %.12f\n", (double)lmin, (double)lo);   // %Lf is unreliable on mingw
}

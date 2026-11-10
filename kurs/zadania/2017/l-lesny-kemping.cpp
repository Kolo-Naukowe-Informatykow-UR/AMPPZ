// AMPPZ 2017 L - Lesny kemping
// binary search on the answer d; check: greedy jumps on the path, cut the circle at the first chosen house
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<ll> p;                                  // p[i] = position of house i on the circle, p[0] = 0
vector<int> nxt, cnt, last;
ll C;                                          // circumference

// can we choose k houses with every gap along the circle at least d?
bool good(ll d) {
    // nxt[i] = first house j > i with p[j] - p[i] >= d, or n if none (two pointers)
    for (int i = 0, j = 0; i < n; i++) {
        if (j < i + 1) j = i + 1;
        while (j < n && p[j] - p[i] < d) j++;
        nxt[i] = j;
    }
    // cnt[i] = greedy jumps from i on the path, last[i] = house where they stop
    for (int i = n - 1; i >= 0; i--) {
        if (nxt[i] == n) { cnt[i] = 0; last[i] = i; }
        else { cnt[i] = cnt[nxt[i]] + 1; last[i] = last[nxt[i]]; }
    }
    // s = chosen house with the smallest number; the others lie after it on the path
    for (int s = 0; s < n; s++) {
        if (cnt[s] >= k) return true;          // the k-th jump proves the closing gap is at least d
        if (cnt[s] == k - 1 && C - (p[last[s]] - p[s]) >= d) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    p.assign(n, 0);
    for (int i = 1; i < n; i++) p[i] = p[i - 1] + a[i - 1];
    C = p[n - 1] + a[n - 1];
    nxt.resize(n); cnt.resize(n); last.resize(n);
    ll lo = 1, hi = C / k + 1;                 // good(lo) holds, good(hi) fails
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        if (good(mid)) lo = mid; else hi = mid;
    }
    printf("%lld\n", lo);
}

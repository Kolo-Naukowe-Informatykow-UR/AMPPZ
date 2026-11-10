// AMPPZ 2013 I - Inzynieria genetyczna, O(n + V), V = largest value
// best[i] = most blocks from the suffix i..n-1; a block of value g[i] that starts at i ends
// at the earliest possible place: e(i) = k-th occurrence of g[i] counting from i;
// best[i] = max(best[i + 1], 1 + best[e(i) + 1]); then rebuild greedily: from position p with
// R blocks still needed, the block may end anywhere up to lim = last index with
// best[lim + 1] >= R - 1; take the smallest value with k occurrences in [p, lim] and end its
// block at its k-th occurrence from p; every position lies in at most two pieces [p, lim]
#include <bits/stdc++.h>
using namespace std;

static char buf[1 << 25];
int bufLen = 0, bufPos = 0;
int readInt() {
    while (bufPos < bufLen && (buf[bufPos] < '0' || buf[bufPos] > '9')) bufPos++;
    int x = 0;
    while (bufPos < bufLen && buf[bufPos] >= '0' && buf[bufPos] <= '9') x = x * 10 + (buf[bufPos++] - '0');
    return x;
}

int main() {
    bufLen = fread(buf, 1, sizeof(buf), stdin);
    int n = readInt(), k = readInt();
    const int V = 1000001;
    vector<int> g(n), cnt(V + 1, 0);
    for (int i = 0; i < n; i++) { g[i] = readInt(); cnt[g[i] + 1]++; }

    // occurrences of every value in one array, in order of position; rk[i] = rank of i among them
    vector<int> start(cnt), pos(n), rk(n);
    for (int v = 0; v < V; v++) start[v + 1] += start[v];
    vector<int> fill(start.begin(), start.end() - 1);
    for (int i = 0; i < n; i++) { rk[i] = fill[g[i]] - start[g[i]]; pos[fill[g[i]]++] = i; }

    vector<int> best(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        best[i] = best[i + 1];                 // g[i] is dropped
        int v = g[i], idx = start[v] + rk[i] + k - 1;
        if (idx < start[v + 1])                // or a block of v starts at i and ends at pos[idx]
            best[i] = max(best[i], 1 + best[pos[idx] + 1]);
    }

    int B = best[0];
    string out = to_string((long long)B * k) + "\n";
    vector<int> inPiece(V, 0);
    int p = 0, lim = -1;
    for (int R = B; R >= 1; R--) {
        while (lim + 1 < n && best[lim + 2] >= R - 1) lim++;   // lim only moves right
        int v = INT_MAX;
        for (int j = p; j <= lim; j++)
            if (++inPiece[g[j]] == k) v = min(v, g[j]);         // smallest value that fits
        for (int j = p; j <= lim; j++) inPiece[g[j]] = 0;       // clear by a second pass
        int q = p, seen = 0;
        while (!(g[q] == v && ++seen == k)) q++;               // k-th occurrence of v from p
        for (int t = 0; t < k; t++) out += to_string(v), out += (R == 1 && t == k - 1) ? "" : " ";
        p = q + 1;
    }
    out += "\n";
    fwrite(out.data(), 1, out.size(), stdout);
}

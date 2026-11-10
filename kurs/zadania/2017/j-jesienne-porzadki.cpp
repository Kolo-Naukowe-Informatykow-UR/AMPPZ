// AMPPZ 2017 J - Jesienne porzadki, O(n + r^2 * k^2), memory O(r * k)
// only price mod r matters, so count the items of every residue class; within a class the
// items are interchangeable: taking x of the c items of class j gives C(c, x) ways and adds
// x * j to the sum mod r; knapsack over the classes: ways[t][s] = ways to take t items with
// sum = s (mod r); the answer is ways[k][0]; C(c, x) mod 10^6 + 3 is safe since c < 10^6 + 3
#include <bits/stdc++.h>
using namespace std;

const long long P = 1000003;

static char buf[1 << 16];
int bufLen = 0, bufPos = 0;
int readChar() {
    if (bufPos == bufLen) { bufLen = fread(buf, 1, sizeof(buf), stdin); bufPos = 0; if (bufLen <= 0) return -1; }
    return buf[bufPos++];
}
int readInt() {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = readChar(); }
    return x;
}

long long power(long long a, long long e) {
    long long r = 1;
    a %= P;
    for (; e > 0; e >>= 1, a = a * a % P)
        if (e & 1) r = r * a % P;
    return r;
}

int main() {
    int n = readInt(), k = readInt(), r = readInt();
    vector<long long> cnt(r, 0);               // prices are never stored: 16 mb limit
    for (int i = 0; i < n; i++) cnt[readInt() % r]++;

    vector<long long> inv(k + 1, 1);
    for (int x = 1; x <= k; x++) inv[x] = power(x, P - 2);

    vector<unsigned long long> ways((k + 1) * r, 0), next((k + 1) * r, 0), b(k + 1);
    ways[0] = 1;                               // nothing taken, sum 0
    for (int j = 0; j < r; j++) {
        long long c = cnt[j];
        if (c == 0) continue;
        int top = (int)min<long long>(c, k);
        b[0] = 1;                              // b[x] = C(c, x) mod P
        for (int x = 1; x <= top; x++) b[x] = b[x - 1] * ((c - x + 1) % P) % P * inv[x] % P;
        for (int t = 0; t <= k; t++) {
            unsigned long long acc[10] = {0};  // sums below 3001 * P^2 < 2^64, reduce once
            int sh = 0;
            for (int x = 0; x <= min(t, top); x++) {
                const unsigned long long* row = &ways[(t - x) * r];
                unsigned long long bx = b[x];
                for (int s = 0; s < r; s++) {
                    int to = s + sh < r ? s + sh : s + sh - r;
                    acc[to] += bx * row[s];
                }
                sh += j; if (sh >= r) sh -= r;  // shift = x * j mod r
            }
            for (int s = 0; s < r; s++) next[t * r + s] = acc[s] % P;
        }
        swap(ways, next);
    }
    printf("%llu\n", ways[k * r + 0]);
}

// AMPPZ 2017 F - Funkcja szyfrujaca, O(d^2) for d <= 18 digits
// appending a digit c to a number x with len digits gives f(10x + c) = 11 f(x) + c * 2^len;
// modulo 11 the first term vanishes, so c = n * inverse(2^len) mod 11 is forced
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// a^e mod m by repeated squaring, O(log e)
ll power(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m;
    while (e > 0) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

// the number with exactly d digits whose value of f is n, or "" if there is none
string withDigits(ll n, int d) {
    string rev;                                    // digits from the last one
    ll r = n;
    for (int len = d - 1; len >= 1; len--) {       // len = digits in front of the current one
        ll p2 = 1LL << len;
        ll c = r % 11 * power(p2 % 11, 11 - 2, 11) % 11;   // inverse by fermat, 11 is prime
        if (c > 9) return "";
        r -= c * p2;
        if (r < 0) return "";
        r /= 11;                                   // exact, r is divisible by 11 now
        rev += char('0' + c);
    }
    if (r < 1 || r > 9) return "";                 // what is left is the leading digit
    rev += char('0' + r);
    reverse(rev.begin(), rev.end());
    return rev;
}

string solve(ll n) {
    for (int d = 1; d <= 18; d++) {                // the leading digit alone gives 11^(d-1) <= n <= 10^18
        string m = withDigits(n, d);
        if (!m.empty()) return m;
    }
    return "NIE";
}

int main() {
    ll n;
    cin >> n;
    cout << solve(n) << "\n";
    return 0;
}

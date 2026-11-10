// AMPPZ 2011 C - Czy sie zatrzyma?, O(1)
// a multiple of 3 stays a multiple of 3 (n/2 and 3n + 3 both keep the factor), so it never reaches 1;
// an odd n > 1 becomes 3(n + 1), so the loop stops only if halving alone reaches 1: n is a power of two
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool stops(ll n) {
    return (n & (n - 1)) == 0;                     // a power of two has a single bit set
}

int main() {
    ll n;
    cin >> n;
    cout << (stops(n) ? "TAK" : "NIE") << "\n";
    return 0;
}

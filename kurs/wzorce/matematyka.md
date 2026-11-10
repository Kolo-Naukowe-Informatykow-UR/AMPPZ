# Wzorzec: matematyka I (modulo, potęgowanie, NWD, sito, zliczanie, parzystość)

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać zadanie "na liczby", gotowe szablony w C++ (reszty,
> potęgowanie, odwrotność, NWD, sito, pętla po wielokrotnościach, dwumiany) i jak szukać niezmiennika. Teoria
> i przykłady: [Dzień 6](../dni/06-matematyka.md). Kombinatoryka i prawdopodobieństwo to ścieżka M (Dni 16-17).

## Sygnały

- "Wypisz wynik modulo 10⁹ + 7", "ostatnia cyfra", "reszta z dzielenia".
- n albo wartości do 10⁹-10¹⁸ przy jednej liczbie na wejściu: wzór, O(log n) albo O(√n), nie pętla.
- "Dzielnik", "podzielne", "wielokrotność", "liczba pierwsza", wartości do 10⁶-10⁷: sito, tablica liczników.
- "Co ile", "kiedy znowu razem", "czy da się odmierzyć krokami a i b": NWD i NWW.
- Funkcja liczona po cyfrach albo bitach, którą trzeba odwrócić: rekurencja po ostatniej cyfrze i reszta modulo.
- "Czy proces się zatrzyma", "czy da się dojść do stanu": niezmiennik (parzystość, reszta, podzielność).
- "Każdy fragment długości k", "parzysta suma": porównanie sąsiednich okien, klasy reszt modulo k.
- Połowienie, "parzysta albo nieparzysta liczba", potęgi dwójki: zapis dwójkowy.

## Ruchy

| Ruch | Kiedy | Koszt | Przykład |
|---|---|---|---|
| Reszty po każdym działaniu | wynik modulo, ostatnie cyfry | O(1) na działanie | Dzień 6, sekcja 1 |
| Szybkie potęgowanie, odwrotność z Fermata | aᵉ dla dużego e, dzielenie modulo p | O(log e) | [2017 F Funkcja szyfrująca](../zadania/2017/f-funkcja-szyfrujaca.md) |
| Rekurencja po ostatniej cyfrze, reszta wymusza cyfrę | odwracanie funkcji po cyfrach | O(cyfry²) | [2017 F Funkcja szyfrująca](../zadania/2017/f-funkcja-szyfrujaca.md) |
| Pętla po wielokrotnościach | "dla każdego dzielnika", pary a \| b | O(M log M) | [2014 D Dzielniki](../zadania/2014/d-dzielniki.md) |
| Sito z najmniejszym dzielnikiem pierwszym | wiele rozkładów, liczby pierwsze do 10⁷ | O(M log log M) | Dzień 6, sekcja 4 |
| Niezmiennik procesu | "czy się zatrzyma", "czy osiągalne" | O(1) po obserwacji | [2011 C Czy się zatrzyma?](../zadania/2011/c-czy-sie-zatrzyma.md) |
| Zapis dwójkowy, bloki [2^j, 2^(j+1)) | połowienie, największa potęga dwójki | O(log n) | [2013 J Janosik](../zadania/2013/j-janosik.md) |
| Klasy reszt modulo k i jedna poprawka parzystości | warunek na każde okno długości k | O(n) | [2012 C Ciąg](../zadania/2012/c-ciag.md) |

## Szablony

```cpp
const ll MOD = 1'000'000'007;
ll sub(ll a, ll b) { return ((a - b) % MOD + MOD) % MOD; }   // never negative

// a^e mod m in O(log e)
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
ll inverse(ll a, ll p) { return power(a, p - 2, p); }   // p prime, p does not divide a

// gcd and lcm (std::gcd and std::lcm in <numeric> do the same in c++17)
ll lcm_(ll a, ll b) { return a / __gcd(a, b) * b; }

// smallest prime factor up to M; factorization by repeated division
vector<int> spf(M + 1, 0);
for (int i = 2; i <= M; i++)
    if (spf[i] == 0)
        for (int j = i; j <= M; j += i)
            if (spf[j] == 0) spf[j] = i;

// for every value v present, walk its multiples: O(M log M)
for (int v = 1; v <= M; v++) if (cnt[v])
    for (int w = 2 * v; w <= M; w += v) pairs += (ll)cnt[v] * cnt[w];

// binomial coefficients mod p for n up to N: factorials and inverse factorials once
vector<ll> f(N + 1), inv(N + 1);
f[0] = 1;
for (int i = 1; i <= N; i++) f[i] = f[i - 1] * i % MOD;
inv[N] = inverse(f[N], MOD);
for (int i = N; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;
auto C = [&](int n, int k) { return (k < 0 || k > n) ? 0 : f[n] * inv[k] % MOD * inv[n - k] % MOD; };

// bits
bool pow2 = n > 0 && (n & (n - 1)) == 0;
int lg = 63 - __builtin_clzll(n);              // floor(log2 n), n > 0
int ones = __builtin_popcountll(n);

// numbers divisible by d in [a, b]
ll cntDiv = b / d - (a - 1) / d;               // a >= 1
```

## Jak naginać

- **Najpierw małe przypadki na kartce albo brute force.** Wypisz wynik dla n = 1..10 i szukaj wzoru (potęgi dwójki,
  reszty, okresowość). Wzór potem udowodnij albo przynajmniej sprawdź brute force na tysiącach n.
- **Odwracanie funkcji:** dopisz ostatni element i zapisz, jak zmienia się wynik. Gdy część wzoru znika modulo jakiejś
  liczby, ostatni element jest wymuszony i całość odtwarzasz od końca bez cofania się.
- **"Dla każdej pary" przy małych wartościach:** tablica liczników i pętla po wielokrotnościach albo po dzielnikach;
  pary równych wartości liczysz osobno (cnt · (cnt - 1), bez i = j).
- **Niezmiennik:** szukaj cechy, której nie zmienia żaden ruch (podzielność, parzystość sumy, reszta, kolor pola). Daje
  dowód NIE; dla TAK potrzebny jest jeszcze przepis.
- **Warunek na każde okno długości k:** porównaj sąsiednie okna; zostają równości aᵢ ~ aᵢ₊ₖ, czyli k niezależnych klas
  i jeden warunek na pierwsze okno.
- **Licz to, co łatwiejsze:** oddane zamiast schowanych, dopełnienie zamiast zbioru, wszystkie minus złe.
- **Sumy blokami:** gdy wyrażenie jest stałe na kawałkach (największa potęga dwójki, ⌊n / d⌋), sumuj kawałkami,
  a nie po jednym.
- **Przepełnienia:** n(n + 1) przy n = 10⁹ to 10¹⁸; iloczyn dwóch reszt modulo większego niż 3 · 10⁹ wymaga
  `__int128`; NWW licz jako a / NWD · b.

## Zadania z archiwum

Grupy "matematyka" i "teoria liczb" w [katalogu](../zadania/katalog.md) oraz zadania z nimi jako techniką poboczną.
Sprawdzone w kursie: 2014 D, 2017 F, 2011 C, 2013 J, 2012 C (także [2021 F Farba](../zadania/2021/f-farba.md):
suma harmoniczna, Dzień 4). Na później: 2011 H Herbata z mlekiem (38 z 55 drużyn, parzystość i porównanie sum ułamków
o mianownikach 2ⁿ), 2016 A Słaby generator pseudolosowy (teoria liczb, bez rankingu), 2022 E Euklides (3 z 50 drużyn,
ścieżka M), 2006 H Szkło.

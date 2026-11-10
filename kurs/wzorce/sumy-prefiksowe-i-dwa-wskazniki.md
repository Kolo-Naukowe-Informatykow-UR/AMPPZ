# Wzorzec: sumy prefiksowe, tablice różnicowe i dwa wskaźniki

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać, że pomogą sumy prefiksowe, tablica różnicowa
> albo okno z dwoma wskaźnikami, gotowe szablony w C++ i jak je nagiąć. Teoria i przykłady:
> [Dzień 4](../dni/04-prefiksy-dwa-wskazniki.md).

## Sygnały

- Wiele pytań o sumę, liczbę albo koszt kawałka tablicy; "dla każdego fragmentu", "ile fragmentów spełnia ...".
- Wiele operacji "dodaj na przedziale", a odczyt dopiero na końcu; przedziały czasu, "ile naraz", "łączny czas".
- "Najdłuższy (najkrótszy) fragment, w którym ...", "pary, których różnica nie przekracza k".
- Wybór elementów "blisko siebie" i koszt zależny od odległości (zrównanie, przesunięcie do wspólnej wartości).
- Permutacja i pytanie o podział na niezależne części; "najlepsza para i < j".
- Plansza i pytania o prostokąty.
- n do 10⁵-10⁶, a naiwne rozwiązanie przegląda wszystkie n² kawałków albo par.

## Sześć ruchów

| Ruch | Kiedy | Koszt | Przykład |
|---|---|---|---|
| Suma prefiksowa | suma, liczba, XOR kawałka | O(n) raz, O(1) na kawałek | [2018 J Jednakowe szaliki](../zadania/2018/j-jednakowe-szaliki.md) |
| Suma prefiksowa i mapa | ile kawałków ma sumę k, liczby ujemne | O(n log n) | CSES Subarray Sums II |
| Maksimum (minimum) prefiksu | najlepsza para i < j, "prefiks to 1..i" | O(n) | [2012 I Inwersje](../zadania/2012/i-inwersje.md) |
| Tablica różnicowa | dodaj na przedziale, odczyt na końcu | O(1) na operację, O(n) odczyt | 2D: 2021 L Leniwce |
| Zdarzenia na posortowanych końcach | jak wyżej, końce do 10⁹ | O(n log n) | [2013 D Demonstracje](../zadania/2013/d-demonstracje.md) |
| Dwa wskaźniki | warunek monotoniczny w długości okna, okno w posortowanej tablicy | O(n) po sortowaniu | [2015 D Studniówka](../zadania/2015/d-studniowka.md) |

Ruch łączony: sumy prefiksowe po parzystości indeksów i szacowanie harmoniczne w
[2021 F Farba](../zadania/2021/f-farba.md).

## Szablony

```cpp
// prefix sums: sum of a[l..r]
vector<ll> pre(n + 1, 0);
for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
auto sum = [&](int l, int r) { return pre[r + 1] - pre[l]; };

// 2d prefix sums: sum of rows r1..r2, columns c1..c2
for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
        P[i + 1][j + 1] = g[i][j] + P[i][j + 1] + P[i + 1][j] - P[i][j];
auto rect = [&](int r1, int c1, int r2, int c2) {
    return P[r2 + 1][c2 + 1] - P[r1][c2 + 1] - P[r2 + 1][c1] + P[r1][c1];
};

// number of pieces with sum k (negative values allowed)
map<ll, int> seen{{0, 1}};
ll cur = 0, cnt = 0;
for (int i = 0; i < n; i++) { cur += a[i]; cnt += seen[cur - k]; seen[cur]++; }

// difference array: add v on [l, r], read everything at the end
vector<ll> d(n + 1, 0);
d[l] += v; d[r + 1] -= v;
for (int i = 1; i < n; i++) d[i] += d[i - 1];  // now d[i] is the value at i

// events for large coordinates: most intervals active at once
vector<pair<ll, int>> ev;                      // (time, +1 or -1), -1 first at equal times
sort(ev.begin(), ev.end());
int active = 0, most = 0;
for (auto [t, delta] : ev) most = max(most, active += delta);

// two pointers: longest good window
int l = 0, best = 0;
for (int r = 0; r < n; r++) {
    add(a[r]);
    while (!good()) remove(a[l++]);
    best = max(best, r - l + 1);
}

// cost of bringing sorted a[l..r] to its median md
auto cost = [&](int l, int r) {
    int md = (l + r) / 2;
    return a[md] * (md - l) - (pre[md] - pre[l]) + (pre[r + 1] - pre[md + 1]) - a[md] * (r - md);
};
```

## Jak naginać

- **Najpierw zapytaj o monotoniczność.** Dwa wskaźniki wymagają, żeby podokno dobrego okna było dobre (albo nadokno
  wystarczającego wystarczało). Liczby ujemne w warunku na sumę to psują; wtedy sumy prefiksowe z mapą albo
  z wyszukiwaniem binarnym.
- **Liczenie zamiast szukania.** Szablon gąsienicy daje dla każdego r najmniejszy dobry początek l, więc liczba dobrych
  okien to suma r - l + 1. Pary "różnica ≤ k" to hi - lo dla każdego elementu.
- **Inna operacja niż dodawanie:** liczniki liter (tablica cnt[26][n + 1]), XOR, sumy po parzystości indeksów, sumy
  ważone (Σ i · a[i] pozwala liczyć koszt przesunięcia do wspólnego punktu).
- **Koszt zależny od odległości:** posortuj; wybrane elementy tworzą okno, cel to mediana (suma odległości) albo
  średnia (suma kwadratów); koszt okna z dwóch sum prefiksowych.
- **Duże współrzędne:** kompresja albo zdarzenia; między kolejnymi zdarzeniami stan jest stały i fragment liczy się
  w całości. Do licznika aktywnych można dołożyć, kto jest aktywny, gdy jest ich mało.
- **Zadanie dla każdego b od 1 do M:** sprawdź, czy elementów "dużych względem b" jest najwyżej suma / b; resztę,
  zachowującą się jednakowo, załatwiają sumy prefiksowe.
- **Plansza obrócona o 45 stopni:** kwadrat w metryce |dx| + |dy| ≤ k (romb) staje się zwykłym kwadratem po zamianie
  współrzędnych (x + y, x - y), a wtedy działają sumy prefiksowe 2D (2021 L Leniwce).

## Zadania z archiwum

Grupy "sumy prefiksowe" i "dwa wskaźniki" w [katalogu](../zadania/katalog.md) oraz zadania z tymi technikami jako
pobocznymi. Sprawdzone w kursie: 2015 D, 2018 J, 2012 I, 2013 D, 2021 F, a z dwoma wskaźnikami jako częścią
wyszukiwania binarnego 2017 L Leśny kemping ([Dzień 5](../dni/05-wyszukiwanie-binarne.md)). Na później (trudność 3-5 według rankingu):
2021 L Leniwce (sumy prefiksowe i tablica różnicowa 2D), 2014 G Globalne ocieplenie i 2013 K Kocyki (zamiatanie, tydzień
2), 2017 B Bajki (dwa wskaźniki ze strukturą danych).

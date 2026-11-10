# Wzorzec: programowanie dynamiczne I (stan i przejście, plecak, najdłuższy podciąg)

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać DP, jak zapisać stan i przejście, gotowe szablony
> w C++ (plecak 0/1, najmniej monet, liczba sposobów dla podzbiorów i monet, LIS w O(n log n) z odtworzeniem, LCS
> z odtworzeniem, odległość edycyjna) i jak zmniejszyć stan, gdy nie mieści się w limitach. Teoria i przykłady:
> [Dzień 10](../dni/10-dp-1.md).

## Sygnały

- "Na ile sposobów" (zwykle "modulo 10⁹ + 7"), "najwięcej / najmniej" po ciągu decyzji, a zachłanne ma kontrprzykład.
- Ciąg do kilku tysięcy elementów i "rozłączne fragmenty", "każdy kawałek musi": DP po prefiksach, O(n²).
- Pojemność, budżet albo suma do ok. 10⁵-10⁶ i przedmioty "każdy raz" albo "dowolnie wiele": plecak.
- "Dokładnie k elementów", "suma podzielna przez r" z małym r: plecak z dodatkowym wymiarem (liczba, reszta).
- "Podciąg" (nie fragment), "w tej samej kolejności", "rosnący": LIS (jeden ciąg) albo LCS (dwa ciągi).
- "Najmniej operacji wstaw / usuń / zamień": odległość edycyjna.
- "Zabronione pary / trójki", "żadne dwa sąsiednie": stan z ostatnimi elementami.
- "Wypisz rozwiązanie", "najmniejsze leksykograficznie": odtwarzanie, DP od końca.
- Limity: liczba stanów razy koszt przejścia ≤ ok. 10⁸; n do 10⁵-10⁶ z jednym wymiarem i przejściem O(1) albo O(log n).

## Ruchy

| Ruch | Kiedy | Zadanie |
|---|---|---|
| Ostatni element wolny albo kończy kawałek (j, i]; warunek z sum prefiksowych | podział ciągu na dobre kawałki | 2002 H Słoneczne wczasy |
| DP od końca, budowa od początku najmniejszym dobrym wyborem | "najmniejszy leksykograficznie", wypisz rozwiązanie | 2013 I Inżynieria genetyczna |
| LCS: tablica po prefiksach dwóch ciągów | dopasowania w zachowanej kolejności | 1998 B Cross-country |
| Stan = ostatnie L - 1 znaków | zakazane fragmenty długości L, liczenie napisów | 2005 D Szaszłyki |
| Plecak po klasach nierozróżnialnych, dwumiany | warunek zależy tylko od reszty albo typu, n duże | 2017 J Jesienne porządki |
| Zamiana wymiaru: dp po wartości zamiast po wadze | W do 10⁹, suma wartości mała | AtCoder Educational DP Contest E (Knapsack 2) |

## Szablony

Sprawdzone programem, który porównuje je z przeglądem wszystkich podzbiorów, wyborów i ciągów operacji na
20 000 losowych małych danych (wynik w sekcji "Zadania z archiwum").

**Plecak 0/1: największa wartość przy pojemności W.**

```cpp
long long knapsack01(const vector<int>& w, const vector<long long>& v, int W) {
    vector<long long> dp(W + 1, 0);            // dp[c] = best value with weight <= c
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)        // downwards: each item at most once
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}
```

**Najmniej monet na kwotę x (monety bez limitu); -1, gdy się nie da.**

```cpp
int minCoins(const vector<int>& coins, int x) {
    const int INF = INT_MAX / 2;
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int c = 1; c <= x; c++)
        for (int w : coins)
            if (w <= c) dp[c] = min(dp[c], dp[c - w] + 1);
    return dp[x] >= INF ? -1 : dp[x];
}
```

**Liczba sposobów modulo MOD: podzbiory o sumie x, zbiory monet i ciągi monet.**

```cpp
long long countSubsets(const vector<int>& a, int x) {      // each element at most once
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int w : a)
        for (int c = x; c >= w; c--) dp[c] = (dp[c] + dp[c - w]) % MOD;
    return dp[x];
}
long long coinSets(const vector<int>& coins, int x) {      // 1 + 3 and 3 + 1 are the same
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int w : coins)                        // coins outside: each multiset counted once
        for (int c = w; c <= x; c++) dp[c] = (dp[c] + dp[c - w]) % MOD;
    return dp[x];
}
long long coinSeqs(const vector<int>& coins, int x) {      // 1 + 3 and 3 + 1 are different
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int c = 1; c <= x; c++)               // sums outside: the last coin is any coin
        for (int w : coins)
            if (w <= c) dp[c] = (dp[c] + dp[c - w]) % MOD;
    return dp[x];
}
```

**LIS w O(n log n) z odtworzeniem (indeksy elementów).**

```cpp
vector<int> lis(const vector<int>& a, bool strict = true) {
    vector<int> tailVal, tailIdx, parent(a.size(), -1);
    for (int i = 0; i < (int)a.size(); i++) {
        auto it = strict ? lower_bound(tailVal.begin(), tailVal.end(), a[i])
                         : upper_bound(tailVal.begin(), tailVal.end(), a[i]);
        int len = it - tailVal.begin();        // a[i] ends a subsequence of length len + 1
        if (len > 0) parent[i] = tailIdx[len - 1];
        if (it == tailVal.end()) { tailVal.push_back(a[i]); tailIdx.push_back(i); }
        else { *it = a[i]; tailIdx[len] = i; }
    }
    vector<int> res;
    for (int i = tailIdx.empty() ? -1 : tailIdx.back(); i != -1; i = parent[i]) res.push_back(i);
    reverse(res.begin(), res.end());
    return res;                                // res.size() is the length
}
```

**LCS z odtworzeniem.**

```cpp
string lcs(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> L(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            L[i][j] = (a[i - 1] == b[j - 1]) ? L[i - 1][j - 1] + 1 : max(L[i - 1][j], L[i][j - 1]);
    string res;
    for (int i = n, j = m; i > 0 && j > 0; ) {  // walk back from (n, m)
        if (a[i - 1] == b[j - 1]) { res += a[i - 1]; i--; j--; }
        else if (L[i - 1][j] >= L[i][j - 1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}
```

**Odległość edycyjna (wstaw, usuń, zamień po 1).**

```cpp
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    iota(prev.begin(), prev.end(), 0);         // from "" to b[0..j): j insertions
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++)
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + (a[i - 1] != b[j - 1])});
        swap(prev, cur);
    }
    return prev[m];
}
```

**Rekurencja z pamięcią (gdy kolejność stanów jest trudna do zapisania pętlą).**

```cpp
vector<long long> memo;                        // -1 = not computed yet
long long solve(int s) {
    if (s <= 1) return 1;                      // base cases
    long long& r = memo[s];
    if (r != -1) return r;
    return r = (solve(s - 1) + solve(s - 2)) % MOD;   // transition
}
```

Rekurencja głębokości 10⁶ może przepełnić stos; wtedy pętla w kolejności topologicznej stanów.

## Jak naginać

- **Zapytaj, co przyszłość musi wiedzieć.** Stan to tylko te informacje o przeszłości, od których zależą dalsze
  decyzje; napisy i zbiory, które różnią się czymś innym, liczy się razem.
- **Przejście przez ostatnią decyzję.** Ostatni element, ostatni kawałek, ostatni przedmiot, ostatnie dopasowanie.
  Gdy ostatnich decyzji jest dużo, szukaj monotoniczności, która wskazuje najlepszą od razu.
- **Zgrupuj nierozróżnialne.** c identycznych (dla warunku) elementów to jedno przejście z dwumianem C(c, x) zamiast
  c przejść.
- **Zamień wymiar.** Pojemność do 10⁹ i małe wartości: dp po wartości. Długi ciąg i mały alfabet: dp po literach.
- **Oszczędzaj pamięć.** Wiersz zależy od poprzedniego: dwa wiersze albo jeden z pętlą w dobrą stronę. Pełna tabela
  tylko wtedy, gdy trzeba odtworzyć rozwiązanie.
- **Od końca.** Odpowiedź najmniejsza leksykograficznie albo "ile jeszcze można od tej pozycji": DP po sufiksach.
- **Cykle w zależnościach.** Nie ma kolejności topologicznej: uogólniony Dijkstra ([karta grafów z wagami](grafy-z-wagami.md)).

## Zadania z archiwum

Omówione w kursie: [2002 H Słoneczne wczasy](../zadania/2002/h-sloneczne-wczasy.md),
[2013 I Inżynieria genetyczna](../zadania/2013/i-inzynieria-genetyczna.md),
[1998 B Cross-country](../zadania/1998/b-cross-country.md), [2005 D Szaszłyki](../zadania/2005/d-szaszlyki.md),
[2017 J Jesienne porządki](../zadania/2017/j-jesienne-porzadki.md).

Do samodzielnej pracy (grupa "DP" w [katalogu](../zadania/katalog.md)): 2003 G Gadanki (najkrótszy fragment tekstu
do 10⁷ liter, z którego da się wykreślić alfabet: DP po literach alfabetu, O(n · 26) albo O(n)), 2022 I Inwestorzy
(14 z 50 drużyn), 2022 B Bary (17 z 50). Te trzy nie są w kursie rozwiązane ani przetestowane; techniki w katalogu
pochodzą z samej treści. Dwa zadania z grupy "DP" w katalogu, 2012 D DNA i 2016 J Kamień, papier, nożyce, po analizie
samej treści rozwiązuje jedna obserwacja, bez tablicy DP (odpowiedź ma bardzo prostą postać); w kursie nie są
rozwiązane ani przetestowane, więc to dobre ćwiczenie z pytania "czy na pewno potrzebuję DP".

Szablony z tej karty sprawdził program `day10-card_check.cpp` (poza repozytorium) na 20 000 losowych małych danych:
plecak 0/1 i liczba podzbiorów o danej sumie z przeglądem wszystkich podzbiorów, najmniej monet i zbiory monet
z przeglądem wszystkich krotności, ciągi monet z rekurencją po ostatniej monecie, LIS (ściśle rosnący
i niemalejący) z przeglądem wszystkich podciągów i sprawdzeniem odtworzonych indeksów, LCS z przeglądem podciągów
pierwszego napisu i sprawdzeniem odtworzonego napisu, odległość edycyjna (5000 par) z BFS po napisach,
rekurencja z pamięcią z pętlą dla s ≤ 10 000. Zero rozbieżności.

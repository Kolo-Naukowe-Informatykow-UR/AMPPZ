# Wzorzec: grafy z wagami (Dijkstra, BFS 0-1, Find-Union, MST)

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać najkrótsze ścieżki z wagami, składowe przy dodawaniu
> krawędzi i drzewo rozpinające, gotowe szablony w C++ (Dijkstra z wieloma źródłami, BFS 0-1, Find-Union, Kruskal,
> zapytania offline z progiem, Floyd-Warshall) i jak nagiąć Dijkstrę do grafu ukrytego, czasu i kosztów zależnych od
> innych kosztów. Teoria i przykłady: [Dzień 9](../dni/09-grafy-2.md). Grafy bez wag: [karta grafów I](grafy.md).

## Sygnały

- "Najkrótsza / najtańsza / najszybsza trasa", długości, czasy albo ceny na krawędziach: Dijkstra.
- Ruchy darmowe i ruchy za 1 ("ile najmniej ścian zburzyć", "ile najmniej zmian kierunku"): BFS 0-1.
- "Najbliższa stacja / szpital / wyjście" z wielu miejsc naraz: Dijkstra z wieloma źródłami.
- "Odległość między każdą parą", n do ok. 400-500: Floyd-Warshall.
- "Połącz wszystkie najtaniej", "sieć", "z każdego da się dojechać do każdego": minimalne drzewo rozpinające.
- "Po każdym nowym połączeniu: czy x i y są połączone, ile jest grup": Find-Union online.
- "Czy da się przy limicie b", "najdłuższy odcinek bez tankowania", "największy skok": wąskie gardło, zapytania offline
  posortowane po b i Kruskal.
- Krawędzie znikają, a pytania są o spójność: przejdź od końca, usuwanie staje się dodawaniem do Find-Union.
- Punkty na płaszczyźnie, koszt z różnic współrzędnych, "dowolna trasa": graf pełny do odchudzenia.
- Koszt rzeczy = min(zrób od razu, rozbij na części i zapłać za części), zależności cykliczne: uogólniony Dijkstra.
- Limity: n, m do 2 · 10⁵-10⁶ to O((n + m) log n); n do 500 pozwala na n³; sumy wag do 10⁹ · 10⁵ to `long long`.

## Ruchy

| Ruch | Kiedy | Zadanie |
|---|---|---|
| Tylko sąsiedzi po posortowaniu x i y | koszt odcinka min(\|dx\|, \|dy\|) albo \|dx\| + \|dy\|, n do 2 · 10⁵ | 2014 K Kapitan |
| Uogólniony Dijkstra: najmniejszy nieostateczny jest ostateczny | koszt[i] = min(z_i, u_i + suma kosztów części), u_i > 0 | 2012 H Hydra |
| Dijkstra na czasach przybycia z czekaniem | okna czasowe na krawędziach, wolno czekać (FIFO) | 2004 I Obóz Babilon |
| Odległość do najbliższej stacji jako waga krawędzi, potem Kruskal offline | tankowanie, pojemność, wiele zapytań z progiem | 2014 B Benzyna |
| Graf stanów z wagami | jednorazowa zniżka, liczba użytych specjalnych ruchów | CSES Flight Discount |

## Szablony

Sprawdzone programem, który porównuje je z Floydem-Warshallem i z przeglądem wszystkich drzew rozpinających na
20 000 losowych grafach (wynik w sekcji "Zadania z archiwum").

**Dijkstra z jednym lub wieloma źródłami.**

```cpp
// dist = LLONG_MAX means unreachable; src holds one or many sources
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, const vector<int>& src) {
    vector<long long> dist(adj.size(), LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    for (int s : src) { dist[s] = 0; pq.push({0, s}); }
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d != dist[v]) continue;            // stale entry
        for (auto [u, w] : adj[v])
            if (d + w < dist[u]) { dist[u] = d + w; pq.push({dist[u], u}); }
    }
    return dist;
}
```

**BFS 0-1.**

```cpp
// weights are 0 or 1; dist = INT_MAX means unreachable
vector<int> bfs01(const vector<vector<pair<int, int>>>& adj, int s) {
    vector<int> dist(adj.size(), INT_MAX);
    deque<int> dq;
    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int v = dq.front(); dq.pop_front();
        for (auto [u, w] : adj[v])
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                if (w == 0) dq.push_front(u); else dq.push_back(u);
            }
    }
    return dist;
}
```

**Find-Union.**

```cpp
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int v) {
        int r = v;
        while (p[r] != r) r = p[r];
        while (p[v] != r) { int nx = p[v]; p[v] = r; v = nx; }   // path compression
        return r;
    }
    bool unite(int a, int b) {                 // false if already in one set
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);         // union by size
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};
```

**Kruskal.**

```cpp
// edges as (weight, u, v) with vertices 0..n-1; -1 if the graph is not connected
long long kruskal(int n, vector<array<long long, 3>> edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long total = 0;
    int taken = 0;
    for (auto [w, u, v] : edges)
        if (dsu.unite(u, v)) { total += w; taken++; }
    return taken == n - 1 ? total : -1;
}
```

**Zapytania offline z progiem** ("czy x i y łączą krawędzie o wadze ≤ b").

```cpp
// qs[i] = (b, x, y); answer 1 iff x and y are connected by edges of weight <= b
vector<char> threshold_queries(int n, vector<array<long long, 3>> edges, const vector<array<long long, 3>>& qs) {
    sort(edges.begin(), edges.end());
    vector<int> ord(qs.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return qs[a][0] < qs[b][0]; });
    DSU dsu(n);
    vector<char> ans(qs.size());
    size_t e = 0;
    for (int i : ord) {
        while (e < edges.size() && edges[e][0] <= qs[i][0]) { dsu.unite(edges[e][1], edges[e][2]); e++; }
        ans[i] = dsu.find(qs[i][1]) == dsu.find(qs[i][2]);
    }
    return ans;
}
```

**Floyd-Warshall** (wszystkie pary, n do ok. 500).

```cpp
// d[i][j] = weight of edge i -> j, 0 on the diagonal, INF (e.g. 1e18) if there is no edge
for (int k = 0; k < n; k++)                    // k must be the outer loop
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
```

## Jak naginać

- **Odchudź graf.** Z n² krawędzi zostaw tylko te, których nie da się zastąpić drogą przez inne wierzchołki bez straty
  (sąsiedzi po posortowaniu, najbliższy w każdym kierunku). Dowód zawsze ten sam: długą krawędź rozbij na krótsze
  przez punkty pośrednie.
- **Zmień, czym jest odległość.** Czas przybycia z czekaniem, liczba przesiadek, para (koszt, czas) porównywana
  leksykograficznie: Dijkstra działa, dopóki dłuższa droga nie może dać lepszego wyniku dalej (wcześniejsze przybycie
  nigdy nie szkodzi, wagi nieujemne).
- **Uogólnij relaksację.** Wartość wierzchołka może być dowolną funkcją wartości innych, byle nie mniejszą od każdej
  z nich (np. u + suma przy u > 0). Wtedy najmniejsza nieostateczna wartość jest ostateczna, jak w Dijkstrze.
- **Dodaj źródło.** Wiele startów to jeden wirtualny wierzchołek połączony z nimi krawędziami 0, czyli wszystkie
  w kolejce na starcie.
- **Przejdź do wąskiego gardła.** Pytanie o "najdłuższe ogniwo" zamiast sumy to MST i zapytania offline posortowane po
  progu.
- **Od końca.** Usuwanie krawędzi z pytaniami o spójność odwróć w czasie i dodawaj do Find-Union.

## Zadania z archiwum

Omówione w kursie: [2014 K Kapitan](../zadania/2014/k-kapitan.md), [2012 H Hydra](../zadania/2012/h-hydra.md),
[2004 I Obóz Babilon](../zadania/2004/i-oboz-babilon.md), [2014 B Benzyna](../zadania/2014/b-benzyna.md).

Do samodzielnej pracy (grupy "najkrótsze ścieżki" i "DSU/MST" w [katalogu](../zadania/katalog.md)): 2024 B Bagaże
(n do 400 przy m do 5 · 10⁵: sygnał na Floyda-Warshalla), 2002 A Autostrady (koszt MST jako funkcja czasu; uwaga:
przykład w PDF ma zlepione liczby), 2013 B Bajthattan (Find-Union na ścianach grafu dualnego, 9 z 52 drużyn). Te trzy
nie są w kursie rozwiązane ani przetestowane; techniki w katalogu pochodzą z samej treści.

Szablony z tej karty sprawdził program `day9-card_check.cpp` (poza repozytorium): Dijkstra z 1-3 źródłami w grafach
skierowanych i nieskierowanych oraz BFS 0-1 porównane z Floydem-Warshallem, Kruskal z przeglądem wszystkich zbiorów
n - 1 krawędzi, zapytania z progiem z BFS po krawędziach ≤ b.

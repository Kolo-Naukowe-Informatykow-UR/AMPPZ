# Wzorzec: grafy I (BFS, DFS, składowe, siatki, sortowanie topologiczne)

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać graf w treści (także ukryty), gotowe szablony w C++
> (BFS z wieloma źródłami, BFS na siatce, składowe bez rekurencji, Kahn z najdłuższą ścieżką, dwukolorowanie) i jak
> zmienić definicję wierzchołka, gdy zwykły graf nie wystarcza. Teoria i przykłady: [Dzień 8](../dni/08-grafy-1.md).
> Grafy z wagami (Dijkstra, Find-Union, MST): Dzień 9.

## Sygnały

- "Połączenia", "znajomi", "drogi", "przejścia", "zależności", "sąsiednie pola": graf wprost.
- "Najmniejsza liczba ruchów / kroków / przesiadek" bez wag: BFS.
- Mapa z `.` i `#` (albo `X`), "obszar", "spójny", "wyspa", "pokój": siatka, flood fill.
- "Najkrótsza, a z nich pierwsza leksykograficznie": BFS od celu i zachłanny wybór ruchu.
- "Czy da się ustawić w kolejności", "najpierw ... potem", "zależy od": sortowanie topologiczne, cykl to NIE.
- Układ nierówności, relacje <, =, >: strzałki od mniejszego do większego; cykl to sprzeczność, najdłuższa ścieżka to
  najmniejszy zakres liczb.
- "Podziel na dwie grupy tak, żeby wrogowie byli w różnych": dwukolorowanie (graf dwudzielny).
- Ruch zależy od czegoś więcej niż pozycja (ostatni ruch, klucz, liczba użytych specjalnych akcji): graf stanów.
- Limity: n, m do 10⁵-10⁶ to O(n + m); n do ok. 5000 pozwala na macierz albo BFS z każdego wierzchołka.

## Ruchy

| Ruch | Kiedy | Zadanie |
|---|---|---|
| BFS od celu zamiast od startu | odległość do jednego celu z wielu miejsc, wybór drogi krok po kroku | 2005 G Skarb |
| BFS z wieloma źródłami | odległość do najbliższego z kilku obiektów | CSES Monsters |
| Flood fill, łączność 4 albo 8 | obszary na mapie, liczba kształtów | 1996 C Shapes |
| Literały x i -x jako wierzchołki | nierówności z minusami, 2-SAT | 2015 B Bogacze |
| Sklejenie równości, potem DAG | relacje "=" obok "<" | 1998 F Relations |
| Przejście po czasie od końca | krawędź działa tylko w chwili zdarzenia, obiekt znika | 2022 M Mniejsze zło |
| Wierzchołek = stan | dodatkowa pamięć ruchu (kierunek, klucz, licznik) | 1997 C 3D-Chess (archiwum) |

## Szablony

Wierzchołki 0..n-1 (przy numeracji od 1 dodaj jeden wierzchołek albo odejmij 1 przy wczytaniu).

```cpp
// bfs from many sources: dist[v] = edges to the nearest source, -1 = unreachable
vector<int> bfs(const vector<vector<int>>& adj, const vector<int>& sources, vector<int>& parent) {
    int n = adj.size();
    vector<int> dist(n, -1), q;
    parent.assign(n, -1);
    for (int s : sources) if (dist[s] == -1) { dist[s] = 0; q.push_back(s); }
    for (size_t h = 0; h < q.size(); h++)
        for (int w : adj[q[h]])
            if (dist[w] == -1) { dist[w] = dist[q[h]] + 1; parent[w] = q[h]; q.push_back(w); }
    return dist;
}

// path source -> t from the parents of bfs (empty if t is unreachable)
vector<int> path_to(int t, const vector<int>& dist, const vector<int>& parent) {
    vector<int> p;
    if (dist[t] == -1) return p;
    for (int v = t; v != -1; v = parent[v]) p.push_back(v);
    reverse(p.begin(), p.end());
    return p;
}

// bfs on a grid from (sr, sc); '#' is a wall; dist[r * k + c]
vector<int> grid_bfs(const vector<string>& g, int sr, int sc) {
    int w = g.size(), k = g[0].size();
    const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, -1, 1};
    vector<int> dist(w * k, -1), q = {sr * k + sc};
    dist[sr * k + sc] = 0;
    for (size_t h = 0; h < q.size(); h++) {
        int r = q[h] / k, c = q[h] % k;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= w || nc < 0 || nc >= k || g[nr][nc] == '#' || dist[nr * k + nc] != -1) continue;
            dist[nr * k + nc] = dist[q[h]] + 1;
            q.push_back(nr * k + nc);
        }
    }
    return dist;
}

// connected components of an undirected graph without recursion; returns their number
int components(const vector<vector<int>>& adj, vector<int>& comp) {
    int n = adj.size(), C = 0;
    comp.assign(n, -1);
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        vector<int> st = {s};
        comp[s] = C;
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int w : adj[v]) if (comp[w] == -1) { comp[w] = C; st.push_back(w); }
        }
        C++;
    }
    return C;
}

// kahn: topological order of a directed graph (shorter than n = there is a cycle);
// len[v] = edges on the longest path ending at v
vector<int> topo(const vector<vector<int>>& adj, vector<int>& len) {
    int n = adj.size();
    vector<int> indeg(n, 0), order;
    len.assign(n, 0);
    for (int u = 0; u < n; u++) for (int v : adj[u]) indeg[v]++;
    for (int v = 0; v < n; v++) if (indeg[v] == 0) order.push_back(v);
    for (size_t h = 0; h < order.size(); h++)
        for (int v : adj[order[h]]) {
            len[v] = max(len[v], len[order[h]] + 1);
            if (--indeg[v] == 0) order.push_back(v);
        }
    return order;
}

// two colouring: col[v] in {0, 1}, false if some edge joins equal colours (an odd cycle)
bool bipartite(const vector<vector<int>>& adj, vector<int>& col) {
    int n = adj.size();
    col.assign(n, -1);
    for (int s = 0; s < n; s++) {
        if (col[s] != -1) continue;
        vector<int> q = {s};
        col[s] = 0;
        for (size_t h = 0; h < q.size(); h++)
            for (int w : adj[q[h]]) {
                if (col[w] == -1) { col[w] = col[q[h]] ^ 1; q.push_back(w); }
                else if (col[w] == col[q[h]]) return false;
            }
    }
    return true;
}
```

Szablony sprawdzone programem testowym na 20 000 losowych grafów (do 8 wierzchołków, skierowane i nieskierowane, także
z pętlami i krawędziami wielokrotnymi) i siatek do 4 × 4 przeciw algorytmowi Floyda-Warshalla (odległości, drogi
i osiągalność), przeglądowi wszystkich ścieżek prostych (najdłuższa ścieżka, cykl) i wszystkich 2ⁿ kolorowań: bez
błędów, kompilacja `g++ -std=c++17 -O2 -Wall -Wextra` bez ostrzeżeń.

## Jak naginać

- **Zmień wierzchołek.** Gdy sama pozycja nie wystarcza, wierzchołkiem jest stan (pozycja, kierunek, klucze,
  licznik). Policz stany przed pisaniem: iloczyn zakresów musi się zmieścić w pamięci.
- **Zmień kierunek.** BFS od celu daje odległości "do celu" dla wszystkich naraz; w grafie skierowanym trzeba wtedy
  odwrócić krawędzie.
- **Dodaj wierzchołki.** Przeciwieństwa zmiennych (-x), wierzchołek-źródło połączony ze wszystkimi startami (to to
  samo, co BFS z wieloma źródłami), wierzchołki na środkach krawędzi, gdy krawędzie mają długość 2.
- **Sklej wierzchołki.** Równości, składowe silnie spójne, pola jednego obszaru: najpierw sklejenie, potem praca na
  mniejszym grafie.
- **Przejdź po czasie od końca.** Gdy krawędzie albo wierzchołki znikają w czasie, od końca tylko się pojawiają.
- **Graf bez wag, ale krawędzie 0 i 1:** BFS 0-1 (Dzień 9), nie zwykły BFS.

## Zadania z archiwum

Omówione w kursie: [2005 G Skarb](../zadania/2005/g-skarb.md), [2015 B Bogacze](../zadania/2015/b-bogacze.md),
[1996 C Shapes](../zadania/1996/c-shapes.md), [2022 M Mniejsze zło](../zadania/2022/m-mniejsze-zlo.md),
[1998 F Relations](../zadania/1998/f-relations.md); wcześniej [2012 I Inwersje](../zadania/2012/i-inwersje.md)
(składowe bez budowania grafu, Dzień 4).

Do samodzielnej pracy (grupa "grafy BFS/DFS" w [katalogu](../zadania/katalog.md)): 1997 C 3D-Chess (BFS po stanach
pozycja i rodzaj ostatniego ruchu), 2005 H Liczby Erdősa (BFS z warunkiem na rosnące lata), 2006 B Dywersja (BFS po
parach stanów w odwróconym grafie), 2022 D Droga na szczyt (DFS na drzewie, rozmiary poddrzew; wraca w Dniu 12).
Uwaga: 1996 E Minimal pour out of vessels (BFS po ilości płynu) ma w PDF test organizatorów, którego wynik (35 dla
naczyń 70 i 101 przy celu 1) nie zgadza się z treścią (13 · 70 - 9 · 101 = 1 daje 22 ruchy), więc kurs go nie używa.

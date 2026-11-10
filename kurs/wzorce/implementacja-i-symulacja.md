# Wzorzec: implementacja i symulacja

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać zadanie, w którym trzeba tylko dokładnie wykonać
> proces z treści, szkielet symulacji, plansza z tablicą kierunków, grupowanie w STL, lista przypadków brzegowych
> i jak skrócić symulację, gdy jest za długa. Teoria: [Dzień 2](../dni/02-stl-symulacja.md).

## Sygnały

- Treść opisuje proces krok po kroku: ruchy na planszy, rundy gry, kolejne operacje na napisie.
- "Wypisz stan po", "kto wygra, jeśli obaj grają według reguły", "ile kroków do zakończenia".
- Liczba kroków razy koszt kroku mieści się w budżecie (ok. 10⁸ operacji na sekundę).
- Wiele szczegółów w treści i wiele przykładów z różnymi odpowiedziami `NIE`.
- Pytanie o grupy równych obiektów ("ile różnych", "czy któreś się powtarza").

## Trzy elementy symulacji

Przed kodem nazwij: **stan** (co trzymasz), **krok** (co robi jedna runda według reguł) i **warunek końca**. Policz
koszt: liczba kroków × koszt kroku. Jeśli któregoś elementu nie umiesz nazwać, wróć do treści.

## Szablony

```cpp
// grid: 4 and 8 neighbours and one border check
const int dr4[4] = {-1, 1, 0, 0}, dc4[4] = {0, 0, -1, 1};
const int dr8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool inside(int r, int c) { return r >= 0 && r < n && c >= 0 && c < m; }

// simulation skeleton
while (!finished(state)) {
    state = step(state);                       // exactly the rules from the statement
    steps++;
}

// monotone process (things are only added): closure with a queue, order does not matter
queue<pair<int, int>> q;                       // cells that changed
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r + dr4[d], nc = c + dc4[d];
        if (inside(nr, nc) && becomesActive(nr, nc)) { activate(nr, nc); q.push({nr, nc}); }
    }
}

// grouping equal objects: sort and compare neighbours, or count in a map
sort(v.begin(), v.end());
for (size_t i = 0; i < v.size();) {
    size_t j = i;
    while (j < v.size() && v[j] == v[i]) j++;  // v[i..j-1] is one group
    i = j;
}
map<string, int> cnt;
for (auto& s : words) cnt[s]++;

// reading until the end of input and whole lines
string line;
while (getline(cin, line)) { /* one line */ }
```

## Przypadki brzegowe przed wysłaniem

Najmniejsze n; największe wartości (przepełnienie, czas); wszystkie równe, powtórzenia, pusta odpowiedź, `NIE`;
pola przy krawędzi, rogi, oba skosy; wiele zestawów w jednym wejściu (stan z poprzedniego zestawu); format
`TAK`/`NIE` i dowolna poprawna odpowiedź. Pełna lista z diagramem: Dzień 2, sekcja 5.

## Jak naginać

- **Za dużo kroków:** sprawdź, czy proces jest monotoniczny (wtedy wynik nie zależy od kolejności i wystarcza
  domknięcie kolejką, [2024 G Gra MPO](../zadania/2024/g-gra-mpo.md)), czy stany się powtarzają (cykl: zapamiętaj,
  kiedy stan wystąpił, i przeskocz pełne okrążenia) albo czy wiele kroków da się wykonać naraz wzorem.
- **Zadanie odwrotne ("czy ten stan jest osiągalny"):** nie symuluj wszystkich gier, tylko zbierz warunki konieczne
  i zbuduj przykład, że wystarczają ([2022 K Kółko i Krzyżyk](../zadania/2022/k-kolko-i-krzyzyk.md)).
- **Przypadek `NIE`, którego nie ma:** zanim go obsłużysz, zapisz warunki wzorem i uprość
  ([2021 H Hasła](../zadania/2021/h-hasla.md)).
- **Grupuj po tym, co ma być różne:** klucz grupowania to cały obiekt, który nie może się powtórzyć
  ([2022 A Aliasy](../zadania/2022/a-aliasy.md)).
- **Kierunki z treści** ustal raz: wiersz 0 na górze, więc północ to `r - 1`. Pary sąsiadów licz raz (tylko "w przód")
  albo podziel licznik przez 2.

## Zadania z archiwum

Grupy "implementacja" i "symulacja" w [katalogu](../zadania/katalog.md). Sprawdzone w kursie: 2024 G, 2022 A, 2021 H,
2022 K.

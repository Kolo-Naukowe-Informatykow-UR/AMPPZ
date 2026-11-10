# AMPPZ 2017 M - Maksymalna piaskownica

> [!info] Karta zadania
> - Treść: `201X/2017/M/M.pdf` ([PDF na GitHubie](../../../201X/2017/M/M.pdf)); pamięć 64 MB, limitu czasu treść nie
>   podaje.
> - Technika: zliczanie (sortowanie przez zliczanie), przypadki brzegowe. Trudność: 1/5 (rozwiązały 43 z 44 drużyn).
> - Kod: [m-maksymalna-piaskownica.cpp](m-maksymalna-piaskownica.cpp). Złożoność: O(n + 100).
> - Dzień kursu: [Dzień 3](../../dni/03-sortowanie-zachlanne.md), zadanie bez etykiety (technika z Dni 1-2).

## Treść w skrócie

Jest n desek (n ≤ 10⁶) o długościach od 1 do 100. Wybierz cztery, z których da się złożyć prostokąt (deski się nie
łączą i nie wystają), o największym polu. Wypisz pole albo `NIE`.

## Zanim przeczytasz dalej

15 minut. Jakie cztery deski tworzą prostokąt? Co mówi limit długości 100?

> [!tip]- Podpowiedź 1
> Prostokąt to dwie pary równych desek: dwie o długości x i dwie o długości y. Kwadrat (x = y) też się liczy.

> [!tip]- Podpowiedź 2
> Długości jest tylko 100. Policz, ile jest desek każdej długości, i zbierz pary od najdłuższej.

## Droga myślenia

1. **Prostokąt z czterech desek** to dwie pary równych: boki x, x, y, y. Pole x · y jest największe dla dwóch
   najdłuższych par.
2. **Ile par daje długość?** Z c desek tej samej długości jest ⌊c / 2⌋ par. Długość, której jest co najmniej 4, daje
   dwie pary naraz, czyli kwadrat.
3. **Limit długości 100** podpowiada zliczanie zamiast sortowania: tablica `cnt[1..100]`, potem przejście od 100 w dół
   i zbieranie par, aż będą dwie.
4. **Brak dwóch par:** `NIE`.

## Rozwiązanie

```cpp
vector<int> cnt(101, 0);
for (int i = 0; i < n; i++) { int a; cin >> a; cnt[a]++; }

vector<int> sides;                             // pair lengths, longest first
for (int len = 100; len >= 1 && sides.size() < 2; len--)
    for (int p = 0; p < cnt[len] / 2 && sides.size() < 2; p++) sides.push_back(len);

if (sides.size() < 2) cout << "NIE\n";
else cout << sides[0] * sides[1] << "\n";
```

Pełny program: [m-maksymalna-piaskownica.cpp](m-maksymalna-piaskownica.cpp).

## Złożoność i optymalność

- O(n + 100) czasu i O(100) pamięci; nie trzeba trzymać desek. Optymalne, bo każdą deskę trzeba przeczytać.
- Omówienie jury 2017 tego zadania nie omawia (to najłatwiejsze zadanie zestawu). Sortowanie wszystkich desek,
  O(n log n), też by przeszło, ale przy limicie pamięci 64 MB i milionie liczb zliczanie jest pewniejsze.

## Pułapki

- **Kwadrat:** długość występująca 4 razy lub więcej daje obie pary. Rozwiązanie, które bierze z każdej długości
  najwyżej jedną parę, myli się na `5 5 5 5`.
- **Para to dwie deski:** długość występująca 3 razy daje jedną parę, nie dwie.
- **`NIE`:** gdy par jest mniej niż dwie, także gdy desek jest mniej niż 4.
- **Szybkie wejście:** milion liczb.

## Weryfikacja

- Kompilacja `g++ -std=c++17 -O2 -Wall -Wextra` bez ostrzeżeń, przykład z treści poprawny (30).
- 1500 testów losowych (n od 1 do 8, długości do 3, do 6 albo do 100, żeby często powtarzały się 3 i 4 razy),
  porównanych z brute force po wszystkich czwórkach desek. Wszystkie zgodne.
- Test maksymalny: n = 10⁶, 0,22 s.

## Wspólny mianownik

**Mały zakres wartości to tablica liczników.** Gdy wartości są małe (tu 100, w innych zadaniach do 10⁶), zamiast
sortować, zliczasz wystąpienia i przechodzisz po wartościach. Drugi wzorzec to przypadki brzegowe z Dnia 2: element
użyty dwa razy (kwadrat), za mało elementów, odpowiedź `NIE`.

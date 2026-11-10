# Wzorzec: przegląd wszystkich możliwości i zadania na warunki

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: jak z limitów odczytać, czy wolno przejrzeć wszystko, gotowe
> pętle po parach, podzbiorach i permutacjach w C++ oraz jak przegląd obciąć, gdy jest odrobinę za duży. Do tego
> zadania "na warunki", w których trzeba tylko dokładnie sprawdzić definicję obiektu. Teoria: [Dzień 1](../dni/01-start.md)
> (złożoność z limitów, typy, mini-protokół).

## Sygnały

- Małe limity: n ≤ 8-10 (permutacje), n ≤ 20 (podzbiory), n ≤ 50-500 (trzy pętle), plansza do 10 × 10.
- "Wypisz dowolne", "czy istnieje", a możliwych odpowiedzi jest mało.
- Długa historia i krótkie dane: zadanie trywialne, które ukrywa jeden prosty warunek.
- Definicja obiektu w treści (kwadrat, akronim, poprawny stan), a pytanie brzmi "czy dane spełniają definicję".
- Odpowiedź na pewno jest mała (nie więcej niż kilka, kilkadziesiąt), choć dane są duże.

## Budżet z limitów

Ok. 10⁸ prostych operacji na sekundę. n ≤ 10-11: O(n!); n ≤ 20-25: O(2ⁿ · n); n ≤ 300-500: O(n³); n ≤ 5000: O(n²);
n ≤ 10⁶: O(n log n) albo O(n). Pełna tabela: Dzień 1, sekcja 4. Zanim napiszesz przegląd, policz iloczyn: liczba
możliwości razy koszt sprawdzenia jednej.

## Szablony

```cpp
// all pairs and triples: O(n^2), O(n^3)
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        for (int k = j + 1; k < n; k++) { /* check (i, j, k) */ }

// all subsets of n <= 20 elements: bit i of mask says whether element i is taken
for (int mask = 0; mask < (1 << n); mask++) {
    ll sum = 0;
    for (int i = 0; i < n; i++)
        if (mask >> i & 1) sum += a[i];
}

// all orders of n <= 10 elements: start from the sorted order
vector<int> p(n);
iota(p.begin(), p.end(), 0);
do { /* check order p */ } while (next_permutation(p.begin(), p.end()));

// fix one thing, compute the rest: every choice of a block [l, r], then a cheap check
for (int l = 0; l < n; l++)
    for (int r = l; r < n; r++) { /* the rest is easy once [l, r] is fixed */ }

// conditions on a grid: check every cell of the object, and the borders first
bool inside(int r, int c) { return r >= 0 && r < n && c >= 0 && c < m; }
```

## Jak naginać

- **Ustal jedną rzecz i policz resztę.** Gdy przegląd całych odpowiedzi jest za duży, przejrzyj wszystkie możliwości
  jednego fragmentu (gdzie leży blok, jaka jest pierwsza wartość, kto wygrywa), a resztę policz zachłannie albo
  wzorem ([2023 J](../zadania/2023/j-juliet-unifies-ones.md)).
- **Ogranicz odpowiedź prostym rozwiązaniem.** Jeśli proste rozwiązanie zawsze działa i kosztuje X, przeglądasz tylko
  rozwiązania tańsze niż X; z ogromnych limitów robi się kilkadziesiąt przypadków
  ([2022 A Aliasy](../zadania/2022/a-aliasy.md)).
- **Obcinanie:** przerwij gałąź przeglądu, gdy już jest gorsza niż najlepsza znana albo łamie warunek; zacznij od
  kandydatów, które najpewniej dadzą dobry wynik.
- **Przegląd po odpowiedzi zamiast po danych:** gdy możliwych odpowiedzi jest mało (np. 26 liter, 100 długości),
  przejrzyj odpowiedzi i dla każdej sprawdź dane.
- **Warunki obiektu:** wypisz wszystkie warunki z definicji, także ten "oczywisty" (nie przechodzimy przez koniec
  wiersza), i sprawdź każdy osobno ([2024 K Kwadracik](../zadania/2024/k-kwadracik.md)).
- **Dowolna poprawna odpowiedź:** wybierz najprostszą konstrukcję, np. pierwszy pasujący element
  ([2024 A Akronim](../zadania/2024/a-akronim.md)).
- **Brute force jako wyrocznia:** nawet gdy przegląd jest za wolny na pełne dane, napisz go: posłuży do testów
  losowych wolniejszego, sprytnego rozwiązania (Dzień 5).

## Zadania z archiwum

Grupy "implementacja" i "brute force z obcięciem" w [katalogu](../zadania/katalog.md). Sprawdzone w kursie: 2024 A,
2024 K, 2023 J, 2022 A, 2022 K. Przegląd 9! ustawień planszy: 2018 H Hobby z [atlasu sygnałów](../myslenie/sygnaly-w-tresci.md).

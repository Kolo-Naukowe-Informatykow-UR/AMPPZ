# AMPPZ 2017 G - Głowica drukarki

> [!info] Karta zadania
> - Treść: `201X/2017/G/G.pdf` ([PDF na GitHubie](../../../201X/2017/G/G.pdf)); pamięć 64 MB, limitu czasu treść nie
>   podaje.
> - Technika: zachłanne (każdy przebieg jak najdłuższy), przeformułowanie na pozycje kolejnych wysokości. Trudność:
>   1/5 (rozwiązało 39 z 44 drużyn).
> - Kod: [g-glowica-drukarki.cpp](g-glowica-drukarki.cpp). Złożoność: O(n).
> - Dzień kursu: [Dzień 4](../../dni/04-prefiksy-dwa-wskazniki.md), zadanie bez etykiety (technika z Dnia 3).

## Treść w skrócie

Na n polach w rzędzie (n ≤ 10⁶) trzeba wydrukować prostopadłościany o wysokościach 1, 2, ..., n, każdą wysokość na
z góry ustalonym polu (dana jest permutacja). Głowica robi przebiegi w lewo albo w prawo i zatrzymuje się nad
dowolnymi polami; na pierwszym drukuje dowolną wysokość h, na każdym kolejnym o 1 niższą niż poprzednio. Każde pole
drukuje się raz. Ile najmniej przebiegów?

## Zanim przeczytasz dalej

15 minut. Przykład: 3 2 4 1 5 6, odpowiedź 2. Jakie wysokości może wydrukować jeden przebieg i w jakiej kolejności
pól?

> [!tip]- Podpowiedź 1
> Jeden przebieg drukuje kolejne wysokości h, h - 1, h - 2, ..., a ich pola idą w jedną stronę. Wypisz pola wysokości
> n, n - 1, ..., 1 po kolei. Czym jest przebieg w tym ciągu?

> [!tip]- Podpowiedź 2
> Przebieg to spójny kawałek ciągu pól, który jest monotoniczny (rosnący albo malejący). Trzeba pociąć ciąg na jak
> najmniej monotonicznych kawałków. Czy opłaca się kiedykolwiek skończyć kawałek wcześniej, niż trzeba?

## Droga myślenia

1. **Co drukuje przebieg.** Wysokości w przebiegu to h, h - 1, ..., czyli kolejne liczby, a pola idą w jedną stronę.
   Niech pos[h] to pole wysokości h. Przebieg to kawałek ciągu pos[n], pos[n - 1], ..., pos[1] (kolejne wysokości),
   który jest rosnący (przebieg w prawo) albo malejący (w lewo).
2. **Zadanie po przeformułowaniu:** pociąć ten ciąg na najmniej spójnych kawałków monotonicznych.
3. **Zachłannie:** każdy kawałek przedłużaj, dopóki się da. Uzasadnienie (zachłanny jest zawsze krok przed, Dzień 3):
   końcówka kawałka monotonicznego też jest monotoniczna, więc jeśli jakiekolwiek pocięcie kończy k-ty kawałek na
   pozycji p, to zachłanny kończy swój k-ty kawałek na pozycji p albo dalej. Zachłanny nie potrzebuje więc więcej
   kawałków.
4. **Kierunek kawałka** ustala dopiero jego drugi element (dwa elementy są zawsze monotoniczne), więc po cięciu
   kierunek jest znów nieznany.

Sprawdzenie na przykładzie: pola wysokości 6, 5, ..., 1 to 6, 5, 3, 1, 2, 4. Kawałek malejący 6, 5, 3, 1, potem rosnący
2, 4: dwa przebiegi.

## Rozwiązanie

```cpp
vector<int> pos(n + 1);
for (int i = 1; i <= n; i++) { int h; cin >> h; pos[h] = i; }

int passes = 1, dir = 0;                       // dir of the current run: 0 unknown, +1 right, -1 left
for (int h = n - 1; h >= 1; h--) {
    int d = pos[h] > pos[h + 1] ? 1 : -1;
    if (dir == 0) dir = d;                     // second height fixes the direction
    else if (d != dir) passes++, dir = 0;      // h starts a new pass
}
```

Pełny program: [g-glowica-drukarki.cpp](g-glowica-drukarki.cpp).

## Złożoność i optymalność

- O(n) czasu, jedna tablica n liczb (4 MB przy limicie 64 MB). Optymalne, bo trzeba przeczytać permutację.
- Omówienie jury (AMPPZ 2017) formułuje zadanie jako pokrycie permutacji najmniejszą liczbą podciągów monotonicznych
  o różnicy 1 albo -1: dla każdego elementu wylicza przedziały wartości, które pokryje ciąg rosnący i malejący, i wybiera
  zachłannie przedziały (zamiatanie: spośród pokrywających najmniejszą niepokrytą wartość ten, który sięga najdalej).
  To samo rozumowanie; wersja powyżej robi je w jednym przebiegu, bo z każdej wartości jest tylko jeden najdłuższy
  kawałek.

## Pułapki

- **Kierunek po cięciu:** nowy kawałek zaczyna się od jednego elementu i nie ma jeszcze kierunku. Kto po cięciu
  ustawia kierunek ostatniego kroku (od h + 1 do h), wlicza wysokość h + 1 do nowego przebiegu, choć należy ona już
  do poprzedniego. Na 4 2 3 1 (pola wysokości 4, 3, 2, 1 to 1, 3, 2, 4) taki kod daje 3 zamiast 2.
- **n = 1:** jeden przebieg.
- **Wysokości, nie pola:** pętla idzie po wysokościach, więc najpierw odwracamy permutację do tablicy pos.

## Weryfikacja

- Kompilacja `g++ -std=c++17 -O2 -Wall -Wextra` bez ostrzeżeń, oba przykłady z treści poprawne (2 i 3).
- 1500 testów losowych (losowe permutacje, n od 1 do 8), porównanych z brute force, który przeszukuje wszerz zbiory
  wydrukowanych pól, a jako ruch próbuje każdego przebiegu dozwolonego przez treść (dowolny kierunek, dowolne pole
  startowe, dowolny monotoniczny ciąg niezadrukowanych pól o wysokościach h, h - 1, ...). Wszystkie zgodne.
- Testy maksymalne: n = 10⁶, permutacja losowa: 0,26 s; zygzak 2 1 4 3 6 5 ... (500 000 przebiegów): 0,17 s.

## Wspólny mianownik

**Przeformułuj na ciąg i potnij zachłannie.** Gdy operacja obsługuje "kolejne" elementy w jakimś porządku, wypisz je
w tym porządku i sprawdź, jaki warunek musi spełniać kawałek obsłużony jedną operacją. Jeśli warunek jest dziedziczny
(każdy kawałek dobrego kawałka jest dobry), to cięcie na jak najdłuższe kawałki jest optymalne.

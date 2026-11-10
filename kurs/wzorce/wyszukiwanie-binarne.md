# Wzorzec: wyszukiwanie binarne i testowanie z brute force

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać wyszukiwanie binarne w tablicy i po wyniku, gotowe
> szablony w C++ (także na liczbach rzeczywistych) i zestaw do stress testu. Teoria i przykłady:
> [Dzień 5](../dni/05-wyszukiwanie-binarne.md).

## Sygnały

- Posortowane dane i pytania "ile elementów w przedziale", "pierwszy element ≥ x", "najbliższy sąsiad".
- "Największe minimum", "najmniejsze maksimum", "jak najdalej od siebie", "najmniejsze obciążenie".
- "Najmniejszy czas, po którym", "najmniejsza pojemność, przy której", "po której minucie".
- "k-ta najmniejsza wartość" spośród n² albo więcej kandydatów, których nie da się wypisać.
- Wynik do 10⁹-10¹⁸ przy n do 10⁵-10⁶, a sprawdzenie "czy x wystarcza" jest zachłanne i liniowe.
- Wynik rzeczywisty z tolerancją 10⁻⁶-10⁻⁹ i warunek, który da się sprawdzić dla ustalonej wartości.
- Przydział zasobów do żądań: "najmniejszy pasujący" (`multiset::lower_bound`).

## Pięć ruchów

| Ruch | Kiedy | Koszt | Przykład |
|---|---|---|---|
| `lower_bound` i `upper_bound` w tablicy | liczenie w przedziale, pierwszy ≥ x | O(log n) na zapytanie | [2011 E Eksterminacja świstaków](../zadania/2011/e-eksterminacja-swistakow.md) |
| `lower_bound` w `set` / `multiset` | najmniejszy pasujący przy usuwaniu, sąsiedzi po zmianie | O(log n) | [2011 F Frania](../zadania/2011/f-frania.md) |
| Po wyniku, liczby całkowite | ok(x) monotoniczne, sprawdzenie zachłanne | log(zakres) · koszt ok | [2017 L Leśny kemping](../zadania/2017/l-lesny-kemping.md) |
| Po wyniku, liczby rzeczywiste | wynik z tolerancją | 100 kroków · koszt ok | [2013 A Autostrada](../zadania/2013/a-autostrada.md) |
| Stress test | WA bez pomysłu, zachłanność bez dowodu | 10-15 minut | [2011 F Frania](../zadania/2011/f-frania.md) |

## Szablony

```cpp
// first index with a[i] >= x (n if none); invariant: false at lo, true at hi
int lo = -1, hi = n;
while (hi - lo > 1) {
    int mid = lo + (hi - lo) / 2;
    if (a[mid] >= x) hi = mid; else lo = mid;
}

// values in [l, r] of a sorted vector
auto cnt = upper_bound(a.begin(), a.end(), r) - lower_bound(a.begin(), a.end(), l);

// smallest free resource with at least need; erase one copy by iterator
auto it = ms.lower_bound(need);
if (it != ms.end()) ms.erase(it);

// binary search on the answer: smallest x with ok(x)
ll lo = MIN - 1, hi = MAX;                     // ok(lo) false, ok(hi) true for sure
while (hi - lo > 1) {
    ll mid = lo + (hi - lo) / 2;
    if (ok(mid)) hi = mid; else lo = mid;
}

// reals: fixed number of steps, long double
long double L = 0, R = 1e9;
for (int it = 0; it < 100; it++) {
    long double M = (L + R) / 2;
    if (ok(M)) R = M; else L = M;
}
```

Stress test (bash, generator dostaje numer testu jako ziarno):

```bash
for i in $(seq 1 2000); do
    ./gen $i > in.txt; ./sol < in.txt > o1.txt; ./brute < in.txt > o2.txt
    if ! cmp -s o1.txt o2.txt; then echo "test $i"; cat in.txt; break; fi
done
```

## Jak naginać

- **Najpierw monotoniczność.** Powiedz jednym zdaniem, dlaczego ok(x) ⇒ ok(x + 1). Gdy warunek "da się" jest prawdziwy
  tylko w środku, rozdziel go na ograniczenia dolne i górne (każda rodzina monotoniczna) albo znajdź punkt w środku
  i szukaj binarnie w obie strony.
- **Sprawdzenie zwykle jest zachłanne.** Największe minimum odległości: bierz najbliższy dopuszczalny punkt. Najmniejsze
  maksimum sumy: dokładaj do kawałka, póki się mieści. Najmniejszy czas: policz, ile się zdąży.
- **Okrąg:** zgadnij wybrany element o najmniejszym numerze i rozetnij okrąg; skoki "do najbliższego dopuszczalnego"
  liczysz dla wszystkich startów naraz dwoma wskaźnikami, a liczbę skoków i punkt końcowy od prawej.
- **Zmiany w czasie:** przy wstawianiu i usuwaniu elementów licz tylko różnicę; z `set` bierzesz dwóch sąsiadów, którzy
  jako jedyni wpływają na zmianę.
- **k-ta wartość:** ok(x) = "co najmniej k kandydatów ≤ x"; liczenie kandydatów ≤ x zwykle robią dwa wskaźniki albo
  `upper_bound` dla każdego wiersza.
- **Granice i przepełnienia:** górna granica musi na pewno spełniać ok; w ok przerywaj sumowanie po przekroczeniu celu;
  mid = lo + (hi - lo) / 2.
- **Liczby rzeczywiste:** przesuń dane, żeby wartości były małe (odejmij pierwszy element), licz na `long double`,
  wypisuj z rzutowaniem na `double` (`%Lf` w MinGW nie działa).
- **Brute force wprost z treści,** na małych danych, z wartościami brzegowymi; przy wielu poprawnych odpowiedziach
  sprawdzarka zamiast porównania napisów.

## Zadania z archiwum

Grupa "wyszukiwanie binarne" w [katalogu](../zadania/katalog.md) oraz zadania z nim jako techniką poboczną.
Sprawdzone w kursie: 2017 L, 2011 E, 2011 F, 2013 A. Na później: 2024 C Cierpliwe krowy (wyszukiwanie binarne po
czasie; bez omówienia jury, sprawdzenie dla ustalonego czasu nie zostało jeszcze opracowane), 2023 G Game of Geniuses (teoria gier, Dzień 17),
2018 B Bony Fibonacciego (5 z 51 drużyn, matematyka i DP), 2021 G Glątwa Gebajta (2 z 45, struktury danych).

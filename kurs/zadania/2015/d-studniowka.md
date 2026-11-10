# AMPPZ 2015 D - Studniówka

> [!info] Karta zadania
> - Treść: `201X/2015/D/D.pdf` ([PDF na GitHubie](../../../201X/2015/D/D.pdf)); pamięć 128 MB, limitu czasu treść nie
>   podaje.
> - Technika: sortowanie, dwa wskaźniki (okno, które przesuwa się tylko w prawo). Trudność: 1/5 (rankingu 2015 nie
>   ma; według omówienia jury 47 zaakceptowanych zgłoszeń, a także 75 błędnych odpowiedzi i 63 przekroczenia czasu).
> - Kod: [d-studniowka.cpp](d-studniowka.cpp). Złożoność: O((n + m) log(n + m)).
> - Dzień kursu: [Dzień 4](../../dni/04-prefiksy-dwa-wskazniki.md), zadanie omówione.

## Treść w skrócie

Jest n dziewcząt i m chłopców (n, m ≤ 250 000) o wzrostach od 1 do 10⁹. Para dziewczyna i chłopak może otwierać
poloneza, gdy ich wzrosty różnią się najwyżej o k (0 ≤ k ≤ 10⁹). Ile jest takich par? Liczą się osoby, nie wzrosty:
dwóch chłopców o tym samym wzroście daje dwie różne pary.

## Zanim przeczytasz dalej

15 minut. Ile par trzeba by sprawdzić, przeglądając wszystkie? Jak duża może być odpowiedź i jaki typ ją zmieści?

> [!tip]- Podpowiedź 1
> Wszystkich par jest do 250 000 · 250 000 = 6,25 · 10¹⁰: za dużo, żeby sprawdzić każdą, i za dużo dla `int`.
> Dla jednej dziewczyny o wzroście a pasują chłopcy o wzroście z przedziału [a - k, a + k]. Jak ich szybko policzyć?

> [!tip]- Podpowiedź 2
> Posortuj chłopców. Pasujący chłopcy tworzą wtedy spójny kawałek tablicy. Co się dzieje z tym kawałkiem, gdy
> przechodzisz do wyższej dziewczyny?

## Droga myślenia

1. **Limity.** Brute force po parach to n · m = 6,25 · 10¹⁰ porównań, czyli minuty, nie sekundy. Potrzebne jest
   O((n + m) log(n + m)) albo lepiej.
2. **Jedna dziewczyna.** Warunek |a - b| ≤ k to a - k ≤ b ≤ a + k. Po posortowaniu chłopców ci, którzy pasują, stoją
   obok siebie: od pierwszego o wzroście co najmniej a - k do ostatniego o wzroście co najwyżej a + k. Ich liczbę
   dają dwa wyszukiwania binarne (`lower_bound`, `upper_bound`) w O(log m).
3. **Wszystkie dziewczyny po kolei.** Gdy posortujesz także dziewczyny, obie granice przedziału [a - k, a + k] rosną
   razem z a. Lewy wskaźnik `lo` (pierwszy chłopiec, który nie jest za niski) i prawy `hi` (pierwszy, który jest za
   wysoki) przesuwają się więc tylko w prawo. Każdy przesuwa się łącznie najwyżej m razy, więc po sortowaniu cały
   przebieg kosztuje O(n + m).
4. **Wynik:** suma `hi - lo` po wszystkich dziewczynach, w `long long`.

```mermaid
flowchart LR
    A["Sort girls and boys"] --> B["Take the next girl, height a"]
    B --> C["Move lo right while boy lo is shorter than a - k"]
    C --> D["Move hi right while boy hi is at most a + k"]
    D --> E["Add hi - lo pairs"]
    E --> B
```

Jak czytać diagram: to pętla dwóch wskaźników. Dla każdej kolejnej (wyższej) dziewczyny oba wskaźniki tylko
doganiają nowy przedział; żaden się nie cofa. Chłopcy na pozycjach od `lo` do `hi - 1` pasują do bieżącej dziewczyny.

Przykład: dziewczęta 1, 5, 7, 15, chłopcy 1, 1, 5, 10, 15, k = 5. Dla 1: przedział [-4, 6], chłopcy 1, 1, 5 (3 pary).
Dla 5: [0, 10], chłopcy 1, 1, 5, 10 (4). Dla 7: [2, 12], chłopcy 5, 10 (2). Dla 15: [10, 20], chłopcy 10, 15 (2).
Razem 11, zgodnie z treścią.

## Rozwiązanie

```cpp
sort(a.begin(), a.end());
sort(b.begin(), b.end());

ll pairs = 0;
int lo = 0, hi = 0;                            // boys in [lo, hi) fit the current girl
for (int i = 0; i < n; i++) {
    while (lo < m && b[lo] < a[i] - k) lo++;   // too short for this girl and every next one
    while (hi < m && b[hi] <= a[i] + k) hi++;  // tall enough to fit
    pairs += hi - lo;
}
```

Pełny program: [d-studniowka.cpp](d-studniowka.cpp). Wariant z wyszukiwaniem binarnym zamiast pętli: `pairs +=
upper_bound(b.begin(), b.end(), a[i] + k) - lower_bound(b.begin(), b.end(), a[i] - k);`, wtedy dziewcząt nie trzeba
sortować.

## Złożoność i optymalność

- Sortowanie O(n log n + m log m), potem dwa wskaźniki O(n + m). Wersja z wyszukiwaniem binarnym ma tę samą złożoność
  całkowitą, O(m log m + n log m).
- Wzrosty do 10⁹, więc sortowanie przez zliczanie odpada. Szybciej niż O(n log n) w modelu porównań się nie da: przy
  k = 0 zadanie rozstrzyga, czy zbiory wzrostów dziewcząt i chłopców mają wspólny element, a to wymaga Ω(n log n)
  porównań. Przy n = m = 250 000 program działa 0,14 s.
- Omówienie jury (AMPPZ 2015): to samo rozwiązanie, posortowane obie tablice i dwa wskaźniki przesuwane tylko w prawo,
  z uwagą, że wystarczą też dwa wyszukiwania binarne.

## Pułapki

- **Przepełnienie wyniku:** do 6,25 · 10¹⁰ par, czyli `long long`.
- **Przepełnienie granicy:** a + k sięga 2 · 10⁹, a `int` kończy się na ok. 2,147 · 10⁹. Tu akurat by się zmieściło,
  ale wystarczy, że ktoś liczy a + k + 1, i wynik jest zły. Najprościej trzymać wzrosty w `long long`.
- **k = 0:** pasują tylko równe wzrosty; warunek musi być nieostry (≤ k, nie < k).
- **Powtórzone wzrosty:** liczysz osoby, nie różne wartości; nie usuwaj duplikatów.
- **75 błędnych odpowiedzi i 63 przekroczenia czasu** w statystykach jury to właśnie te dwie pułapki: `int` i pętla
  po wszystkich parach.

## Weryfikacja

- Kompilacja `g++ -std=c++17 -O2 -Wall -Wextra` bez ostrzeżeń, przykład z treści poprawny (11).
- 1500 testów losowych (n, m od 1 do 8, wzrosty do 5, do 12 albo do 10⁹, często skrajne 1 i 10⁹, k od 0 do 10⁹),
  porównanych z brute force po wszystkich parach. Wszystkie zgodne.
- Test maksymalny: n = m = 250 000, k = 10⁹ (każda para pasuje, wynik 62 500 000 000): 0,14 s.

## Wspólny mianownik

**Licz pary przez okno w posortowanej tablicy.** Gdy pytanie brzmi "ile par spełnia warunek na różnicę", posortuj
i dla każdego elementu policz partnerów w przedziale wartości. Przedział przesuwa się w jedną stronę, więc dwa
wskaźniki dają O(n). Ten sam ruch rozwiązuje CSES Sum of Two Values i wszystkie zadania "ile par różni się najwyżej
o k".

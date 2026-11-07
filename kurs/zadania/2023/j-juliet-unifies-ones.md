# AMPPZ 2023 J - Juliet Unifies Ones

> [!info] Karta zadania
> - Treść (po angielsku): `202X/2023/J/J.pdf` ([PDF na GitHubie](../../../202X/2023/J/J.pdf)).
> - Technika: przegląd wszystkich możliwości (brute force), bo limity są malutkie. Trudność: 1/5.
> - Kod: [j-juliet-unifies-ones.cpp](j-juliet-unifies-ones.cpp) (O(n³)) i dla ciekawych
>   [j-juliet-unifies-ones-dp.cpp](j-juliet-unifies-ones-dp.cpp) (O(n)).
> - Dzień kursu: [Dzień 1](../../dni/01-start.md), ćwiczenie do samodzielnego rozwiązania.

## Treść w skrócie

Napis z zer i jedynek jest "zunifikowany", gdy wszystkie jedynki tworzą jeden spójny blok (może być pusty), np.
`0011110`, `1`, `0000`. Z danego napisu S (długość do 50) usuwamy znaki. Ile najmniej znaków trzeba usunąć, żeby
to, co zostanie, było zunifikowane? Przykład: `00011011001` daje 2.

## Zanim przeczytasz dalej

To ćwiczenie: rozwiąż samodzielnie (20 minut), napisz kod, sprawdź na przykładzie. Dopiero potem otwieraj
podpowiedzi albo rozwiązanie.

> [!tip]- Podpowiedź 1
> Spójrz na limit: |S| ≤ 50. Ile operacji możesz sobie pozwolić? Czy da się sprawdzić "wszystkie możliwe
> miejsca bloku jedynek"?

> [!tip]- Podpowiedź 2
> Wynik ma postać: zera, blok jedynek, zera. Wybierz przedział pozycji [l, r) w oryginalnym napisie, w którym
> będzie leżał blok. Co musisz usunąć wewnątrz przedziału, a co poza nim?

> [!tip]- Podpowiedź 3
> Wewnątrz przedziału usuwasz każde 0, poza nim każdą 1. Koszt dla przedziału to liczba takich znaków.
> Sprawdź wszystkie przedziały (także pusty) i weź minimum.

> [!success]- Rozwiązanie
> Dla każdego przedziału [l, r) (0 ≤ l ≤ r ≤ n) liczymy koszt: zera wewnątrz plus jedynki na zewnątrz.
> Przedziałów jest około n²/2 = 1275, każdy liczymy w O(n), razem około 64 000 operacji. Przedział pusty
> (l = r) oznacza "usuń wszystkie jedynki".
>
> ```cpp
> int best = INT_MAX;
> for (int l = 0; l <= n; l++)
>     for (int r = l; r <= n; r++) {
>         int cost = 0;
>         for (int i = 0; i < n; i++) {
>             bool inside = (l <= i && i < r);
>             if (inside && s[i] == '0') cost++;   // a zero inside the block must go
>             if (!inside && s[i] == '1') cost++;  // a one outside the block must go
>         }
>         best = min(best, cost);
>     }
> cout << best << "\n";
> ```
>
> Dlaczego to poprawne: każdy zunifikowany wynik wyznacza przedział od pierwszej do ostatniej zachowanej
> jedynki w oryginale; usunięcia muszą objąć co najmniej zera wewnątrz i jedynki na zewnątrz, a to wystarcza.
> Przeglądamy wszystkie przedziały, więc trafiamy też na najlepszy.

> [!example]- Dla ciekawych: O(n) programowaniem dynamicznym
> Idziemy po napisie i pamiętamy, w której fazie jesteśmy: 0 = przed blokiem jedynek, 1 = w bloku, 2 = po
> bloku. Każdy znak albo usuwamy (koszt 1, faza bez zmian), albo zostawiamy: zostawione 0 w fazie 1 kończy
> blok (faza 2), zostawiona 1 w fazie 0 zaczyna blok, a zostawiona 1 w fazie 2 jest zabroniona.
> `dp[faza]` = najmniejszy koszt dotąd. To pierwsza zapowiedź programowania dynamicznego z Dnia 10:
> **stan** (faza) i **przejście** (usuń albo zostaw). Kod: [j-juliet-unifies-ones-dp.cpp](j-juliet-unifies-ones-dp.cpp).
> Przy n ≤ 50 nie ma to znaczenia na zawodach: piszesz wersję prostszą.

## Weryfikacja

- Obie wersje skompilowane bez ostrzeżeń, przykład z treści daje 2.
- 1500 losowych napisów długości 1-13 porównanych z rozwiązaniem siłowym, które sprawdza wszystkie 2^n
  podzbiory zachowanych znaków: obie wersje zgodne zawsze.
- Porównanie ze źródłami: oficjalnego omówienia AMPPZ 2023 nie znalazłem (research z 2026-11-07); zadanie
  jest na sędzi QOJ (https://qoj.ac/category/194, wymaga konta). Optymalność: przy n ≤ 50
  liczy się tylko to, żeby zmieścić się w limicie, a O(n) z wersji DP to dolne ograniczenie (trzeba przeczytać
  napis).

## Wspólny mianownik

**Małe limity to zaproszenie do brute force.** n ≤ 50 oznacza, że nie trzeba żadnego sprytu. Typowy błąd
początkującego to szukanie eleganckiego wzoru przez pół godziny, gdy prosta potrójna pętla wchodzi
w milisekundę. Drugi wzór: **ustal jedną rzecz (tu: gdzie leży blok) i policz resztę**. Ten ruch wraca w
setkach zadań: "zgadnij" fragment odpowiedzi, przejrzyj wszystkie możliwości tego fragmentu, a dla każdej
reszta jest łatwa.

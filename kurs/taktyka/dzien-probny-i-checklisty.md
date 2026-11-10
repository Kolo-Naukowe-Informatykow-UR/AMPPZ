# Dzień próbny i checklisty

> [!abstract] W skrócie
> Sesja próbna dzień przed zawodami to jedyna okazja, żeby bez kary sprawdzić środowisko: edytor, kompilator i flagi,
> szybkość sędziego, rozmiar stosu, werdykty, drukowanie i pytania do jury. Do tego trzy checklisty: wieczór przed
> zawodami, start zawodów (karta na biurko) i ostatnia godzina.

## Sesja próbna

**Intuicja.** Na zawodach nie chcesz odkryć, że edytor wcina tabulatorami, `bits/stdc++.h` nie działa albo rekurencja
głębokości 10⁵ kończy się błędem. Sesja próbna to test generalny: zadania są łatwe, a liczy się sprawdzenie wszystkiego,
co może zaskoczyć.

**Co sprawdzić (po kolei):**

- [ ] Logowanie, układ klawiatury (gdzie są `{`, `|`, `~`), edytor: wcięcia spacjami, numery linii, podświetlanie.
- [ ] Szablon ([szablony/szablon.cpp](../szablony/szablon.cpp)) wpisany z pamięci i skrypt kompilacji, na przykład
  `g++ -std=c++17 -O2 -Wall -Wextra -o a a.cpp` (albo flagi z regulaminu, w 2022 `-O3 -static`); `g++ --version`.
- [ ] Zadanie próbne rozwiązane i zaakceptowane: wiecie, jak wysłać i gdzie widać werdykt.
- [ ] Celowo zły wynik (WA), pętla nieskończona (TLE) i wyjście poza tablicę albo dzielenie przez zero (RTE): jak
  wyglądają werdykty i ile się na nie czeka.
- [ ] Szybkość sędziego: program z pętlą 10⁸ i 10⁹ prostych operacji wysłany jako rozwiązanie próbne (czas w werdykcie
  albo TLE mówi, ile mieści się w sekundzie).
- [ ] Stos: rekurencja głębokości 10⁶ (na przykład DFS po ścieżce). Jeśli kończy się błędem, na zawodach głębokie DFS
  piszecie pętlą.
- [ ] Wydruk kodu: jak zlecić, gdzie odebrać, ile trwa.
- [ ] Pytanie do jury przez system: jak zadać i gdzie widać odpowiedź.
- [ ] Ranking: gdzie go widać i jak się odświeża.
- [ ] Raz przećwiczona zmiana przy komputerze i podział czytania.

> [!question] Do sprawdzenia w regulaminie 2026
> Czy jest sesja próbna i jak długa (w 2022 cały pierwszy dzień, w eliminacjach UJ 30 minut), system sprawdzający,
> flagi kompilacji, czy wolno wnosić wydruki (biblioteczka kursu, S10) i ile stron.

## Wieczór przed zawodami

- [ ] Sen: 7-8 godzin. Zmęczenie kosztuje więcej niż ostatnie dwie godziny nauki.
- [ ] Dokumenty: legitymacja studencka, dokument tożsamości, zaświadczenie z uczelni (w 2022 wymagane przy wejściu).
- [ ] Wydruki, jeśli regulamin pozwala: biblioteczka, karty wzorców, ta checklista, tablica zadań.
- [ ] Długopisy, kilka czystych kartek (organizator zwykle daje papier, ale nie zawsze), zegarek bez funkcji
  elektronicznych tylko jeśli dozwolony.
- [ ] Woda, coś do jedzenia, jeśli wolno wnosić.
- [ ] Ustalone role na start: kto pierwszy przy komputerze, kto czyta od początku, kto od końca, kto koordynuje.

## Karta na biurko

Wydrukuj i połóż obok klawiatury.

> [!example] Start
> 1. Kierowca: szablon, skrypt kompilacji, test na przykładzie.
> 2. Czytanie: B od pierwszego zadania w górę, C od ostatniego w dół, A środek po szablonie; 2-3 minuty na zadanie,
>    ocena T/Z/N w tablicy.
> 3. Pierwsze T od razu na komputer, plan powiedziany w 30 sekund.
> 4. 0:15-0:30: ranking; zadania z wieloma AC czytamy jeszcze raz.
> 5. 0:30: wszystko przeczytane, kolejka ustalona.

> [!example] Przed każdym zgłoszeniem
> Przykłady przez `diff`; n = 1; największe dane (czas, typy); format wyjścia; zerowanie przy wielu testach; brak
> wypisywania pomocniczego; właściwe zadanie w systemie.

> [!example] Po odrzuceniu
> Wydruk, komputer dla następnej osoby. WA: treść jeszcze raz, brzegi, przepełnienie, format. TLE: operacje, wejście,
> pętla nieskończona. RTE: indeksy, rekurencja, zero, pamięć. Po 10-15 minutach bez przyczyny: stress test.
> Ponowne zgłoszenie tylko ze znalezioną przyczyną.

> [!example] Ostatnia godzina
> 4:00: wybieramy 1-2 zadania do dokończenia, nic nowego i trudnego. 4:45: wysyłamy wszystko, co się kompiluje
> i przechodzi przykłady. Ostatnie 2-3 minuty: żadnych nowych poprawek.

## Po zawodach

Retrospektywa ([szablon](retrospektywa.md)) jeszcze tego samego dnia, póki pamiętacie, dlaczego podjęliście
decyzje. Najcenniejsze są decyzje, które były złe mimo dobrych intencji: one zmieniają zasady drużyny.

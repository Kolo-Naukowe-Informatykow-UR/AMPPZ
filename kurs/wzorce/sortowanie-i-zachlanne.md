# Wzorzec: sortowanie i algorytmy zachłanne

> [!abstract] W skrócie
> Karta do szybkiego sięgnięcia w trakcie zadania: po czym poznać, który schemat zachłanny pasuje, gotowy szablon
> w C++ i jak schemat nagiąć do nietypowej treści. Teoria i dowody: [Dzień 3](../dni/03-sortowanie-zachlanne.md).

## Sygnały

- Wybór podzbioru albo kolejności, a liczba możliwości (2ⁿ, n!) jest astronomiczna przy n do 10⁵-10⁶.
- Przedziały, spotkania, terminy, "nie nachodzą na siebie", "zdąży przed".
- "Najmniej zmian, żeby nigdzie nie było ...", "najmniej punktów, które trafią ...".
- Zasób, który rośnie po każdym wyborze ("statki", "siła", "pieniądze"), i pytanie o najmniej kroków.
- Warunek typu "największy element mniejszy niż suma pozostałych".

## Pięć schematów

| Schemat | Reguła | Dowód | Przykład |
|---|---|---|---|
| Skrajne elementy | rozwiązanie istnieje, gdy istnieje z elementów skrajnych | podmień elementy dowolnego rozwiązania na skrajne | [2014 A Adwokat](../zadania/2014/a-adwokat.md) |
| Najwcześniejszy koniec | sortuj po końcu, bierz każdy przedział zgodny z ostatnim | zamiana pierwszego wyboru | CSES Movie Festival |
| Najwcześniejszy termin | sortuj po terminie, wykonuj po kolei | zamiana sąsiadów | [2012 J Jutro](../zadania/2012/j-jutro.md) |
| Przebicie przedziałów | prawy koniec pierwszego nietrafionego przedziału | przesunięcie punktu w prawo | [2022 C Ctrl+C Ctrl+V](../zadania/2022/c-ctrl-c-ctrl-v.md) |
| Największy dostępny | kopiec dostępnych, bierz największy | zamiana z późniejszym wyborem | [2019 A Asymilacja](../zadania/2019/a-asymilacja.md) |

Odwrotność skrajnego elementu, "wyrzuć skrajny, który na pewno nie pasuje": [2019 C Koło (z)
Matematyków](../zadania/2019/c-kolo-z-matematykow.md).

## Szablony

```cpp
// earliest end: maximum number of disjoint intervals [l, r]
sort(iv.begin(), iv.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
    return x.second < y.second;
});
int cnt = 0, lastEnd = INT_MIN;
for (auto [l, r] : iv)
    if (l > lastEnd) cnt++, lastEnd = r;           // use l >= lastEnd if touching is allowed

// stabbing: minimum points hitting every interval
sort(iv.begin(), iv.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
    return x.second < y.second;
});
int points = 0, last = INT_MIN;
for (auto [l, r] : iv)
    if (l > last) points++, last = r;              // put a point at the right end

// largest available while the resource grows
sort(a.begin(), a.end());
priority_queue<ll> avail;
int next = 0, steps = 0;
while (have < need) {
    while (next < n && a[next] <= have) avail.push(a[next++]);
    if (avail.empty()) { steps = -1; break; }
    have += avail.top(); avail.pop(); steps++;
}
```

Zauważ, że najwcześniejszy koniec i przebicie przedziałów to ten sam kod: liczba rozłącznych przedziałów wybranych
zachłannie jest równa najmniejszej liczbie punktów trafiających wszystkie przedziały.

## Jak naginać

- **Kryterium porównania nie jest oczywiste:** porównaj dwa sąsiednie elementy w obu kolejnościach i wypisz, kiedy
  pierwsza jest lepsza. Wychodzi warunek, który staje się komparatorem (np. a.x · b.y < b.x · a.y przy proporcjach).
- **Nierówności ścisłe i nieostre:** "ściśle po", "nie na styk" zmienia `>` na `>=` w jednym miejscu. Zanim
  wyślesz, sprawdź przypadek styku końca z początkiem.
- **Kilka niezależnych grup** (dni, kolory, klasy reszt): rozwiązanie zachłanne dla każdej grupy osobno, w jednym
  przebiegu z tablicą stanów grup.
- **Zachłanne z poprawką:** wybierz najlepiej w każdej grupie, a potem napraw jeden globalny warunek (np. parzystość
  liczby wyborów) najtańszą zmianą. Przykład: 2012 C Ciąg z [atlasu sygnałów](../myslenie/sygnaly-w-tresci.md).
- **Nie umiesz udowodnić:** brute force na wszystkich małych danych i porównanie (Dzień 5). Kontrprzykład zwykle
  pojawia się przy n ≤ 5.

## Zadania z archiwum

Grupy "sortowanie" i "zachłanne" w [katalogu](../zadania/katalog.md). Łatwe i sprawdzone w kursie: 2014 A, 2012 J,
2022 C, 2019 C, 2019 A. Na później (trudność 3 według rankingu): 2018 K Kieszonkowe, 2017 H Hasła, 2012 C Ciąg,
2011 F Frania.

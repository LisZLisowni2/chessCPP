# Szachy

Szachy to strategiczna gra planszowa grana przez dwóch graczy na 64 polowej szachownicy przy pomocy bierek.
Bierki to figury oraz pionki, którymi gracze posługują się. Każda bierka ma swój sposób poruszania się, jej ilość na planszy na starcie oraz wartość punktową.
| Bierka  | Opis | Liczba na starcie | Uwagi | Wartość punktowa |
| --- | --- | --- | --- | --- | 
| Pionek (Pawn) | najsłabsza jednostka, mogąca poruszać się tylko o 1 pole do przodu. Jak dojdzie do końca (czyli do linii 1 lub 8) może zamienić się na dowolną figurę. | 8 | Może w pierwszym ruchu ruszyć się o 2 pola | 1 |
| Goniec (Bishop) | figura poruszająca się po skosie, tylko i wyłączenie | 2 | Zawsze jest tylko w danym kolorze | 3 |
| Skoczek (Knight) | figura poruszająca się w sposób przypominający literę L | 2 | Jako jedyna figura może przeskakiwać nad innymi | 3 |
| Wieża (Rook) | figura poruszająca się poziomo i pionowa, nie po skosie | 2 | Nie może przeskakiwać nad innymi bierkami | 5 |
| Hetman (Queen) | najmocniejsza figura, poruszająca się po każdej osi, pionowo i poziomo | 1 | Łączy cechy gońca i wieży | 9 |
| Król (King) | figura poruszająca się o jedno pole w każdą stronę, w tym po osi | 1 | Nie może wejść pod bicie | Nie ma wartości punktowej |

## Zasady gry

### Początkowe rozstawienie

![Początkowe rozstawienie](https://chessforkids.pl/wp-content/uploads/2025/10/1-1.png)

### Ogólne zasady

Celem każdego z graczy jest uniemożliwienie królowi przeciwnika jakiekolwiek ruchu, który nie groziłby mu zbiciem, tzw.. mat. Jeśli gracz nie ma żadnego legalnego ruchu, a jego król nie może wykonać ruchu, który nie groziłby zbiciem, wtedy mamy remis, tzw.. pat.
Grę zaczyna biały i wykonuje swój legalny ruch. Legalny ruch to taki, który:
- bierki poruszają się zgodnie z zasadami oraz nie łamią fundamentalnych założeń gry
- nie może bić własnych bierek
- król nie może znaleźć się pod szachem, czyli w sytuacji, gdy jest atakowany przez przeciwną figurę

Po turze białego gracza, swoją turę zaczyna czarny i tak na zmianę. Gra toczy się do momentu mata, pata albo sytuacji, w której niemożliwe jest zamatowanie przeciwnika.

### Specjalne zasady
- Roszada: Jeśli król nie wykonał jeszcze żadnego ruchu oraz żadna przeciwna figura nie obejmuje swoim zasięgiem drogi do wieży, może wykonać specjalny ruch zwany Roszadą, który polega na ruchu 2 pola w kierunku wieży oraz umieszczenie za królem 

Roszada krótka:

![Roszada krótka](https://upload.wikimedia.org/wikipedia/commons/0/04/SCD_castle_kingside.png)

Roszada długa:

![Roszada długa](https://upload.wikimedia.org/wikipedia/commons/0/03/SCD_castle_queenside.png)

- En passant (Bicie w przelocie): Specjalny ruch pionka, który pozwala mu zbić pionka przeciwnka, jeśli przeciwny ruszył się o dwa pola, a pionek sojuszniczy znajduje się na linii 4 lub 5.

![En passant](https://upload.wikimedia.org/wikipedia/commons/a/ae/Ajedrez_captura_al_paso_del_peon.png)

![Gif bicia w przelocie](https://www.coolmathgames.com/sites/default/files/inline-images/What%20is%20en%20passant%20Gameplay.gif)

- Przemiana: Jeśli pionek dojdzie do pola przemiany, czyli linii 8 lub 1, wtedy można ją zamienić na dowolną figurę.

## Działanie programu

### Ogólne

Program zostanie napisany w C++, na początku wygeneruje planszę oraz przy pomocy wielkości znaków oznaczy, które bierki są czyje. Po przygotowaniu gry, gracze wykonają swoją turę, a ona będzie rejestrowana przy pomocy notacji szachowej. Przed każdym ruchem będzie sprawdzane, czy ten ruch jest legalny i jeśli nie, wystosuje odpowiedni komunikat. Sprawdzany również będzie, czy jest szach, czy jest mat, czy jest pat.

### Wymagania i funkcjonalności

- Modułowy program, aby łatwo dokładać kolejne części
- Generowanie planszy 8x8 oraz aktualizowanie jej w toku gry
- Wykonywanie legalne ruchu przez gracza
- Sprawdzanie, czy król gracza jest pod szachem.
- Sprawdzanie, czy król gracza jeszcze istnieje.
- Wyświetlanie stosownego komunikatu po grze
- Obsługa gry przy pomocy klawiatury, aby nie musieć uczyć się notacji szachowej
- Czytelny i estetyczny kod
- Znaczące nazewnictwo zmiennych i stałych w języku angielskim
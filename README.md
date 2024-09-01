# Proiectarea algoritmilor

Student: Andronache Madalina-Georgiana
Grupa: 322CC

Urmatorul fisier contine informatii despre rezolvarea problemelor propuse in 
tema 1 de la PA.

Cea mai mare provocare intalnita a fost rezolvarea corecta si cat mai eficienta
a problemei propuse intr-un timp cat mai scurt. Aceasta tema a fost rezolvata
pe parcursul a 15 zile: in total am lucrat la aceasta tema 30 h, dintre care 2 h
fiind necesare pentru scrierea fisierului README, iar restul pentru codarea si 
testarea problemelor. In viitor, imi doresc rezolvarea mai rapida a cerintelor. 

Cuprins:
1. Alimentare Servere
2. Colorare
3. Compresie
4. Criptat
5. Oferta

# 1. Alimentare Servere

Am considerar rezolvarea problemei utilizand tehnica de cautarea binara 
pentru a găsi valoarea optima a unei puterii de calcul ce poate fi atinsa.

Ne dorim ca: `Pi - Y >= X` <=> `Pi - X >= Y` <=> `Y <= Pi - X` <=>
`|T - Ci| <= Pi - X` <=> `-(Pi - X) <= T - Ci <= Pi - X` <=>
`- Pi + X <= T - Ci <= Pi - X` <=> `X - Pi + Ci <= T <= Pi - X + Ci` <=>
Deci, pentru fiecare server i, unde i este cuprins intre 1 si n (numarul
de servere), am avea nevoie de o cantitate de curent in intervalul 
[X - Pi + Ci, Pi - X + Ci]. 

Cautam binar in intervalul `left = 1LL * INT32_MIN * 10LL` si 
`right = minimul puterilor pi` (deoarece ne dorim ca mereu Pi >= X). X este 
mijlocul intervalului determinat de left si right, `mid = (left + right) / 2`,
si `actual_mid = (long double) mid / (long double) 10` si apoi verificam 
daca exista cel putin un punct in care toate aceste intervale sa se suprapuna.
Ulterior, ajustam limitele cautarii binare, daca gasim, actualizam raspunsul 
`ans`si `left = mid + 1` (poate gasim un raspuns mai bun), 
altfel `right = mid - 1`.

Pentru precizie, inmultim rezultatul cu 10. La final afisam rezultatul cu exact
2 zecimale. Am incercam sa calculez simplu mijlocul, insa precizia nu era 
suficient de buna, intrucat a fost nevoie de acest artificiu de calcul.

Complexitatea este:
* *Complexitate temporala*: O(n log m) - `n` reprezinta numarul de servere, 
pentru ca pentru fiecare server se caluleaza si actualizeaza limitele 
intervalului, incercand sa gasim punctul sau punctele in care toate 
intervalele se suprapun, iar `m` reprezinta valoarea initiala a variabilei 
`right`, deci minimul puterilor Pi, deci algoritmul de cautare binara va 
face O(log m) pasi pentru determinarea valorii cautate. 
* *Complexitate spatiala*: O(n) - 2 tablouri unidimensionale folosite pentru 
a retine puterile de calcul si a liminelor de alimentare ale serverelor.

Tehnica folosita:
* Divide et impera - deoarece folosim binary search.

# 2. Colorare

Am considerat o metoda iterativa bazata pe calcularea cazurilor de colorare 
pentru a afla numarul de tablouri distincte. 

Luand in cosiderare restrictiile problemei, am distins urmatoarele 2 cazuri 
de baza:
* pentru 1H => avem 6 modalitati in care putem colora dreptunghiurile.
* pentru 1V => avem 3 modalitati in care putem colora dreptunghiurile.

Ulterior, am observat faptul ca numarul total de tablouri distincte, depinde de
care este orientarea ultimului dreptunghi si a celui actual. Astfel:

* daca ultimul dreptunghi a fost orizontal si urmeaza un dreptunghi vertical =>
avem o singura modalitate de a alege culoarea dreptunghiului vertical.
* daca ultimul dreptunghi a fost orizontal si urmeaza un dreptunghi orizontal =>
pentru gruparea celor 2 noi dreptunghiuri, avem 3 variante de a alege culorile.
* daca ultimul dreptunghi a fost vertical si urmeaza un dreptunghi vertical =>
acesta poate fi ales in 2 moduri.
* daca ultimul dreptunghi a fost vertical si urmeaza un dreptunghi orizontal =>
pentru gruparea celor 2 noi dreptunghiuri, avem 2 variante de a alege culorile.

Astfel, in rezolvare, initializam raspunsul `ans` cu valoarea specifica in 
functie de orientarea primului dreptunghi si variabila `last` in care memoram 
la fiecare pas orientarea ultimului dreptunghi. Dupa, continuam constructia, 
in functie de cele 4 cazuri prezentate anterior.

Initial, am considerat ridicarea la putere iterativa, insa, aceasta nu era 
suficient de rapida, motiv pentru care am adoptat tehnica exponentierii 
logaritmice pentru a calcula rezultatul.

Complexitatea este:
* *Complexitate temporala*: O(n log m) - `n` reprezinta numarul de perechi citite, 
pentru ca pentru fiecare pereche se apeleaza una dintre functiile `horizontal` 
sau `vertical`, care calculeaza rezultatul total, iar `m` reprezinta valoarea
medie pentru `num`, numarul de dreptunghiuri din fiecare pereche, pentru care 
algoritmul de cautare exponentiere logaritmica va face O(log m) pasi pentru 
determinarea valorii cautate.
* *Complexitate spatiala*: O(1) - folosim un numar constant de variabile locale.

Links resurse:
* exponentiere logaritmica: 
https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/ 


# 3. Compresie

Am considerat o abordare de tip Greedy pentru rezolvarea acestei probleme, 
deoarece luam decizii locale optime la fiecare pas, pentru a ajunge la o 
solutie globala optima. 

In primul rand, calculam sumele din ambele siruri. Daca sumele elementelor 
nu sunt egale, atunci este clar ca oricate operatii am face, nu vom ajunge 
la doua siruri egale. Altfel, initializam cele doua sume cu primul element din
fiecare sir, si 2 indicii: i si j care sa contorizeze pozitia in cadrul fiecarui
tablou unidimensional, initial egale cu 0. Daca cele doua sume sunt egale, 
inseamna ca am ajuns la o subsecventa egala, deci crestem lungimea totala a 
rezultatului `ans++`, cat si pozitiile in fiecare sir si actualizam sumele 
din cele doua tablouri unidimensionale cu urmatorul element din sir. Facem 
aceste operatii, cat timp nu am ajuns la finalul a cel putin unul din cele 
doua siruri. In final, afisam rezultatul `ans`.

Complexitatea este:
* *Complexitate temporala*: O(n + m) - `n` reprezinta lungimea primului sir, 
iar `m` reprezinta lungimea celui de-al doilea sir, intrucat fiecare element 
din cele doua siruri este procesat cel mult o data.
* *Complexitate spatiala*: O(n) - folosim doua tablouri unidimensionale pentru
a retine cele doua siruri. s

# 4. Criptat 

Am considerat o abordare de tip DP - Dynamic Programming pentru rezolvarea
acestei probleme. 

Incepem prin a procesa fiecare cuvant, salvandu-i lungimea,
adica numarul de litere `length`, cat si construind un vector caracteristic 
in care marcam aparitia fiecarei litere intalnite `letter`, tot la initiere, 
calculam si numarul total de litere ale cuvintelor `sum_lengths`. Ulterior, 
fiecarei litere folosite ii atribuim un id unic, `id[i]`, reprezentand 
valoarea id-ului, iar in tabloul bidimensional `fr`, intr-un element 
`fr[i][j]` memoram frecventa literei cu id-ul j, in cuvantul cu indice i.
Pentru fiecare litera unica gasita, incercam sa gasim parola de lungime unica,
retinand intotdeauna numarul de caractere ale parolei de lungime maxima. 
Consideram urmatoarea abordare de tip "rucsac": pentru fiecare cuvant din 
lista, incercam sa vedem daca pentru fiecare lungime existenta deja in vectorul
`dp`, adaugarea cuvantului ajuta la rezultatul final. Daca raspunsul este unul
pozitiv, atunci actualizam vectorul `dp`, unde `dp[i]` reprezinta numarul maxim 
de aparitii ale literei vizate in cuvant, iar i reprezinta lungimea cuvantului.
Pentru litera vizata, intoarcem din functia `get` lungimea maxima a unei parole
pentru care litera vizata indeplineste si conditia de dominanta, adica numarul
ei de aparitii sa fie mai mare decat jumatate din lungimea cuvantului.

Totusi, initial, pentru aceasta problema am considerat o abordare de tip
Greedy, insa, solutia pentru aceasta varianta obtinea doar 28 puncte.

Complexitatea este:
* *Complexitate temporala*: O(n * m) - `n` reprezinta numarul de cuvinte 
citite, iar `m` reprezinta suma lungimilor tuturor cuvintelor, deoarece, 
in functia `get`, pentru fiecare cuvant din lista se actualizeaza vectorul
`dp`, deci O(n * m).
* *Complexitate spatiala*: O(n + m) - folosim tablouri unidimensionale pentru
stocarea celor n cuvinte si lungimi: `words` si `length` - O(n), iar pentru
matricea `dp` se stocheaza maxim valoarea m, suma lungimilor tuturor cuvintelor.
Restul tablourilor, ex. `letter`, `id` au dimensiune constanta O(1). Deci, 
in total avem, O(n + m).

# 5. Oferta

Am considerat o abodare de tip DP - Dynamic Programming pentru rezolvarea 
acestei probleme. In matricea `dp` stochez cele mai mici k preturi unice ce
se pot obtine pentru a cumpara produse. Matricea dp va contine intotdeauna 
doar 4 linii, reprezentand o minimizare a consumului de memorie, pentru a 
intra in limitele propuse, iar pe prima coloana dp[i][0] va contine numarul
de preturi unice obtinute cu produsele luate in considerare pana la acel 
moment.

In primul rand, distingem urmatoarele cazuri de baza ale problemei:
* `dp[0][0] = 1` - un element si `dp[0][1] = 0` - pretul 0 obtinut pentru 0 
produse
* `dp[1][0] = 1` - un element si `dp[1][1] = v[0]` - pretul obtinut pentru 
cumpararea integrala a primului produs.
* `dp[2][0] = 2` - doua elemente si `dp[2][1]`, respectiv `dp[2][2]`, preturile
obtinute pentru cumpararea fie integrala a primelor 2 produse, fie cu reducerea 
de 50%, stocate in ordine crescatoare.

Pentru urmatoarele n - 2 produse pe care trebuie sa le cumparam aplicam 
urmatorii pasi: calculam listele de preturi care se pot obtine daca:
* cumparam al i-lea produs integral
* cumparam al i-lea produs aplicand reducerea de 50% pentru 2 produse
* cumparam al i-lea produs aplicand reducerea de 100% pentru 3 produse.
Memoram aceste liste de preturi in 3 tablouri unidimensionale, pe care, 
ulterior, le interclasam, salvand in matricea `dp` doar cele mai mici k
preturi unice pe care le putem obtine.

La final, verificam, daca numarul de preturi unice obtinute stocate in matrice 
in elementul `dp[n % 4][0]` este mai mic decat k, afisam `-1`, altfel, afisam
valoarea `dp[n % 4][k]`, deci cel de-al k-lea cel mai mic pret unic pe care 
il putem obtine.

Complexitatea este:
* *Complexitate temporala*: O(n * k) - `n` reprezinta numarul de produse pe 
care trebuie sa le cumparam, pentru fiecare produs incepand cu cel cu indicele
3 pana la n, calculam listele de preturi, deci, parcurgem maxim k elemente, pe 
care, le interclasam, facand apel la functia `merge` care are complexitate de 
O(n + m), daca consideram ca primul vector are n elemente si cel de-al doilea m,
dar, cum n si m <= k, putem aproxima complexitatea functiei la O(2 * k), deci 
O(k). Deci, in total vom avea O(n * k).
* *Complexitate spatiala*: O(n) - folosim un tablou unidimensional pentru
stocarea celor n preturi si in plus, matricea `dp[5][10005]` si vectorii 
intermediari folositi la calcularea listelor de preturi si a rezultatelor 
interclasarii, acesti avand la un moment dat, dimensiune maxima k. Deci, 
in total, avem o complexitate spatiala de aproximativ O(n + 5k).

# Observatii

Problemele propuse mi s-au parut destul de interesante, pentru unele fiind 
necesara uneori o schimbare de perspectiva la prima tehnica de rezolvare
care imi venea in minte. Dar, consider ca a fost o tema care mi-a placut.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

ifstream fin("oferta.in");
ofstream fout("oferta.out");

#define NMAX 10001
#define LINES 5

// face interclasarea sirurilor a si b, memorand in c, maxim primele k
// elemente unice, returnand numarul de elemente unice pe care le contine c
int merge(double a[], double b[], double c[], int n, int m, int k) {
    int i = 0, j = 0, p = 0;

    while (i < n && j < m && p < k) {
        // daca elementele din cele 2 siruri sunt egale
        if (a[i] == b[j]) {
            // ne aflam la primul rezultat in sirul c sau am gasit un nou
            // rezultat unic, atunci il adaugam si inaintam in sirul a si b
            if (p == 0 || c[p - 1] != a[i]) {
                c[p++] = a[i++];
                j++;
            } else {
                i++;
                j++;
            }
        } else if (a[i] < b[j]) {
            // daca elementul din a este mai mic, il adaugam in c si
            // crestem indicele
            if (p == 0 || c[p - 1] != a[i]) {
                c[p++] = a[i++];
            }
        } else {
            // altfel, adaugam in c elementul din b si crestem indicele
            if (p == 0 || c[p - 1] != b[j]) {
                c[p++] = b[j++];
            }
        }
    }

    // daca in sirul a sau b au mai ramas elemente, le copiem, pana cand
    // ajungem la maxim k valori unice in vectorul c
    for (int t = i; t < n && p < k; t++) {
        if (c[p - 1] != a[t]) {
            c[p++] = a[t];
        }
    }

    for (int t = j; t < m && p < k; t++) {
        if (c[p - 1] != b[t]) {
            c[p++] = b[t];
        }
    }

    return p;
}

void solve(int n, int v[], double dp[][NMAX], int k) {
    double prices1[NMAX], prices2[NMAX], prices3[NMAX];
    double result1[NMAX], result2[NMAX];
    int m;

    // pentru urmatoarele n - 2 produse
    for (int i = 3; i <= n; i++) {
        // calcum preturile ce se pot obtine daca cumparam al i-lea produs
        // la pret intreg
        for (int j = 0; j < dp[(i - 1) % 4][0]; j++) {
            prices1[j] = 0;
            prices1[j] = dp[(i - 1) % 4][j + 1] + v[i - 1];
        }

        // aplicand oferta de reducere 50% cand grupam 2 produse
        for (int j = 0; j < dp[(i - 2) % 4][0]; j++) {
            prices2[j] = 0;
            prices2[j] = dp[(i - 2) % 4][j + 1] + v[i - 1] + v[i - 2]
                        - (double)(min(v[i - 1], v[i - 2])) / 2;
        }

        // aplicand oferta de reducere 100% cand grupam 3 produse
        for (int j = 0; j < dp[(i - 3) % 4][0]; j++) {
            prices3[j] = 0;
            prices3[j] = dp[(i - 3) % 4][j + 1] + v[i - 1] + v[i - 2] + v[i - 3]
                        - (double)(min(min(v[i - 3], v[i - 2]), v[i - 1]));
        }

        // m - nr. de elemente distincte rezultate dupa interclasarea
        // primelor 2 tablouri
        m = merge(prices1, prices2, result1, dp[(i - 1) % 4][0],
                        dp[(i - 2) % 4][0], k);

        // dp[i % 4][0] - nr. de elemente distincte rezultate dupa
        // interclasarea tuturor celor 3 tablouri
        dp[i % 4][0] = merge(result1, prices3, result2, m,
                                   dp[(i - 3) % 4][0], k);

        // copiem cele dp[i % 4][0] preturi distincte in matricea dp
        for (int j = 1; j <= dp[i % 4][0]; j++) {
            dp[i % 4][j] = result2[j - 1];
        }
    }
}

int main() {
    int n, k, v[NMAX];
    double dp[LINES][NMAX];

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        fin >> v[i];
    }

    // nu exista solutie, deoarece nu putem obtine k preturi distincte
    if ((n == 1 && n < k) || (n == 2 && n < k)) {
        fout << -1;
        return 0;
    }

    // dp[i][0] = nr de preturi distincte gasite, pana la produsul i, inclusiv
    dp[0][0] = 1;
    // pentru 0 produse, platim 0
    dp[0][1] = 0;
    dp[1][0] = 1;
    // primul produs va fi cumparat la pret intreg
    dp[1][1] = v[0];
    dp[2][0] = 2;
    // pentru doua produse, memoram preturile cu care le putem cumpara
    dp[2][1] = min((double)(v[0] + v[1]),
                   v[0] + v[1] - (double)(min(v[0], v[1])) / 2);
    dp[2][2] = max((double)(v[0] + v[1]),
                   v[0] + v[1] - (double)(min(v[0], v[1])) / 2);

    solve(n, v, dp, k);

    // daca numarul de preturi obtinute este mai mic decat k, nu avem solutie
    if (dp[n % 4][0] < k) {
        fout << -1;
    } else {
        // afisam cel de-al k-lea pret unic pe care il putem obtine
        fout << fixed << setprecision(1) << dp[n % 4][k];
    }

    fin.close();
    fout.close();
    return 0;
}

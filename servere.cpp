#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

ifstream fin("servere.in");
ofstream fout("servere.out");

#define NMAX 100001

int main() {
    int n;

    long double p[NMAX], c[NMAX];
    long double interval_left, interval_right;
    long double current_left, current_right, actual_mid;

    long long left = 1LL * INT32_MIN * 10LL, right = 1LL * INT32_MAX;
    long long mid = 0, ans = 0;

    // citim numarul de servere
    fin >> n;

    for (int i = 0; i < n; i++) {
        // citim puterile de calcul ale fiecarui server
        fin >> p[i];
        // initializam valoarea lui right cu cea mai mica putere de calcul
        if (p[i] < right)
            right = p[i];
    }

    right *= 10LL;

    // citim pragurile de alimentare optime pentru fiecare server
    for (int i = 0; i < n; i++)
        fin >> c[i];

    // folosim cautarea binara pentru a gasi valoare optima
    while (left <= right) {
        // calculam mijlocul intervalului
        mid = (left + right) / 2LL;
        actual_mid = (long double) mid / (long double) 10;

        // initializam intervalele pentru primul server
        interval_left = actual_mid - p[0] + c[0];
        interval_right = p[0] - actual_mid + c[0];

        // calculam pentru fiecare dintre cele n - 1 servere ramase intervalele
        for (int i = 1; i < n; i++) {
            current_left = actual_mid - p[i] + c[i];
            current_right = p[i] - actual_mid + c[i];

            // memoram intervalul cel mai restrans,
            // practic intersectia celor n intervale
            interval_left = max(interval_left, current_left);
            interval_right = min(interval_right, current_right);
        }

        // daca exista un interval comun pentru datele de intrare
        if (interval_left <= interval_right) {
            // incercam sa ajustam limita, poate obtin un rezultatul mai bun
            left = mid + 1LL;
            // actualizam raspunsul
            ans = mid;
        } else {
            // ajustam limita inferioara
            right = mid - 1LL;
        }
    }

    // afisam partea intreaga
    fout << (long long)(ans / 10LL) << ".";

    // si partea fractionala
    if (ans >= 0LL)
        fout << ans % 10LL;
    else
        fout << (-ans) % 10LL;

    fin.close();
    fout.close();
    return 0;
}

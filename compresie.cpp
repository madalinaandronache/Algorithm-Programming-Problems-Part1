#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("compresie.in");
ofstream fout("compresie.out");

#define NMAX 300001

// citeste un vector cu n elemente si returneaza suma elementelor
int read(int &n, int v[]) {
    int sum = 0;

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> v[i];
        sum += v[i];
    }

    return sum;
}

int solve(int n, int a[], int m, int b[]) {
    int i, j, ans = 0, suma, sumb;

    // pornim comparatia de pe prima pozitie in ambii vectori
    i = j = 0;
    // suma din primul sir
    suma = a[0];
    // suma din cel de-al doilea sir
    sumb = b[0];

    while (i < n && j < m) {
        if (suma == sumb) {
            // lungimea sirului rezultat creste
            ans++;
            // inaintam la urmatorul numar in ambele siruri
            i++;
            j++;
            // actualizam sumele
            suma = a[i];
            sumb = b[j];
        } else if (suma < sumb) {
            // inaintam la urmatorul numar in primul sir
            i++;
            // adaugam la suma din primul sir urmatorul element
            suma += a[i];
        } else {
            // inaintam la urmatorul numar in primul sir
            j++;
            // adaugam la suma din al doilea sir urmatorul element
            sumb += b[j];
        }
    }

    return ans;
}

int main() {
    int n, m, a[NMAX], b[NMAX];

    // daca suma din primul vector nu este egala cu suma din al doilea vector
    if (read(n, a) != read(m, b)) {
        fout << -1;
    } else {
        fout << solve(n, a, m, b);
    }

    fin.close();
    fout.close();
    return 0;
}

#include <iostream>
#include <fstream>

#define MOD 1000000007

using namespace std;

ifstream fin("colorare.in");
ofstream fout("colorare.out");

// calculeaza x^n - exponentiere modulara
long long expo(long long x, long long n) {
    long long result = 1;

    while (n > 0) {
        // daca puterea este impara, inmultim rezultatul cu baza
        if (n % 2 == 1) {
            result = ((result % MOD) * (x % MOD)) % MOD;
        }

        x = ((x % MOD) * (x % MOD)) % MOD;
        n = n / 2;
    }

    return result;
}

// determina rezultatul dupa adaugarea a num dreptunghiuri verticale
void vertical(int num, long long &ans) {
    ans = ((ans % MOD) * (expo(2, num) % MOD)) % MOD;
}

// determina rezultatul dupa adaugarea a num dreptunghiuri orizontale
void horizontal(int num, long long &ans) {
    ans = ((ans % MOD) * (expo(3, num) % MOD)) % MOD;
}

void init(int num, long long &ans, char &last, char &type) {
    // daca primul dreptunghi aseazat este orizontal
    if (type == 'H') {
        // exista 6 modalitati
        ans = 6;
        horizontal(num, ans);
        last = 'H';
    } else {
        // altfel, exista 3 modalitati
        ans = 3;
        vertical(num, ans);
        last = 'V';
    }
}

int main() {
    int k, num;
    char type, last;
    long long ans = 1;

    fin >> k;
    fin >> num >> type;

    // scadem numarul de dreptunghiuri care trebuiesc asezate
    num--;

    // initializam ans in functie de prima pereche citita
    init(num, ans, last, type);

    // pentru urmatoarele k - 1 perechi
    for (int i = 1; i < k; i++) {
        fin >> num >> type;

        // discutam cazurile in functie de orientarea ultimului dreptunghi
        // si a urmatorului
        if (last == 'H' && type == 'V') {
            // asez primul dreptunghi care poate fi pus doar intr-o
            // singura culoare
            num--;
            // raman num grupari verticale consecutive
            vertical(num, ans);
            last = 'V';
        } else if (last == 'V' && type == 'H') {
            num--;
            // asez prima grupare de dreptunghiuri orizontale care pot fi
            // alese in doar 2 moduri
            ans = ((ans % MOD) * 2) % MOD;
            // raman num grupari orizontale consecutive
            horizontal(num, ans);
            last = 'H';
        } else if (last == 'H' && type == 'H') {
            // avem num grupari orizontale cosecutive
            horizontal(num, ans);
        } else {
            // avem num grupari verticale cosecutive
            vertical(num, ans);
        }
    }

    fout << ans;

    fin.close();
    fout.close();
    return 0;
}

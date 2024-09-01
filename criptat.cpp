#include <fstream>

using namespace std;

ifstream fin("criptat.in");
ofstream fout("criptat.out");

#define NMAX 1001
#define LMAX 10001
#define DIFFERENT_LETTERS 8
#define NUM_CHR 26

int n, length[NMAX], fr[NMAX][DIFFERENT_LETTERS + 1], id[NUM_CHR], dp[LMAX];
string words[NMAX];
bool letter[NUM_CHR] = {false};
int sum_lengths = 0;

void init() {
    fin >> n;
    for (int i = 1; i <= n; i++) {
        fin >> words[i];
        // memoram lungimea fiecarui cuvant
        length[i] = words[i].size();
        // calculam lungimea totala a cuvintelor
        sum_lengths += length[i];
        // marcam cu true daca literea a fost folosita
        for (int j = 0; j < length[i]; j++) {
            letter[(int)(words[i][j] - 'a')] = true;
        }
    }
}

void reset_dp() {
    dp[0] = 0;
    for (int i = 1; i <= sum_lengths; i++) {
        dp[i] = -1;
    }
}

// calculeaza parola de lungime maxima pentru litera cu id-ul target_letter
int get(int target_letter) {
    reset_dp();

    // pentru fiecare cuvant din lista
    for (int i = 1; i <= n; i++) {
        for (int j = (sum_lengths - length[i]); j >= 0; j--) {
            // pentru fiecare lungime existenta deja, incercam sa adaugam
            // noul cuvant
            if (dp[j] != -1) {
                if ((dp[j] + fr[i][target_letter]) > dp[(j + length[i])]) {
                    dp[(j + length[i])] = (dp[j] + fr[i][target_letter]);
                }
            }
        }
    }

    for (int i = sum_lengths; i >= 1; i--) {
        // daca litera este dominanta
        if (dp[i] > (i / 2)) {
            // returnam lungimea cuvantului
            return i;
        }
    }

    return 0;
}

void solve(int num_letters) {
    int ans = 0;

    // pentru fiecare litera unica gasita, aplicam dp
    for (int i = 1; i <= num_letters; i++) {
        int length = get(i);
        // actualizam raspunsul cu lungimea maxima gasita
        if (length > ans) {
            ans = length;
        }
    }

    fout << ans;
}

int main() {
    init();

    // pentru fiecare litera folosita ii atribuim un id unic
    int cnt = 0;
    for (int i = 0; i < NUM_CHR; ++i)
        if (letter[i])
            id[i] = (++cnt);

    // calculam frecventa fiecarei litere in fiecare cuvant
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < length[i]; ++j)
            ++fr[i][id[(int)(words[i][j] - 'a')]];

    solve(cnt);

    fin.close();
    fout.close();
    return 0;
}

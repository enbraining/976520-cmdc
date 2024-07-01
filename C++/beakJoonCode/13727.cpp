#include <bits/stdc++.h>
using namespace std;

const int MODULO = 1e9 + 7;

long long exponentiate(long long base, long long power) {
    long long result = 1, pivot = base;
    while (power) {
        if (power & 1) result = result * pivot % MODULO;
        pivot = pivot * pivot % MODULO;
        power >>= 1;
    }
    return result;
}

vector<int> berlekampMassey(vector<int> sequence) {
    vector<int> L, current;
    int Lf, Ld;
    for (int i = 0; i < sequence.size(); i++) {
        long long t = 0;
        for (int j = 0; j < current.size(); j++) {
            t = (t + 1ll * sequence[i - j - 1] * current[j]) % MODULO;
        }
        if ((t - sequence[i]) % MODULO == 0) continue;
        if (current.empty()) {
            current.resize(i + 1);
            Lf = i;
            Ld = (t - sequence[i]) % MODULO;
            continue;
        }
        long long k = -(sequence[i] - t) * exponentiate(Ld, MODULO - 2) % MODULO;
        vector<int> C(i - Lf - 1);
        C.push_back(k);
        for (auto& j : L) C.push_back(-j * k % MODULO);
        if (C.size() < current.size()) C.resize(current.size());
        for (int j = 0; j < current.size(); j++) {
            C[j] = (C[j] + current[j]) % MODULO;
        }
        if (i - Lf + (int)L.size() >= (int)current.size()) {
            tie(L, Lf, Ld) = make_tuple(current, i, (t - sequence[i]) % MODULO);
        }
        current = C;
    }
    for (auto& i : current) i = (i % MODULO + MODULO) % MODULO;
    return current;
}

int getNthTerm(vector<int> recurrence, vector<int> dp, long long n) {
    int m = recurrence.size();
    vector<int> S(m), T(m);
    S[0] = 1;
    if (m != 1) T[1] = 1;
    else T[0] = recurrence[0];
    auto multiply = [&recurrence](vector<int> V, vector<int> W) {
        int m = V.size();
        vector<int> T(2 * m);
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                T[j + k] += 1ll * V[j] * W[k] % MODULO;
                if (T[j + k] >= MODULO) T[j + k] -= MODULO;
            }
        }
        for (int j = 2 * m - 1; j >= m; j--) {
            for (int k = 1; k <= m; k++) {
                T[j - k] += 1ll * T[j] * recurrence[k - 1] % MODULO;
                if (T[j - k] >= MODULO) T[j - k] -= MODULO;
            }
        }
        T.resize(m);
        return T;
    };
    while (n) {
        if (n & 1) S = multiply(S, T);
        T = multiply(T, T);
        n >>= 1;
    }
    long long result = 0;
    for (int i = 0; i < m; i++) result += 1ll * S[i] * dp[i] % MODULO;
    return result % MODULO;
}

int findNthTerm(vector<int> sequence, long long n) {
    if (n < sequence.size()) return sequence[n];
    vector<int> V = berlekampMassey(sequence);
    if (V.empty()) return 0;
    return getNthTerm(V, sequence, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> sequence = { 1, 272, 589185, 930336768, 853401154, 217676188, 136558333, 415722813, 985269529, 791527976, 201836136, 382110354, 441223705, 661537677, 641601343, 897033284, 816519670, 365311407, 300643484, 936803543, 681929467, 462484986, 13900203, 657627114, 96637209, 577140657, 600647073, 254604056, 102389682, 811580173, 592550067, 587171680, 526467503, 265885773, 951722780, 219627841, 371508152, 283501391, 159234514, 439380999, 722868959, 125599834, 351398134, 456317548, 365496182, 614778702, 502680047, 193063685, 309004764, 743901785, 870955115, 312807829, 160375015, 691844624, 137034372, 350330868, 895680450, 282610535, 317897557, 28600551, 583305647, 539409363, 327406961, 627805385, 680183978, 681299085, 954964592, 743524009, 788048339, 699454626, 666369521, 857206425, 490463127, 477198247, 599963928, 21247982, 107843532, 753662937, 239039324, 608530376, 523383010, 654448101, 801430395, 393034561, 93313778, 983052766, 240336620, 825539982, 525118275, 563899476, 706271688, 547405697, 477082486, 664058071, 353207278, 729486413, 795704637, 999271072, 540749624, 411451016, 736422999, 879369181, 918733916, 982303557, 512499644, 261033810, 391766409, 334092786, 931794834, 854181848, 821090190, 751839258, 433126935, 571194155, 52438113, 552977155, 320805296, 173355929, 969659468, 258854248, 159509877, 374487748, 401382023, 44060530, 510164669, 336596764, 652050424, 373872552, 517226592, 719871041, 43959496, 235333335, 304962191, 253114421, 43638769, 361871585, 8060121, 147014624, 114846460, 430864038, 368951246, 863795701, 36066788, 971606149, 935875286, 486724123, 73790652, 236936530, 307697424, 753314001, 40450345, 529462842, 166162047, 974102330, 600865526, 63237062, 749041914, 670937123, 806399597, 776678839, 842565920, 608499253, 469062485, 842196981, 247762946, 778570576, 237951782, 286343384, 988318575, 147255879, 905747089, 711062313, 21396079, 826846622, 443781794, 786474911, 400737121, 844768961, 686214818, 590050845, 855473150, 18501778, 33258755, 398169058, 811192244, 710397887, 591757177, 775311969, 168256434, 509615161, 489764304, 605188191, 498085780, 164388183, 524662873, 322602324, 853641480, 205349527, 308211944, 93153206 };
    long long n;
    cin >> n;
    cout << findNthTerm(sequence, n) << '\n';
}

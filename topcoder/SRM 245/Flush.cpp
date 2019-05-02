#include <bits/stdc++.h>
using namespace std;

const int MAXS = 4 * 14;

class Flush {
public:
  double size(vector<int> suits, int number) {
    auto comb = array<array<long long, MAXS>, MAXS>();
    comb[0][0] = 1;
    for (int n = 1; n < MAXS; ++n) {
      comb[n][0] = comb[n][n] = 1;
      for (int k = 1; k < n; ++k) {
        comb[n][k] = comb[n - 1][k] + comb[n - 1][k - 1];
      }
    }

    int A = suits[0];
    int B = suits[1];
    int C = suits[2];
    int D = suits[3];

    long long totalFlush = 0;

    for (int a = 0; a <= A; ++a)
    for (int b = 0; b <= B; ++b)
    for (int c = 0; c <= C; ++c)
    for (int d = 0; d <= D; ++d) if (a+b+c+d == number) {
      long long ways = comb[A][a] * comb[B][b] * comb[C][c] * comb[D][d];
      int flush = max(a, max(b, max(c, d)));
      totalFlush += flush * ways;
    }
    return totalFlush / (double) comb[A+B+C+D][number];
  }
};

// CUT begin
ifstream _greed_data("Flush.sample");

string next_line() {
    string s;
    getline(_greed_data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> suits, int number, double __expected) {
    time_t startClock = clock();
    Flush *instance = new Flush();
    double __result = instance->size(suits, number);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> suits;
        from_stream(suits);
        int number;
        from_stream(number);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(suits, number, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556786028;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Flush (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end


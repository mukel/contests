// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

const int
  MAXN = 60;

class WordPattern {
public:
  long long countWords(string word) {
    int N = word.size();
    if (N == 1) {
      return 1;
    }

    long long ans = 0;
    auto dp = array<array<long long, MAXN>, MAXN>();
    dp[0][0] = 1;
    for (int w = 1; w < N; ++w) {
      for (int j = 0; j <= w; ++j) {
        int k = w - j;
        if (j > 0) dp[j][k] += dp[j - 1][k];
        if (k > 0) dp[j][k] += dp[j][k - 1];
        if (w == N - 1) ans += dp[j][k];
      }
    }
    return ans * 4 - 4;
  }
};

// CUT begin
ifstream _greed_data("WordPattern.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string word, long long __expected) {
    time_t startClock = clock();
    WordPattern *instance = new WordPattern();
    long long __result = instance->countWords(word);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
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
        string word;
        from_stream(word);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(word, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556800019;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WordPattern (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

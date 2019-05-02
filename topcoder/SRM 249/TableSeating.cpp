// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

const int
  MAX_MASK = 1 << 12;

class TableSeating {
public:
  double getExpected(int numTables, vector<int> probs) {
    double ans = 0;

    auto dp = array<double, MAX_MASK>();

    dp[0] = 1;

    for (int s = 0; s < (1 << numTables); ++s) {
      for (int i = 0; i < (int) probs.size(); ++i) {
        int groupMask = (1 << (i+1)) - 1;

        int cnt = 0;
        for (int j = 0; j + i < numTables; ++j) {
          if ((s & (groupMask << j)) == 0) { // can seat group
            cnt++;
          }
        }
        if (cnt) {
          for (int j = 0; j + i < numTables; ++j) {
            if ((s & (groupMask << j)) == 0) { // can seat group
              dp[s | (groupMask << j)] += dp[s] * (probs[i] / 100.0) / cnt;
            }
          }
        } else {
          ans += __builtin_popcount(s) * dp[s] * (probs[i] / 100.0);
        }
      }
    }

    return ans;
  }
};

// CUT begin
ifstream _greed_data("TableSeating.sample");

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

bool do_test(int numTables, vector<int> probs, double __expected) {
    time_t startClock = clock();
    TableSeating *instance = new TableSeating();
    double __result = instance->getExpected(numTables, probs);
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
        int numTables;
        from_stream(numTables);
        vector<int> probs;
        from_stream(probs);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numTables, probs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556803214;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 350 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TableSeating (350 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

class Musical {
public:

  const double PI = 2 * acos(0);

  double dist(double a, double b) {
    double d = abs(a - b);
    for (int i = -100; i <= +100; ++i) {
      d = min(d, abs((a + i * 2 * PI) - b));
    }
    return d;
  }

  string loser(int n, double time) {

    auto child = vector<double>(n);
    double delta = time / 10.0 * (2 * PI);
    for (int i = 0; i < n; ++i) {
      child[i] = -i * (2 * PI) / n + delta;
      cerr << child[i] / (2 * PI) * 360 << " ";
    }
    cerr << endl;

    auto chair = vector<double>(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      chair[i] = i * (2 * PI) / (n - 1);
      cerr << chair[i] / (2 * PI) * 360 << " ";
    }
    cerr << endl;

    auto d = vector<double>(n);
    for (int i = 0; i < n; ++i) {
      d[i] = 1e9;
      for (double c : chair) {
        d[i] = min(d[i], dist(child[i], c));
      }
      cerr << d[i] << " ";
    }
    cerr << endl;

    int loser = max_element(d.begin(), d.end()) - d.begin();

    return string("") + (char)('A' + loser);
  }
};

// CUT begin
ifstream _greed_data("Musical.sample");

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

bool do_test(int n, double time, string __expected) {
    time_t startClock = clock();
    Musical *instance = new Musical();
    string __result = instance->loser(n, time);
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
        int n;
        from_stream(n);
        double time;
        from_stream(time);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, time, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556795649;
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
        cout << "Musical (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

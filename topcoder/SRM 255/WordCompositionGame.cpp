// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

#define ALL(c) (c).begin(), (c).end()

class WordCompositionGame {
public:

  int calc(vector<string> a, vector<string> b, vector<string> c) {
    int score = 0;
    for (string s : a) {
      score += 3 - binary_search(ALL(b), s) - binary_search(ALL(c), s);
    }
    return score;
  }

  string score(vector<string> a, vector<string> b, vector<string> c) {
    sort(ALL(a));
    sort(ALL(b));
    sort(ALL(c));
    return
      to_string(calc(a, b, c)) + "/" +
      to_string(calc(b, a, c)) + "/" +
      to_string(calc(c, a, b));
  }
};

// CUT begin
ifstream _greed_data("WordCompositionGame.sample");

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

bool do_test(vector<string> listA, vector<string> listB, vector<string> listC, string __expected) {
    time_t startClock = clock();
    WordCompositionGame *instance = new WordCompositionGame();
    string __result = instance->score(listA, listB, listC);
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
        vector<string> listA;
        from_stream(listA);
        vector<string> listB;
        from_stream(listB);
        vector<string> listC;
        from_stream(listC);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(listA, listB, listC, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556811187;
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
        cout << "WordCompositionGame (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

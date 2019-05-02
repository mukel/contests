// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

class LanguageRecognition {
public:

  int validLetter(char c) {
    if ('a' <= c && c <= 'z') return c;
    if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
    return -1;
  }

  int whichLanguage(vector<string> languages, string text) {
    int L = languages.size();

    auto langFreq = vector<vector<int>>(L + 1, vector<int>(0xFF));
    auto langCnt = vector<int>(L + 1);
    languages.push_back(text);

    for (int i = 0; i < L + 1; ++i) {
      string s = languages[i];
      for (char c : s) {
        int letter = validLetter(c);
        if (letter >= 0) {
          ++langFreq[i][letter];
          ++langCnt[i];
        }
      }
    }

    auto score = vector<double>(L);
    for (int i = 0; i < L; ++i) {
      for (char c = 'a'; c <= 'z'; ++c) {
        double si = langFreq[L][c] / (double) langCnt[L];
        double t = langFreq[i][c] / (double) langCnt[i];
        double delta = si - t;
        score[i] += delta * delta;
      }
    }

    return min_element(score.begin(), score.end()) - score.begin();
  }
};

// CUT begin
ifstream _greed_data("LanguageRecognition.sample");

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

bool do_test(vector<string> languages, string text, int __expected) {
    time_t startClock = clock();
    LanguageRecognition *instance = new LanguageRecognition();
    int __result = instance->whichLanguage(languages, text);
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
        vector<string> languages;
        from_stream(languages);
        string text;
        from_stream(text);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(languages, text, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556804868;
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
        cout << "LanguageRecognition (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

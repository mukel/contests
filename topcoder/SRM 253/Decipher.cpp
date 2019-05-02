// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

class Decipher {
public:
  vector<string> decipher(vector<string> encoded, string frequencyOrder) {
    auto cnt = vector<int>(26);
    for (string s : encoded) {
      for (char c : s) {
        if (c != ' ') {
          cnt[c - 'A']++;
        }
      }
    }

    auto order = vector<int>(26);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) -> bool {
      if (cnt[i] != cnt[j]) {
        return cnt[i] > cnt[j];
      }
      return i < j;
    });

    for (string& s : encoded) {
      string t = s;
      int curChr = 0;
      for (int index : order) {
        if (cnt[index] == 0) {
          break;
        }
        for (int i = 0; i < (int) s.size(); ++i) {
          if (s[i] == (char)('A' + index)) {
            t[i] = frequencyOrder[curChr];
          }
        }
        curChr++;
      }
      s = t;
    }

    return encoded;
  }
};

// CUT begin
ifstream _greed_data("Decipher.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < (int) ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> encoded, string frequencyOrder, vector<string> __expected) {
    time_t startClock = clock();
    Decipher *instance = new Decipher();
    vector<string> __result = instance->decipher(encoded, frequencyOrder);
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
        vector<string> encoded;
        from_stream(encoded);
        string frequencyOrder;
        from_stream(frequencyOrder);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(encoded, frequencyOrder, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556808118;
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
        cout << "Decipher (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

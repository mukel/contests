// Alfonso² Peterssen (mukel)
#include <bits/stdc++.h>
using namespace std;

#define ALL(c) (c).begin(), (c).end()

class MagicCube {
public:

  int get(int i, int j, int k, vector<int>& cube) {
    return cube[i * 9 + j * 3 + k];
  }

  int score(vector<int>& c) {
    auto s = vector<int>(3 * 3 * 3);
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          s[0 * 9 + i * 3 + j] += get(i, j, k, c);
          s[1 * 9 + i * 3 + k] += get(i, j, k, c);
          s[2 * 9 + j * 3 + k] += get(i, j, k, c);
        }
      }
    }
    return *max_element(ALL(s)) - *min_element(ALL(s));
  }

  int getScore(vector<int> nums) {
    int ans = score(nums);
    for (int i = 0; i < (int) nums.size(); ++i) {
      for (int j = i + 1; j < (int) nums.size(); ++j) {
        swap(nums[i], nums[j]);
        ans = min(ans, score(nums));
        swap(nums[i], nums[j]);
      }
    }
    return ans;
  }
};

// CUT begin
ifstream _greed_data("MagicCube.sample");

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

bool do_test(vector<int> nums, int __expected) {
    time_t startClock = clock();
    MagicCube *instance = new MagicCube();
    int __result = instance->getScore(nums);
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
        vector<int> nums;
        from_stream(nums);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(nums, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1556812219;
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
        cout << "MagicCube (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end

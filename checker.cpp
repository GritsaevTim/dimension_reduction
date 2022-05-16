#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

using namespace std;

typedef long double ld;

template <typename T> ld calc_norm(vector<T> &a, vector<T> &b) {
  ld norm = 0;
  for (int i = 0; i < a.size(); ++i) {
    norm += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return sqrt(norm);
}

ld calc_error(vector<vector<int>> &a, vector<vector<ld>> &b) {
  ld error = 0;
  for (int i = 0; i < a.size(); ++i) {
    for (int j = i + 1; j < a.size(); ++j) {
      ld norm1 = calc_norm(a[i], a[j]);
      ld norm2 = calc_norm(b[i], b[j]);
      error += abs(norm1 - norm2);
    }
  }
  return error;
}

template <typename T> void read(vector<vector<T>> &in, int n, int m) {
  in.resize(n, vector<T>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> in[i][j];
    }
  }
}

ld calc_dispersion(vector<vector<int>> &in) {
  ld sqr = 0, mean = 0;
  for (int i = 0; i < in.size(); ++i) {
    for (int j = 0; j < in[0].size(); ++j) {
      sqr += in[i][j] * in[i][j];
      mean += in[i][j];
    }
  }
  int cnt = in.size() * in[0].size();
  sqr /= cnt;
  mean /= cnt;
  return sqr - mean * mean;
}

ld calc_grade(int n, int m, int k, ld error, ld dispersion) {
  ld del = (ld)n * (n - 1) / 2 * dispersion;
  return 10 - (error / del);
}

int main() {
  cout.precision(5);
  cout << fixed;

  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, m, k;
    vector<vector<int>> in;
    vector<vector<ld>> out;
    string add = "";
    add += (char)(i + '0');
    string s = "tests/test" + add + ".txt";
    cout << s << endl;
    freopen(s.c_str(), "r", stdin);
    cin >> n >> m >> k;
    cout << n << " "
         << " " << m << " " << k << endl;
    read(in, n, m);
    s = "answers/test" + add + ".txt";
    freopen(s.c_str(), "r", stdin);
    read(out, n, k);

    ld error = calc_error(in, out);
    ld disp = calc_dispersion(in);
    ld grade = calc_grade(n, m, k, error, disp);
    cout << error << " " << grade << endl << endl;
  }
}
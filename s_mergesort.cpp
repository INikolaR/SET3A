#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

mt19937 generator(42);
int total_comp = 0;
const int times = 100;

pair<int, int> LCPCompare(const string& a, const string& b, int k) {
    for (int i = k; i < a.size() && i < b.size(); i++) {
        ++total_comp;
        if (a[i] != b[i]) {
            return {a[i] - b[i], i};
        }
    }
    return {a.size() - b.size(), min(a.size(), b.size())};
}

vector<pair<string*, int> > stringMerge(vector<pair<string*, int> >& a, vector<pair<string*, int> >& b) {
    vector<pair<string*, int> > R;
    int i = 0;
    int j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i].second > b[j].second) {
            R.push_back(a[i]);
            ++i;
        } else if (a[i].second < b[j].second) {
            R.push_back(b[j]);
            ++j;
        } else {
            pair<int, int> p = LCPCompare(*a[i].first, *b[j].first, a[i].second);
            if (p.first < 0) {
                R.push_back(a[i]);
                ++i;
                b[j].second = p.second;
            } else {
                R.push_back(b[j]);
                ++j;
                a[i].second = p.second;
            }
        }
    }
    while (i < a.size()) {
        R.push_back(a[i]);
        ++i;
    }
    while (j < b.size()) {
        R.push_back(b[j]);
        ++j;
    }
    return R;
}

vector<pair<string*, int> > StringMergeSort(const vector<string*>& R) {
    if (R.empty()) {
        return vector<pair<string*, int> >();
    }
    if (R.size() == 1) {
        return {{R[0], 0}};
    }
    int m = R.size() / 2;
    vector<pair<string*, int> > P = StringMergeSort(vector<string*>(R.begin(), R.begin() + m));
    vector<pair<string*, int> > Q = StringMergeSort(vector<string*>(R.begin() + m, R.end()));
    return stringMerge(P, Q);
}

void measure(string input_file, string output_file_time, string output_file_comp) {
    ifstream fin;
    fin.open(input_file);
    ofstream fout_time, fout_comp;
    fout_time.open(output_file_time);
    fout_comp.open(output_file_comp);
    int n;
    while (fin >> n) {
        vector<string> s;
        s.reserve(n);
        for (int i = 0; i < n; i++) {
            string t;
            fin >> t;
            s.emplace_back(t);
        }
        vector<string> ss;
        vector<string*> sss(s.size(), nullptr);
        chrono::steady_clock::time_point begin, end;
        int total_time;
        for (int i = 0; i < times; ++i) {
            ss = vector<string>(s);
            total_comp = 0;
            for (int j = 0; j < ss.size(); ++j) {
                sss[j] = &ss[j];
            }
            begin = chrono::steady_clock::now();
            StringMergeSort(sss);
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/s_m_random.txt", "comp_result/s_m_random.txt");
    measure("test_data/reversed.txt", "time_result/s_m_reversed.txt", "comp_result/s_m_reversed.txt");
    measure("test_data/almost.txt", "time_result/s_m_almost.txt", "comp_result/s_m_almost.txt");
    return 0;
}
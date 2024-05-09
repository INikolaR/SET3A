#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

mt19937 generator(42);
int total_comp = 0;
const int times = 1;

vector<string*> MSDRadixSort(vector<string*>& R, int n) {
    if (R.empty()) {
        return vector<string*>();
    }
    vector<vector<string*> > RR(74, vector<string*>(0));
    vector<string*> excl;
    for (int i = 0; i < R.size(); i++) {
        if (R[i]->size() == n) {
            excl.emplace_back(R[i]);
        } else {
            ++total_comp;
            if ('0' <= (*R[i])[n] && (*R[i])[n] <= '9') {
                RR[(*R[i])[n] - '0'].emplace_back(R[i]);
            } else if ('a' <= (*R[i])[n] && (*R[i])[n] <= 'z') {
                RR[(*R[i])[n] - 'a' + 10].emplace_back(R[i]);
            } else if ('A' <= (*R[i])[n] && (*R[i])[n] <= 'Z') {
                RR[(*R[i])[n] - 'A' + 36].emplace_back(R[i]);
            } else if ((*R[i])[n] == '!') {
                RR[62].emplace_back(R[i]);
            } else if ((*R[i])[n] == '@') {
                RR[63].emplace_back(R[i]);
            } else if ((*R[i])[n] == '#') {
                RR[64].emplace_back(R[i]);
            } else if ((*R[i])[n] == '%') {
                RR[65].emplace_back(R[i]);
            } else if ((*R[i])[n] == ':') {
                RR[66].emplace_back(R[i]);
            } else if ((*R[i])[n] == ';') {
                RR[67].emplace_back(R[i]);
            } else if ((*R[i])[n] == '^') {
                RR[68].emplace_back(R[i]);
            } else if ((*R[i])[n] == '&') {
                RR[69].emplace_back(R[i]);
            } else if ((*R[i])[n] == '*') {
                RR[70].emplace_back(R[i]);
            } else if ((*R[i])[n] == '(') {
                RR[71].emplace_back(R[i]);
            } else if ((*R[i])[n] == ')') {
                RR[72].emplace_back(R[i]);
            } else if ((*R[i])[n] == '-') {
                RR[73].emplace_back(R[i]);
            } 
        }
    }
    vector<string*> ans;
    ans.reserve(R.size());
    ans.insert(ans.end(), excl.begin(), excl.end());
    for (int i = 0; i < 74; ++i) {
        RR[i] = MSDRadixSort(RR[i], n + 1);
        ans.insert(ans.end(), RR[i].begin(), RR[i].end());
    }
    return ans;
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
        for (int i = 0; i <= times; ++i) {
            ss = vector<string>(s);
            total_comp = 0;
            for (int j = 0; j < ss.size(); ++j) {
                sss[j] = &ss[j];
            }
            begin = chrono::steady_clock::now();
            MSDRadixSort(sss, 0);
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/r_random.txt", "comp_result/r_random.txt");
    // measure("test_data/reversed.txt", "time_result/r_reversed.txt", "comp_result/r_reversed.txt");
    // measure("test_data/almost.txt", "time_result/r_almost.txt", "comp_result/r_almost.txt");
    return 0;
}
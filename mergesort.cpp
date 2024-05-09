#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

mt19937 generator(42);
int total_comp = 0;
const int times = 100;

bool operator==(const string& lhs, const string& rhs) {
    int i = 0;
    while (i < lhs.length() && i < rhs.length()) {
        ++total_comp;
        if (lhs[i] != rhs[i]) {
            return false;
        }
        ++i;
    }
    return lhs.length() == rhs.length();
}

bool operator!=(const string& lhs, const string& rhs) {
    return !(lhs == rhs);
}

bool operator<(const string& lhs, const string& rhs) {
    int i = 0;
    while (i < lhs.length() && i < rhs.length()) {
        ++total_comp;
        if (lhs[i] != rhs[i]) {
            return lhs[i] < rhs[i];
        }
        ++i;
    }
    return lhs.length() < rhs.length();
}

bool operator>(const string& lhs, const string& rhs) {
    int i = 0;
    while (i < lhs.length() && i < rhs.length()) {
        ++total_comp;
        if (lhs[i] != rhs[i]) {
            return lhs[i] > rhs[i];
        }
        ++i;
    }
    return lhs.length() > rhs.length();
}

bool operator<=(const string& lhs, const string& rhs) {
    int i = 0;
    while (i < lhs.length() && i < rhs.length()) {
        ++total_comp;
        if (lhs[i] != rhs[i]) {
            return lhs[i] < rhs[i];
        }
        ++i;
    }
    return lhs.length() <= rhs.length();
}

bool operator>=(const string& lhs, const string& rhs) {
    int i = 0;
    while (i < lhs.length() && i < rhs.length()) {
        ++total_comp;
        if (lhs[i] != rhs[i]) {
            return lhs[i] > rhs[i];
        }
        ++i;
    }
    return lhs.length() >= rhs.length();
}

void merge(vector<string*>::iterator first1, vector<string*>::iterator last1,
           vector<string*>::iterator first2, vector<string*>::iterator last2,
           vector<string*>::iterator d_first) {
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            copy(first1, last1, d_first);
            return;
        }
        if (*(*first2) < *(*first1)) {
            *d_first = *first2;
            ++first2;
        }
        else {
            *d_first = *first1;
            ++first1;
        }
    }
    std::copy(first2, last2, d_first);
}

void mergeSort(vector<string*>& a, int start, int end) {
    if (start + 1 == end) {
        return;
    }
    int middle = (start + end) / 2;
    mergeSort(a, start, middle);
    mergeSort(a, middle, end);
    vector<string*> c(end - start);
    merge(a.begin() + start, a.begin() + middle, a.begin() + middle, a.begin() + end, c.begin());
    copy(c.begin(), c.end(), a.begin() + start);
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
            mergeSort(sss, 0, sss.size());
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/m_random.txt", "comp_result/m_random.txt");
    measure("test_data/reversed.txt", "time_result/m_reversed.txt", "comp_result/m_reversed.txt");
    measure("test_data/almost.txt", "time_result/m_almost.txt", "comp_result/m_almost.txt");
    return 0;
}
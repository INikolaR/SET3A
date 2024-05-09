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

int partition(vector<string>& a, int start, int end){
    swap(a[start], a[generator() % (end - start) + start]);
	string pivot = a[start];
    int left = start + 1;
    int right = end - 1;
    while (true) {
        while (left < end && a[left] < pivot) {
            ++left;
        }
        while (right >= left && a[right] >= pivot) {
            --right;
        }
        if (right < left) {
            break;
        }
        swap(a[left], a[right]);
    }
    swap(a[start], a[right]);
    return right;
}

void quickSort(vector<string>& a, int start, int end) {
	if (start >= end - 1) {
        return;
    }
    int pivot = partition(a, start, end);
    quickSort(a, start, pivot);
    quickSort(a, pivot + 1, end);
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
        chrono::steady_clock::time_point begin, end;
        int total_time;
        for (int i = 0; i < times; ++i) {
            ss = vector<string>(s);
            total_comp = 0;
            begin = chrono::steady_clock::now();
            quickSort(ss, 0, ss.size());
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/q_random.txt", "comp_result/q_random.txt");
    measure("test_data/reversed.txt", "time_result/q_reversed.txt", "comp_result/q_reversed.txt");
    measure("test_data/almost.txt", "time_result/q_almost.txt", "comp_result/q_almost.txt");
    return 0;
}
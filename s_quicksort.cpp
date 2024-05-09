#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

mt19937 generator(42);
int total_comp = 0;
const int times = 100;

// compares strings pretending that first n symbols are equal (a < b marked with return value < 0)
int ncmp(const string& a, const string& b, int n) {
    if (a.length() <= n) {
        if (b.length() <= n) {
            return 0;
        } else {
            return -1;
        }
    } else {
        if (b.length() <= n) {
            return 1;
        } else {
            ++total_comp;
            return a[n] - b[n];
        }
    }
}

pair<int, int> partition(vector<string>& a, int start, int end, int n) {
    swap(a[start], a[generator() % (end - start) + start]); // putting pivot to start
	string pivot = a[start]; // here is pivot
    // filtering elements that are < pivot (considering only n first symbols)
    int left = start + 1;
    int right = end - 1;
    while (true) {
        while (left < end && ncmp(a[left], pivot, n) < 0) {
            ++left;
        }
        while (right >= left && ncmp(a[right], pivot, n) >= 0) {
            --right;
        }
        if (right < left) {
            break;
        }
        swap(a[left], a[right]);
    }
    swap(a[start], a[right]);
    int first_ge = right; // first element that is >= pivot
    // filtering elements that are == pivot (considering only n first symbols)
    left = right;
    right = end - 1;
    while (true) {
        while (left < end && ncmp(a[left], pivot, n) == 0) {
            ++left;
        }
        while (right >= left && ncmp(a[right], pivot, n) > 0) {
            --right;
        }
        if (right < left) {
            break;
        }
        swap(a[left], a[right]);
    }
    return {first_ge, left}; // a[start..first_ge - 1] is < pivot;
                                // a[first_ge..left - 1] is == pivot;
                                // a[left..end - 1] is > pivot
}

void quickSort(vector<string>& a, int start, int end, int n) {
    // if all len(elem) are < n then elems are all equal
    bool b = true;
    for (int i = start; i < end; i++) {
        if (a[i].length() > n) {
            b = false;
            break;
        }
    }
    if (b) {
        return;
    }
	if (start >= end - 1) {
        return;
    }
    pair<int, int> pivot = partition(a, start, end, n);
    quickSort(a, start, pivot.first, n);
    quickSort(a, pivot.first, pivot.second, n + 1);
    quickSort(a, pivot.second, end, n);
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
        for (int i = 0; i <= times; ++i) {
            ss = vector<string>(s);
            total_comp = 0;
            begin = chrono::steady_clock::now();
            quickSort(ss, 0, ss.size(), 0);
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/s_q_random.txt", "comp_result/s_q_random.txt");
    measure("test_data/reversed.txt", "time_result/s_q_reversed.txt", "comp_result/s_q_reversed.txt");
    measure("test_data/almost.txt", "time_result/s_q_almost.txt", "comp_result/s_q_almost.txt");
    return 0;
}
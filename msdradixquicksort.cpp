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

pair<int, int> partition(vector<string*>& a, int start, int end, int n) {
    swap(a[start], a[generator() % (end - start) + start]); // putting pivot to start
	string pivot = *a[start]; // here is pivot
    // filtering elements that are < pivot (considering only n first symbols)
    int left = start + 1;
    int right = end - 1;
    while (true) {
        while (left < end && ncmp(*a[left], pivot, n) < 0) {
            ++left;
        }
        while (right >= left && ncmp(*a[right], pivot, n) >= 0) {
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
        while (left < end && ncmp(*a[left], pivot, n) == 0) {
            ++left;
        }
        while (right >= left && ncmp(*a[right], pivot, n) > 0) {
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

void quickSort(vector<string*>& a, int start, int end, int n) {
    // if all len(elem) are < n then elems are all equal
    bool b = true;
    for (int i = start; i < end; i++) {
        if ((*a[i]).length() > n) {
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

vector<string*> MSDRadixQuickSort(vector<string*>& R, int n) {
    if (R.empty()) {
        return vector<string*>();
    }
    if (R.size() < 74) {
        quickSort(R, 0, R.size(), 0);
        return R;
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
        RR[i] = MSDRadixQuickSort(RR[i], n + 1);
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
            MSDRadixQuickSort(sss, 0);
            end = chrono::steady_clock::now();
            total_time += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        }
        fout_time << n << " " << total_time / times << endl;
        fout_comp << n << " " << total_comp << endl;
        
    }
}

int main() {
    measure("test_data/random.txt", "time_result/r_q_random.txt", "comp_result/r_q_random.txt");
    measure("test_data/reversed.txt", "time_result/r_q_reversed.txt", "comp_result/r_q_reversed.txt");
    measure("test_data/almost.txt", "time_result/r_q_almost.txt", "comp_result/r_q_almost.txt");
    return 0;
}
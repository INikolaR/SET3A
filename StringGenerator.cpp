#include <bits/stdc++.h>

using namespace std;

mt19937 generator(42);

class StringGenerator {
public:
    vector<string> random(int sz) {
        vector<string> res;
        res.reserve(sz);
        for (int i = 0; i < sz; i++) {
            stringstream ss;
            int size_of_string = generator() % 191 + 10; // random number in [10, 200]
            for (int j = 0; j < size_of_string; j++) {
                int num = generator() % 74; // 74 is the size of alphabet
                if (num < 10) { // 0-9 equals 0-9
                    ss << static_cast<char>('0' + num);
                } else if (num < 36) { // 10-35 equals a-z
                    ss << static_cast<char>('a' + num - 10);
                } else if (num < 62) { // 36-61 equals A-Z
                    ss << static_cast<char>('A' + num - 36);
                } else { // 62-73 equals !@#%:;^&*()-
                    ss << additional_alphabet_[num - 62];
                }
            }
            res.emplace_back(ss.str());
        }
        return res;
    }
    vector<string> reversed(int sz) {
        vector<string> res = random(sz);
        sort(res.begin(), res.end(), StringGenerator::cmp);
        return res;
    }
    vector<string> almost(int sz) {
        vector<string> res = random(sz);
        sort(res.begin(), res.end());
        int number_of_replacing = generator() % (sz / 100); // one replace per 100 elems
        for (int i = 0; i < number_of_replacing; ++i) {
            int l = generator() % sz;
            int r = generator() % sz;
            swap(res[l], res[r]);
        }
        return res;
    }
    vector<vector<string> > multiple_random(int start, int end, int step) {
        vector<string> sample = random(end);
        vector<vector<string> > res;
        res.reserve((end - start) % step + 1);
        for (int i = start; i < end; i += step) {
            res.emplace_back(vector<string>(sample.begin(), sample.begin() + i));
        }
        return res;
    }
    vector<vector<string> > multiple_reversed(int start, int end, int step) {
        vector<string> sample = reversed(end);
        vector<vector<string> > res;
        res.reserve((end - start) % step + 1);
        for (int i = start; i < end; i += step) {
            res.emplace_back(vector<string>(sample.begin(), sample.begin() + i));
        }
        return res;
    }
    vector<vector<string> > multiple_almost(int start, int end, int step) {
        vector<string> sample = almost(end);
        vector<vector<string> > res;
        res.reserve((end - start) % step + 1);
        for (int i = start; i < end; i += step) {
            res.emplace_back(vector<string>(sample.begin(), sample.begin() + i));
        }
        return res;
    }
private:
    static bool cmp(string& a, string& b) {
        return a > b;
    }
    string additional_alphabet_ = "!@#%:;^&*()-";
};

int main() {
    StringGenerator gen = StringGenerator();
    vector<vector<string> > random = gen.multiple_random(100, 3000, 100);
    ofstream fout;
    fout.open("random.txt");
    for (int i = 0; i < random.size(); i++) {
        fout << random[i].size() << " ";
        for (int j = 0; j < random[i].size(); ++j) {
            fout << random[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    vector<vector<string> > reversed = gen.multiple_reversed(100, 3000, 100);
    fout.open("reversed.txt");
    for (int i = 0; i < reversed.size(); i++) {
        fout << reversed[i].size() << " ";
        for (int j = 0; j < reversed[i].size(); ++j) {
            fout << reversed[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    vector<vector<string> > almost = gen.multiple_almost(100, 3000, 100);
    fout.open("almost.txt");
    for (int i = 0; i < almost.size(); i++) {
        fout << almost[i].size() << " ";
        for (int j = 0; j < almost[i].size(); ++j) {
            fout << almost[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
    return 0;
}
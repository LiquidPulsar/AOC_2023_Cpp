#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <string.h>
#include <cstring>
#include <unordered_set>

#include <stdexcept>

using namespace std;

int main(int argc, char const *argv[])
{
    std::cout << argc << " args" << endl;
    if (argc < 2) {
        std::cout << "No part entered";
        return 1;
    }
    regex pat("(\\d+)");

    ifstream file(string(argc>2 ? argv[2] : "input") + ".txt");

    string line;
    // cout << (bool) getline(file, line) << "\n";
    // cout << line << "\n";
    // cout << string(argc>1 ? argv[1] : "test") + ".txt";
    int tot = 0;
    
    // WSL vsc doesnt like my strlen :3
    if (argv[1] == nullptr 
        || *(argv[1]+1) != 0 
        || *argv[1]<'1' 
        || *argv[1]>'2') {
        std::cout << "Invalid part specified\n";
        return 1;
    }
    // switch ((*argv[1]) * (strlen(argv[1])==1))

    if (*argv[1] == '1') {
        while (getline(file, line)) {
            // cout << line << "\n";
            int colon = line.find(':');
            int bar = line.find('|');
            unordered_set win = unordered_set<int>();
            string first_half = line.substr(colon,bar-colon);
            string second_half = line.substr(bar);

            auto words_begin = sregex_iterator(first_half.begin(), first_half.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                win.insert(stoi(match[1]));
            }

            int score = 0;
            words_begin = sregex_iterator(second_half.begin(), second_half.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                int c = stoi(match[1]);
                if (win.contains(c)) {
                    score = score==0 ? 1 : score<<1;
                }
            }
            tot += score;
            // cout << score << endl;

        }    
        std::cout << tot << endl;
    } else {
        int map[200] = {0};
        int counts[200] = {0};
        int l = 0;
        while (getline(file, line)) {
            counts[l]++;
            // cout << line << "\n";
            int colon = line.find(':');
            int bar = line.find('|');
            unordered_set win = unordered_set<int>();
            string first_half = line.substr(colon,bar-colon);
            string second_half = line.substr(bar);

            auto words_begin = sregex_iterator(first_half.begin(), first_half.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                win.insert(stoi(match[1]));
            }

            int score = 0;
            words_begin = sregex_iterator(second_half.begin(), second_half.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                int c = stoi(match[1]);
                if (win.contains(c)) {
                    map[l] += 1;
                }
            }
            l++;
        }    
        for (int i=0; i<200; i++) {
            int n = counts[i];
            tot += n;
            for (int j=i+1; j<i+map[i]+1; j++) {
                counts[j] += n;
            }

            // std::cout << n << " ";
        }
        // std::cout << endl;
        std::cout << tot << endl;
    }
    
}
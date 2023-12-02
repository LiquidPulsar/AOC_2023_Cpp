#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <string.h>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << argc << " args" << endl;
    if (argc < 2) {
        cout << "No part entered";
        return 1;
    }
    string nums[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    map<string, int> m{};
    ostringstream s;
    s << "(?=(\\d";

    for (size_t i = 0; i < sizeof(nums)/sizeof(*nums); i++)
    {
        m[nums[i]] = m[to_string(i)] = i;
        s << '|' << nums[i];
    }
    s << "))";
    regex pat(s.str());

    // cout << s.str() << "\n";

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
        cout << "Invalid part specified\n";
        return 1;
    }
    // switch ((*argv[1]) * (strlen(argv[1])==1))

    while (getline(file, line)) {
        // cout << line << "\n";
        int first = -1, last;
        if (*argv[1] == '1') {
            for (char c : line) {
                if ('0'<=c && c<='9') {
                    if (first==-1) first = c-'0';
                    last = c-'0';
                }
            }
        } else {
            auto words_begin = sregex_iterator(line.begin(), line.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                string s = match[1];
                // cout << s << "\n";
                if (m.contains(s)) {
                    // cout << s << " was in the map\n";
                    if (first==-1) first = m[s];
                    last = m[s];
                }
            }
        }

        if (first == -1)
        {
            cout << "line " << line << " had no ints!\n";
            return 0;
        }
        tot += 10 * first + last;
    }    
    cout << tot << endl;
}

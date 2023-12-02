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
    regex pat("(\\d+) ([rgb])");

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

    int game = 1;
    while (getline(file, line)) {
        // cout << line << "\n";
        int r,g,b;
        r = g = b = 0;

        auto words_begin = sregex_iterator(line.begin(), line.end(), pat);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); i++) {
                smatch match = *i;
                int amt = stoi(match[1]);
                string col = match[2];
                char c = col[0];
                
                switch (c) {
                    case 'r':
                        r = max(r,amt);
                        break;
                    case 'g':
                        g = max(g,amt);
                        break;
                    case 'b':
                        b = max(b,amt);
                        break;
                }
            }
        // cout << r << " " << g << " " << b << "\n";
        if (*argv[1] == '1') {
            tot += (r<=12 && g<=13 && b<=14) * game++;
        } else {
            tot += r * g * b;
        }
    }    
    cout << tot << endl;
}

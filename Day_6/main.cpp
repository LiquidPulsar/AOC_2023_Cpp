#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <string.h>
#include <cstring>
#include <math.h>

using namespace std;

string no_spaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

int winners(int64_t t, int64_t d) {
    double s,l,r;
    s = sqrt(t*t - 4*d);
    l = (t - s)/2 + 1e-9; // Roots on exact boundary, so shift by epsilon for >
    r = (t + s)/2 - 1e-9;
    return floor(r) - ceil(l) + 1;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cout << "No part entered";
        return 1;
    }

    ifstream file(string(argc>2 ? argv[2] : "input") + ".txt");
    string dline, tline;

    // WSL vsc doesnt like my strlen :3
    if (argv[1] == nullptr 
        || *(argv[1]+1) != 0 
        || *argv[1]<'1' 
        || *argv[1]>'2') {
        cout << "Invalid part specified\n";
        return 1;
    }

    bool part_1 = *argv[1] == '1';

    getline(file, tline);
    tline = tline.substr(5);

    getline(file, dline);
    dline = dline.substr(9);

    if (!part_1) {
        tline = no_spaces(tline);
        dline = no_spaces(dline);
    }

    stringstream tstream(tline);
    stringstream dstream(dline);

    int64_t t,d;
    int prod = 1;
    while (tstream >> t) {
        dstream >> d;
        prod *= winners(t,d);
    }
    cout << prod;
}
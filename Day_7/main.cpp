#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <string.h>
#include <cstring>
#include <math.h>

using namespace std;

typedef pair<pair<int,string>,int> Hand;

static string no_spaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

static int rate_hand(string hand, bool part_1) {
    map<char,int> M;
    for(char c: hand)
        M[c] = (M.find(c) == M.end()) ? 1 : M[c]+1;
    
    int best,snd_best,jacks;
    best = snd_best = 0;
    jacks = (M.find('J') == M.end()) ? 0 : M['J'];

    for(auto it = M.cbegin(); it != M.cend(); ++it) {
        if (!part_1 && it->first == 'J') continue;
        if (it->second > best) {
            snd_best = best;
            best = it->second;
        } else if (it->second > snd_best) {
            snd_best = it->second;
        }
    }
    if (!part_1) {
        best += jacks;
    }
    // cout << best << ' ' << snd_best << endl;
    return best*3 + snd_best;
}

int winners(int64_t t, int64_t d) {
    double s,l,r;
    s = sqrt(t*t - 4*d);
    l = (t - s)/2 + 1e-9; // Roots on exact boundary, so shift by epsilon for >
    r = (t + s)/2 - 1e-9;
    return floor(r) - ceil(l) + 1;
}

int score(char c, bool part_1) {
    if ('2'<=c && c<='9') return c - '0';
    switch (c)
    {
    case 'T': return 10;
    case 'J': return part_1 ? 11 : 0;
    case 'Q': return 12;
    case 'K': return 13;
    case 'A': return 14;
    }
    throw invalid_argument("Invalid card!");
}

bool lt(string a, string b, bool part_1) {
    int s_a,s_b;
    for (size_t i = 0; i < 5; i++)
    {
        s_a = score(a[i],part_1);   
        s_b = score(b[i],part_1); 
        if (s_a != s_b) return s_a < s_b;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cout << "No part entered";
        return 1;
    }

    ifstream file(string(argc>2 ? argv[2] : "input") + ".txt");
    string line;

    // WSL vsc doesnt like my strlen :3
    if (argv[1] == nullptr 
        || *(argv[1]+1) != 0 
        || *argv[1]<'1' 
        || *argv[1]>'2') {
        cout << "Invalid part specified\n";
        return 1;
    }

    bool part_1 = *argv[1] == '1';

    vector<Hand> hands;
    while (!file.eof()) {
        getline(file, line);
        stringstream stream(line);
        string hand;
        int bet;
        stream >> hand >> bet;

        hands.push_back(pair(
            pair(
                rate_hand(hand,part_1),
                hand
            ), bet
        ));
        // cout << hand << bet << '\n'; 
    }

    sort(hands.begin(),hands.end(),[part_1](Hand a, Hand b){
        return (a.first.first == b.first.first)
                ? lt(a.first.second,b.first.second,part_1)
                : a.first < b.first;
    });

    // for (Hand hand: hands) {
    //     cout << hand.first.first << ' ' << hand.first.second << ' ' << hand.second << endl;
    // }

    int tot = 0;
    for (size_t i = 0; i < hands.size(); i++)
    {
        tot += hands[i].second * (i+1);
    }
    cout << tot;
    
}
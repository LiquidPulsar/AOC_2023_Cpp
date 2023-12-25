#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <string.h>
#include <cstring>
#include <inttypes.h>

#define INF INT32_MAX;

using namespace std;

typedef int64_t Int;

typedef struct {
    Int lo;
    Int hi;
    Int ofs; // can be ignored
} Range;

typedef vector<Range> RangeMap;

static inline Range shift_by(Range r, Int o) {
    return {
        r.lo + o,
        r.hi + o,
        r.ofs
    };
}

static Int lookup(RangeMap rm, Int x) {
    for (Range r: rm) {
        if (r.hi > x) {
            return (r.lo <= x) ? x + r.ofs : x;
        }
    }
    return x;
}

static vector<Range> lookup_range(RangeMap rm, Range x) {
    vector<Range> out;
    for (Range r: rm) {
        if (x.hi < r.lo) { // Too far left
            out.push_back({x.lo,x.hi});
            return out;
        } else if (x.lo >= r.hi) {
            
        } else if (x.hi < r.hi) {
            if (x.lo < r.lo) {
                out.push_back({x.lo,r.lo});
                out.push_back(shift_by({r.lo,x.hi},r.ofs));
            } else {
                out.push_back(shift_by(x,r.ofs));
            }
            return out;
        } else { // r.hi <= x.hi
            if (x.lo < r.lo) {
                out.push_back({x.lo,r.lo});
                out.push_back(shift_by({r.lo,r.hi},r.ofs));
            } else {
                out.push_back(shift_by({x.lo,r.hi},r.ofs));
            }
            x = {r.hi,x.hi};
        }
    }
    out.push_back({x.lo,x.hi});
    return out;
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

    vector<RangeMap> rms;

    getline(file, line);
    stringstream stream(line.substr(6));

    vector<Int> seeds;
    vector<Range> seed_ranges;
    while (stream) {
        Int x;
        stream >> x;
        seeds.push_back(x);
    }

    // Why is the last elem duplicated?
    // I guess it is to do with pulling smth
    // off the stream
    seeds.pop_back();

    for (size_t i = 0; i < seeds.size(); i+=2)
    {
        seed_ranges.push_back({
            seeds[i],
            seeds[i] + seeds[i+1]
        });
    }    

    getline(file, line);

    while (getline(file, line)) {
        RangeMap rm;
        while (getline(file, line) && line.length() > 1) {
            stringstream stream(line);
            Int d,s,r;
            stream >> d >> s >> r;
            rm.push_back({s,s+r,d-s});
        }
        sort(rm.begin(), rm.end(), [](Range a, Range b){
            return a.lo < b.lo;
        });
        rms.push_back(rm);
    }

    if (part_1) {
        Int lowest = INF;
        for (Int s: seeds) {
            for (RangeMap rm: rms)
                s = lookup(rm, s);
            lowest = min(lowest,s);
        }
        cout << lowest << '\n';
    } else {
        for (RangeMap rm: rms) {
            vector<Range> next;
            for (Range s: seed_ranges) {
                auto tmp = lookup_range(rm, s);
                next.reserve(next.size() + distance(tmp.begin(), tmp.end()));
                next.insert(next.end(),tmp.begin(), tmp.end());
            }
            seed_ranges = next;
        }

        Int lowest = INF;
        for (Range r: seed_ranges) {
            lowest = min(lowest,r.lo);
        }
        cout << lowest << '\n';
    }
}

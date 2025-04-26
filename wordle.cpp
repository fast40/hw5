#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void get_all_possible_strings(const std::string &in, const std::string &floating, int unknowns, int i, std::set<std::string> &dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
        std::set<std::string> all_possible;

        int unknowns = 0;

        for (int i = 0; i < in.size(); i++) {
                if (in[i] == '-') {
                        unknowns++;
                }
        }

        // cout << unknowns << endl;
        // cout << in << endl;
        // cout << floating << endl;

        get_all_possible_strings(in, floating, unknowns, 0, all_possible);

        std::set<std::string> result;

        for (std::string value : all_possible) {
                if (dict.find(value) != dict.end()) {
                        result.insert(value);
                }
        }

        return result;

}

// Define any helper functions here

void get_all_possible_strings(const std::string &in, const std::string &floating, int unknowns, int i, std::set<std::string> &result) {
        if (i >= in.size()) {
                result.insert(in);
                return;
        }

        if (in[i] != '-') {
                get_all_possible_strings(in, floating, unknowns, i+1, result);
                return;
        }

        if (floating.size() == unknowns) {
                for (int fi = 0; fi < unknowns; fi++) {
                        get_all_possible_strings(in.substr(0, i) + floating[fi] + in.substr(i+1), floating.substr(0, fi) + floating.substr(fi+1), unknowns-1, i+1, result);
                }
        }
        else {
                for (char c = 'a'; c <= 'z'; c++) {
                        int index = floating.find(c);
                        if (index == std::string::npos) {
                                get_all_possible_strings(in.substr(0, i) + c + in.substr(i+1), floating, unknowns-1, i+1, result);
                        }
                        else {
                                get_all_possible_strings(in.substr(0, i) + c + in.substr(i+1), floating.substr(0, index) + floating.substr(index+1), unknowns-1, i+1, result);
                        }
                }
        }
}

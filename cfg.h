/*
Jamison Hubbard
CFG Implementation
CSCI 498A Compilers
Feb 2020

cfg.h
*/

#ifndef CFG_H
#define CFG_H

using namespace std;

#include <string>
#include <vector>
#include <map>
#include <set>

class CFG {
    public:
    // Constructor
    CFG(string filename);

    // Internal methods
    bool isTerminal(string symbol);

    // getters
    set<string> getNT(); // get nonterminals
    set<string> getT(); // get terminals
    vector<string> getProductionsFor(string nonterminal);
    vector<string> getRHSOccurencesFor(string symbol);

    // testing methods
    void printMap();
    void testDerivesToLambda();

    // cfg algorithms
    bool derivesToLambda(string nonTerm, map<string, vector<string>> &ruleStack);
    set<string> firstSet(string nonTerm);
    set<string> followSet(string symbol);

    private:
    map<string, vector<string>> cfgMap;
    set<string> nonterminals;
    set<string> terminals;
    string startNonterminal;
};

#endif /* CFG_H */
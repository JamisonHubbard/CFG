/*
Jamison Hubbard
CFG Implementation 
CSCI 498A Compilers
Feb 2020

cfg.cpp
*/

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "cfg.h"

// Constructor

CFG::CFG(string filename) {

    ifstream fileIn(filename);
    if (!fileIn) exit(1);

    string line;
    string currentNT;

    while (getline(fileIn, line)) {

        istringstream lineIn(line);
        string first, second, temp, rule;
        vector<string> lineEnd, currentRule;

        lineIn >> first;
        lineIn >> second;
        while (lineIn >> temp) lineEnd.push_back(temp);

        if (first == "|") {
            currentRule = cfgMap[currentNT];
            rule = second;
            if (isTerminal(rule)) terminals.insert(rule);
            else nonterminals.insert(rule);
        }
        else {
            if (cfgMap.find(first) == cfgMap.end()) {
                currentNT = first;
                if (isTerminal(currentNT)) terminals.insert(currentNT);
                else nonterminals.insert(currentNT);
            }
            else {
                currentRule = cfgMap[currentNT];
            }
        }

        for (int i = 0; i < lineEnd.size(); ++i) {
                
            if (lineEnd[i] == "|") {
                currentRule.push_back(rule);
                rule = "";
                continue;
            }

            if (lineEnd[i] == "$") {
                if (startNonterminal != "") exit(2);
                startNonterminal = currentNT;
                break;
            }

            if (rule != "") rule += " ";
            rule +=  lineEnd[i];

            if (isTerminal(lineEnd[i])) terminals.insert(lineEnd[i]);
            else nonterminals.insert(lineEnd[i]);
        }

        currentRule.push_back(rule);
        cfgMap[currentNT] = currentRule;
    }

    fileIn.close();
    terminals.erase("lambda");
}

// Internal Methods

bool CFG::isTerminal(string symbol) {
    char first = symbol[0];
    return !(isupper(first));
}

// Getters

set<string> CFG::getNT() {return nonterminals;}
set<string> CFG::getT() {return terminals;}

vector<string> CFG::getProductionsFor(string nonterminal) {
    if (nonterminals.find(nonterminal) == nonterminals.end()) exit (3);

    return cfgMap[nonterminal];
}

vector<string> CFG::getRHSOccurencesFor(string symbol) {
    vector<string> occurences;

    map<string, vector<string>>::iterator mit = cfgMap.begin();
    for (pair<string, vector<string>> nonterm : cfgMap) {
        for (int i = 0; i < nonterm.second.size(); ++i) {
            string rhs = nonterm.second[i];
            istringstream rhsIn(rhs);
            bool inRHS = false;
            string word;

            while (rhsIn >> word) {
                if (word == symbol) inRHS = true;
            }

            if (inRHS) occurences.push_back(rhs);
        }
    }

    return occurences;
}

// Test Methods

void CFG::printMap() {
    int ruleCount = 1;
    map<string, vector<string>>::iterator mit = cfgMap.begin();
    for (pair<string, vector<string>> row : cfgMap) {
        bool barNeeded = false;
        cout << to_string(ruleCount) << "   " << row.first << " -> ";
        for (int i = 0; i < row.second.size(); ++i) {
            if (barNeeded) cout << to_string(ruleCount) << "      | ";
            else barNeeded = true;

            cout << row.second[i] << endl;
            ruleCount++;
        }
    }

    cout << endl << "Start Symbol:   " << startNonterminal << endl << endl;
    cout << "Terminals:      ";
    set<string>::iterator sit = terminals.begin();
    for (string term : terminals) {
        cout << term << " ";
    }
    cout << endl << endl << "Nonterminals:   ";
    sit = nonterminals.begin();
    for (string nonterm : nonterminals) {
        cout << nonterm << " ";
    }
    cout << endl;
}
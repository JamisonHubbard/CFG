/*
Jamison Hubbard
CFG Implementation
CSCI 498A Compilers 
Feb 2020

main.cpp
*/

#include <iostream>
#include <string>

#include "cfg.h"

using namespace std;

int main(int argc, char *argv[]) {

    string filename = "test1.cfg";
    CFG grammar(filename);
    grammar.printMap();

    vector<string> testProductions = grammar.getProductionsFor("E");
    vector<string> testOccurences = grammar.getRHSOccurencesFor("A");

    cout << endl << "Productions for E: " << endl;
    for (int i = 0; i < testProductions.size(); ++i) {
        cout << testProductions[i] << endl;
    }
    cout << endl << "Occurences of A: " << endl;
    for (int i = 0; i < testOccurences.size(); ++i) {
        cout << testOccurences[i] << endl;
    }

    return 0;
}
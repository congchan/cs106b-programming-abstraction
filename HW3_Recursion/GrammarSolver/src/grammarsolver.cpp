/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 *
 * Assignment 3B: Grammar Solver
 * Write a function for generating random sentences from a grammar.
 * The function accepts a reference to an input file representing a language grammar,
 * along with a symbol to randomly generate and the number of times to generate it.
 * Your function should generate the given number of random expansions of the given symbol and return them as a Vector of strings.
 *
 * @Author: Cong Chen
 * @Version: 2017/06
 */

#include "grammarsolver.h"
#include "map.h"
#include "vector.h"
#include "random.h"

using namespace std;
/* Generating Random Expansions from the Grammar
 * Rrecursively walking the GrammarMap data to generate elements by successively expanding them.
 * This program return the string containing the terminal word
 */
void findTerminal(Map<string, Vector<Vector<string> > > &grammarMap, string symbol, string& expansion) {
    if (grammarMap.containsKey(symbol)) {
        //randomly pick a rule according to the key symbol
        Vector<Vector<string> > rules = grammarMap[symbol];
        Vector<string> ruleVector = rules[randomInteger(0,rules.size()-1)];
        for (string element:ruleVector) {
            findTerminal(grammarMap,element,expansion);
        }
    } else {
        expansion += symbol+" ";
    }
}


/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    /* Part 1: Reading the Input File
     * Read an input file with a grammar in Backus-Naur Form and turns its contents into a map;*/
    Map<string, Vector<Vector<string> > > grammarMap;
    while (true) {
        string line;
        getline(input, line);
        if(input.fail()) break;
        Vector<string> ruleVector = stringSplit(line, "::=");
        string key = ruleVector[0];
        string value = ruleVector[1];
        Vector<Vector<string> > lineVector;
        for (string element:stringSplit(value,"|")) {
            ruleVector = stringSplit(element," ");
            lineVector.add(ruleVector);
        }
        grammarMap.add(key,lineVector);

    }

    /* Part 2: Generating Random Expansions from the Grammar
     * Rrecursively walking the GrammarMap data to generate elements by successively expanding them. */
    Vector<string> output;

    for (int i=1;i<=times;i++) {
        string expansion;
        findTerminal(grammarMap,symbol,expansion);
        output.add(trimEnd(expansion));
    }

    return output;

    /*return {};           */// This is only here so it will compile
}

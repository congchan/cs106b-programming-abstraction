/* File: ngrams.cpp
 * CS 106B assignment2 Part B: Random Writter
 * This programme reads in a source text and build an order k Markov model called "N- grams" for it,
 * and generate random output that follows the frequency patterns of the model.
 * So that the new text that sounds like it came from the same author as that file.
 *
 * @Author: Cong Chen
 * @Version: 2017/06
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
#include "map.h"
#include "vector.h"
#include <simpio.h>
#include "filelib.h"
#include "tokenscanner.h"

using namespace std;
Map<Vector<string>,Vector<string> > buildNGrams(Vector<string> &letters,int N) {
    //This function create and return the ngram map
    Map<Vector<string>,Vector<string> > map;
    Vector<string> prefixes(N-1," ");
    string suffix;
    for (int i=0;i<letters.size();i++) {
        int k = i;
        //The current prefixes will be a new key if never appear before
        for (int j=0;j<prefixes.size();j++) {
            prefixes[j]=letters[k%letters.size()];
            suffix = letters[(k+1)%letters.size()];
            k++;
        }
        Vector<string> suffixes;
        if (map.containsKey(prefixes) ) {
            suffixes = map.get(prefixes);
        }
        suffixes.add(suffix);
        map.put(prefixes, suffixes);
    }
    //cout << letters << endl;
    //cout << map << endl;
    return map;
}

int main() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams').This program makes random text based on a document."
            "Give me an input file and an 'N' value for groups of words, and I'll create random text for you." << endl;
    //Check for valid input filename
    string fileName;
    while (true) {
       cout << "Input file name?" << endl;
       fileName = getLine();
       if (fileExists(fileName)) {
           break;
       }
       cout << "Unable to open that file.  Try again." << endl;
    }
    //Loading the content from source file into a vector
    ifstream in;
    in.open(fileName);
    TokenScanner scanner(in);
    scanner.ignoreWhitespace();
    //scanner.addWordCharacters("\n");
    Vector<string> letters;
    while (scanner.hasMoreTokens()) {
        letters.add(scanner.nextToken());
    }
    in.close();

    //Check for valid input N-Grams for N
    int N;
    while (true) {
       cout << "Value of N?" << endl;
       N = getInteger();
       if (N<2) {
           cout << "N must be 2 or greater." << endl;
           continue;
       }       
       break;
    }

    //Step 1: Building Map of N-Grams
    Map<Vector<string>,Vector<string> > map = buildNGrams(letters,N);
    Vector< Vector<string> > key = map.keys();

    //Step 2: Generating Random Text， user defines the text length
    int wlength;
    while (true) {
        cout << "# of random words to generate (0 to quit)?" << endl;
        wlength = getInteger();
        if  (wlength==0) {
            break;
        } else if (wlength<4) {
            cout << "Must be at least 4 words." << endl;
            continue;
        } else {
            int Rkey = randomInteger(0, key.size()-1);
            Vector<string> window = key[Rkey];
            cout << "... ";
            for (int i =1;i<wlength;i++) {
                if (window[0]=="," || window[0]==";" || window[0]=="." || window[0]=="?" || window[0]==":" || window[0]=="'"
                    || window[0]=="\""     )
                {
                   cout << window[0];
                } else {
                    cout << " " << window[0] ;
                }
                int Rvalue = randomInteger(0, map.get(window).size()-1);
                string nextLetter =  map.get(window)[Rvalue];
                window.remove(0);
                window.add(nextLetter);
            }
            cout << "... " << endl;
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

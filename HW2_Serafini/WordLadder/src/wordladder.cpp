/* File: wordladder.cpp
 * CS106B assignment2 Part A: Word Ladder.
 * A word ladder is a connection from one word to another formed by changing one letter
 * at a time with the constraint that at each step the sequence of letters still forms a valid word.
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <simpio.h>
#include "filelib.h"
#include "vector.h"
#include "stack.h"
#include "queue.h"
#include "strlib.h"
#include "lexicon.h"
#include <string>
#include "console.h"

using namespace std;
Stack<string> findLadder(Lexicon &lex, string w1, string w2) {
    //This function return the shortest ladder from w1 to w2
    Queue<Stack<string> > ladders;
    Stack<string> subladder;
    Set<string> usedWords;
    usedWords.add(w1);
    subladder.push(w1);
    ladders.add(subladder);
    while (!ladders.isEmpty()) {
        Stack<string> subladder = ladders.dequeue();
        string lasWord = subladder.peek();
        //cout << "head = " << lasWord << " " ;
        //return the neighbor word one by one
        for (int i=0;i<lasWord.length();i++) {
            string dummyWord = lasWord;
            for(char ch = 'a'; ch <= 'z'; ch++) {
                if (ch != lasWord[i] ) {
                    dummyWord[i]=ch;
                    if (equalsIgnoreCase(dummyWord,w2)) {
                        return subladder;
                    }
                    if (lex.contains(dummyWord) & !usedWords.contains(dummyWord) ) {
                        //wcout << "neighbors = " << dummyWord << endl;
                        usedWords.add(dummyWord);
                        Stack<string> newLadder = subladder;
                        newLadder.push(dummyWord);
                        ladders.enqueue(newLadder);
                    }
                }                
            } 
        }
    }
    cout << "Ladder found!" << endl;
    return subladder;
}

int main() {
    cout << "Welcome to CS 106B Word Ladder. Please give me two English words, "
            "and I will change the first into the second by changing one letter at a time." << endl;
    //Loading the dictionary data from the file you specified.
    Lexicon lex;
    while (true) {
       cout << "Dictionary file name? " << endl;
       string fileName = getLine();
       //string fileName = "smalldict1.txt";
       if (fileExists(fileName)) {
           ifstream in;
           in.open(fileName);
           while (true) {
               string word;
               in >> word;
               if (in.fail()) break;
               lex.add(word);
           }
           //Lexicon lex(fileName); //this way fail to use contains() method
           //cout <<" words loaded!" << endl;
           break;
       }
       cout << "Unable to open that file.  Try again." << endl;
    }

    //User input two word for laddering from w1 to w2.
    string w1;
    string w2;
    while (true) {
        cout << " " << endl;
        cout << "Word #1 (or Enter to quit): " << endl;
        w1 = getLine();
        if (w1.length()==0) break;
        cout << "Word #2 (or Enter to quit): " << endl;
        w2 = getLine();
        if (w2.length()==0) break;
        w1 = toLowerCase(w1);
        w2 = toLowerCase(w2);
        if (w1.compare(w2)==0) {
            cout << "The two words must be different." << endl;
        } else if (w1.length() != w2.length()) {
            cout << "The two words must be the same length." << endl;
        } else if ( !lex.contains(w1) ||  !lex.contains(w2) ) {
            cout << "The two words must be found in the dictionary." << endl;
        } else {
            //qualified input， begin to look for ladder
            Stack<string> ladder = findLadder(lex,w1,w2);
            cout << "A ladder from " << w2 << " back to " << w1 << ":" << endl;
            cout << w2 << " ";
            while (!ladder.isEmpty()) {
                cout << ladder.pop() << " ";
            };
            cout << " " << endl;
        }
    }
    cout <<  "Have a nice day." << endl;
    return 0;
}

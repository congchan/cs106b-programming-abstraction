/* Assignment 4: Boggle
 * Write a program that plays a fun, graphical rendition of this little charmer,
 * adapted for the human and computer to play pitted against one another.
 *
 * The Boggle game board is a square grid onto which you randomly distribute a set of letter cubes.
 * The goal is to find words on the board by tracing a path through adjoining letters.
 *
 * @Author: Cong Chen
 * @Version: 2017/06
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "set.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    Lexicon dictionary;
    Set<string> humanWordSet;
    Set<string> computerWordSet;
    int boardSize;
private:
    // TODO: add any other member functions/variables necessary
    Grid<char> board;
    Grid<bool> boardMark;
    int humanScore;
    int computerScore;

    bool humanNeighborSearch(int row, int col, string word);
    bool computerNeighborSearch(int row, int col, string word);


};

#endif // _boggle_h

/* Class: Boggle.cpp
 * A Boggle class is used to abstract a boggle game.
 * A Boggle object represents the current board and state for a single Boggle game,
 * and it should have member functions to perform most major game functions like finding words on the board and keeping score.

 * @Author: Cong Chen
 * @Version: 2017/06
 */

#include "Boggle.h"
#include "bogglegui.h"
#include "shuffle.h"
#include "lexicon.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // initialize the object
    Boggle::boardSize = 4;
    Boggle::dictionary = dictionary;
    Boggle::humanWordSet;
    Boggle::computerWordSet;
    Boggle::humanScore=0;
    Boggle::computerScore=0;
    if (boardText == "") { // user did not specify the board
        // shuffle the board cube location
        Vector<string> boardCubes;
        for (string element:CUBES) {
            boardCubes.add(element);
        }
        shuffle(boardCubes);
        // shuffle the dice face of each cube
        for (int i=0;i<boardCubes.size();i++) {
            boardText += shuffle(boardCubes[i])[0];
        }
    }

    BoggleGUI::labelAllCubes(boardText);
    // set the board
    Boggle::board = Grid<char>(boardSize,boardSize);
    for (int i=0;i<boardSize;i++) {
        for (int j=0;j<boardSize;j++) {
            board.set(i,j,boardText[i*4+j]);
        }
    }


}

char Boggle::getLetter(int row, int col) {
    /*return the character that is stored in your Boggle board at the given 0-based row and column.
     * If the row and/or column are out of bounds, you should throw an int exception.*/
    if (row<boardSize & col<boardSize) {
        return board[row][col];
    } else throw -1;
}


bool Boggle::checkWord(string word) {
    // return true if the word is verified
    if (dictionary.contains(word) & word.size()>=4 ) {
        return true;
    }
    return false;
}

bool Boggle::humanWordSearch(string word) {
    /*employ recursive backtracking that "fails fast":
     *as soon as you realize you can't form the word starting at a position, you backtrack.*/
    // initialize the status where no cube has been searched yet
    boardMark = Grid<bool>(boardSize,boardSize,false);
        for (int i=0;i<boardSize;i++) {
            for(int j=0;j<boardSize;j++){
                boardMark.set(i,j,true);
                BoggleGUI::labelCube(i,j,getLetter(i,j),boardMark[i][j]);
                if (board[i][j]==word[0]) {
                    if (humanNeighborSearch(i,j,word)) {
                        humanScore += word.length()-3;
                        humanWordSet.add(word);
                        return true;
                    }
                }
                boardMark.set(i,j,false);
                BoggleGUI::labelCube(i,j,getLetter(i,j),boardMark[i][j]);
            }
        }

    return false;   // remove this
}

int Boggle::getScoreHuman() {
    // score = word length - 3
    return humanScore;
}

Set<string> Boggle::computerWordSearch() {
    /* traverses the board using an exhaustive search to find all remaining words.
     * Be sure to use the lexicon prefix search to abandon searches down dead-end paths. */
    // initialize the status where no cube has been searched yet
    boardMark = Grid<bool>(boardSize,boardSize,false);
    Set<string> computerWordSet;

    for (int i=0;i<boardSize;i++) {
        for(int j=0;j<boardSize;j++){
            computerNeighborSearch(i,j,charToString(board[i][j]));
        }
    }

    return computerWordSet;

}

int Boggle::getScoreComputer() {
    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}

/*Given a location(row,col) with a char as prefix, find its neighbors location that hold char as suffix,
 * check the new prefix = prefix+suffix is a valid prefix or not  */
bool Boggle::computerNeighborSearch(int row,int col, string prefix) {
    boardMark.set(row,col,true);
    for (int i=row-1;i<=row+1;i++){
        for (int j =col-1;j<=col+1;j++){
            if (i<boardSize & i>=0 & j<boardSize & j>=0) {
                if ( !boardMark[i][j]) {
                    string newPrefix = prefix + charToString(board[i][j]);
                    if (dictionary.containsPrefix(newPrefix)) {
                        if (checkWord(newPrefix) & !humanWordSet.contains(newPrefix) & !computerWordSet.contains(newPrefix)) {
                            computerWordSet.add(newPrefix);
                            BoggleGUI::recordWord(newPrefix,BoggleGUI::COMPUTER);
                            computerScore += newPrefix.length()-3;
                        }
                        computerNeighborSearch(i,j,newPrefix);
                    }
                }
            }
        }
    }
    boardMark.set(row,col,false);

    return false;
}




/*Given a location(row,col) with the char == word[0], find its neighbors location that hold char == word[1] */
bool Boggle::humanNeighborSearch(int row,int col,string word) {

    boardMark.set(row,col,true);
    BoggleGUI::labelCube(row,col,getLetter(row,col),boardMark[row][col]);
    if (word=="") return true;
    if (word.length()==1) return true;
    if (getLetter(row,col)!=word[0]) return false;

    for (int i=row-1;i<=row+1;i++){
        for (int j =col-1;j<=col+1;j++){
            if (i<boardSize & i>=0 & j<boardSize & j>=0) {
                if (board[i][j]==word[1] & !boardMark[i][j]) {
                    if (humanNeighborSearch(i,j,word.substr(1))) return true;
                }
            }
        }
    }
    boardMark.set(row,col,false);
    BoggleGUI::labelCube(row,col,getLetter(row,col),boardMark[row][col]);
    return false;

}

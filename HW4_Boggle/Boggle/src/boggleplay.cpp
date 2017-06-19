// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "simpio.h"
#include "bogglegui.h"
#include "Boggle.h"
#include "string.h"


void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    string boardText;
    if(!getYesOrNo("Do you want to generate a random board? ")) {
        boardText = getLine("Type the 16 letters to appear on the board: ");
    }

    BoggleGUI::initialize(4,4);
    Boggle game(dictionary,boardText);
    BoggleGUI::setStatusMessage("Your turn");

    //Human's turn
    while(true) {
        BoggleGUI::setAnimationDelay(50);
        string humanInput = toUpperCase(getLine("Type a word (or Enter to stop):"));
        if (humanInput=="") break;
        if (!game.checkWord(humanInput)) {
            cout<< "You must enter an unfound 4+ letter word from the dictionary." << endl;
        } else if (!game.humanWordSet.contains(humanInput)) {
            BoggleGUI::clearHighlighting();
            if(game.humanWordSearch(humanInput)){
                BoggleGUI::recordWord(humanInput,BoggleGUI::HUMAN);
                BoggleGUI::setStatusMessage("You found a word! \""+ humanInput +"\" ");
                BoggleGUI::setScore(game.getScoreHuman(),BoggleGUI::HUMAN);
            }

        }
    }

    //Computer's turn
    game.computerWordSearch();
    if (game.getScoreComputer()>game.getScoreHuman()) {
        BoggleGUI::setStatusMessage("Human, you are defeated!");
    } else if (game.getScoreComputer()==game.getScoreHuman()) {
        BoggleGUI::setStatusMessage("Impressive, Human, you could catch up with my mind!");
    } else {
        BoggleGUI::setStatusMessage("That is impossible, I was defeayou defeated!");
    }

    BoggleGUI::setScore(game.getScoreComputer(),BoggleGUI::COMPUTER);



}

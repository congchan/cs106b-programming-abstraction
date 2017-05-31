/* File name: life.cpp
 * For CS106B Assignment 1: The Game of Life.
 * The Game of Life is a simulation of the life cycle of bacteria using a two-dimensional grid of cells.
 */
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;
void animation(Grid<char> grid) {
    LifeGUI lifegui;
    lifegui.resize(grid.numRows(), grid.numCols());
    for (int i =0 ; i< grid.numRows();i++) {
        for (int j =0; j< grid.numCols(); j++) {
            bool alive = false;
            if (grid[i][j]=='X') alive = true;
            lifegui.drawCell(i,j,alive);
        }
    }
    pause(50);


}

int wrap(int co, int dimension, bool ifWrap) {
    /* This function return the wrapped coordinate.*/
    if (ifWrap) {
        return (co+dimension)%dimension;
    } else {
        return co;
    }

}

Grid<char> evolution(Grid<char> grid, bool ifWrap) {
    /* This function generates the next generation of the input bacteria colony,
     * and return the next generation bacteria grid;
     */
    Grid<char> nextG(grid.numRows(),grid.numCols());
    int neighbors = 0;
    for (int i =0 ; i< grid.numRows();i++) {
        for (int j =0; j< grid.numCols(); j++) {
            neighbors = 0;
            char LT = grid[wrap(i-1,grid.numRows(),ifWrap)][wrap(j-1,grid.numCols(),ifWrap)];
            char L = grid[wrap(i,grid.numRows(),ifWrap)][wrap(j-1,grid.numCols(),ifWrap)];
            char LB = grid[wrap(i+1,grid.numRows(),ifWrap)][wrap(j-1,grid.numCols(),ifWrap)];
            char B = grid[wrap(i+1,grid.numRows(),ifWrap)][wrap(j,grid.numCols(),ifWrap)];
            char RB = grid[wrap(i+1,grid.numRows(),ifWrap)][wrap(j+1,grid.numCols(),ifWrap)];
            char R = grid[wrap(i,grid.numRows(),ifWrap)][wrap(j+1,grid.numCols(),ifWrap)];
            char RT = grid[wrap(i-1,grid.numRows(),ifWrap)][wrap(j+1,grid.numCols(),ifWrap)];
            char T = grid[wrap(i-1,grid.numRows(),ifWrap)][wrap(j,grid.numCols(),ifWrap)];
            if (LT =='X') neighbors +=1 ;
            if (L =='X') neighbors +=1 ;
            if (LB =='X') neighbors +=1 ;
            if (B =='X') neighbors +=1 ;
            if (RB =='X') neighbors +=1 ;
            if (R =='X') neighbors +=1 ;
            if (RT =='X') neighbors +=1 ;
            if (T =='X') neighbors +=1 ;
            switch (neighbors) {
            case 2:
                nextG[i][j] =grid[i][j];
                break;
            case 3:
                nextG[i][j] = 'X';
                break;
            default:
                nextG[i][j] = '-';
            }
        }
    }
    return nextG;
}

void gridDisplay(Grid<char> &grid) {
    /*This function display loaded grid.
     */
    for (int i =0 ; i< grid.numRows();i++) {
        for (int j =0; j< grid.numCols(); j++) {
            if (j == grid.numCols()-1 ) {
                cout << grid[i][j] << endl;
            } else {
                cout << grid[i][j];
            }
        }
    }
}

Grid<char> loadGrid(string file) {
    /*This function load the file gird data and return the grid.
     */
    ifstream in;
    in.open(file);
    string line;
    string row;
    string col;
    getline(in, row);
    getline(in, col);
    Grid<char> grid(stringToInteger(row),stringToInteger(col));
    for (int r = 0; r<grid.numRows();r++) {
        getline(in, line);
        for (int c =0; c< grid.numCols();c++) {
            grid[r][c]= line[c];
        }
    }
    cout << row << "*" << col << " Grid loaded" << endl;
    /*cout << grid.toString2D() << endl; */
    in.close();
    return grid;
}

int main() {
    cout << "Welcome to CS106B Game of life,"
            "a simulation of the lifecycle of a bacteria colony."
            "Cells (X) live and die by the following rules:"
            "- A cell with 1 or fewer neighbors dies."
            "- Locations with 2 neighbors remian stable."
            "- Locations with 3 neighbors will create life."
            "- A cell with 4 or more neighbors dies." << endl;


    cout << "Grid imput file name? " << endl;
    string fileName;
    while (true) {
       fileName = getLine();
       if (fileExists(fileName)) break;
       cout << "Unable to open that file.  Try again." << endl;
    }
    Grid<char> grid = loadGrid(fileName);

    cout << "Should the sumulation wrap around the grid (y/n)?" << endl;
    bool ifWrap = true;
    gridDisplay(grid);

    while (true) {
        /*User input to choose a)nimate, t)ick, q)uit? */
        cout << "a)nimate, t)ick, q)uit? " << endl;
        string userin = getLine();

        if (userin == "t") {
            Grid<char> nextGen = evolution(grid,ifWrap);
            gridDisplay(nextGen);
            grid = nextGen;
        } else if (userin == "q") {
            break;
        } else if (userin == "a") {
            cout << "How many frames?" << endl;
            int frames = getInteger();
            for (int i =0;i<frames;i++) {
                Grid<char> nextGen = evolution(grid,ifWrap);
                animation(nextGen);
                grid = nextGen;
            }
        }
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

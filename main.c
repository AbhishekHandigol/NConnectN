#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include "win.h"
#include "board.h"
#include "move.h"
#include "CursorTrakedWindow.h"



int main(int argc, char** argv) {
    initscr();
    noecho();
    cbreak();
    FILE* fp = NULL;

    int num_rows = 0;
    int num_cols = 0;
    int num_pieces = 0;
    num_rows = atoi(argv[1]);
    num_cols = atoi(argv[2]);
    num_pieces = atoi(argv[3]);

    fp = fopen(argv[4], "w");

    CursorTrackedWindow top = newCursorTrackedWindow(1, num_cols, 0, 0);//window that tracks the cursor
    CursorTrackedWindow middle = newCursorTrackedWindow(num_rows,num_cols,1,0);//tracks the screen
    CursorTrackedWindow bottom = newCursorTrackedWindow(num_rows,15,num_rows+2,0);
    fillWindow(&middle, '*');
    fillWindow(&top, ' ');
    fillWindow(&bottom, ' ');
    keypad(top.cursesWin, true);
    wrefresh(top.cursesWin);



    //make a board
    Board board = makeBoard(num_rows,num_cols,num_pieces,'*');
    TurnType playerTurn = Player1;
    // pick a starting player
    placeBoardMove(board, &middle);
    while(!isGameOver(board)){
        //show them the state of the game
        //printBoard(board);
        //get a move from the user
        getValidMove(fp, &board, playerTurn, &top, &middle, &bottom);
        placeBoardMove(board, &middle);
        //place their move on the board
        //        //placeMove(move, &board, &top);
        //change turn
        //playerTurn = (playerTurn + 1) % 2;
        playerTurn = playerTurn == Player1 ? Player2 : Player1;
    }
    declareWinner(fp, board, playerTurn, &top, &middle, &bottom);
    delwin(top.cursesWin);
    delwin(middle.cursesWin);
    delwin(bottom.cursesWin);
    endwin();
    //print the winning board
    //printBoard(board);
    //declare who wins or a tie
    //clean up
    cleanUpBoard(&board);
    fclose(fp);
    return 0;
}


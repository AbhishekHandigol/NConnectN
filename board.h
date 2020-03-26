
#ifndef NCURSESCONNECTN_BOARD_H
#define NCURSESCONNECTN_BOARD_H
#include "move.h"



//typedef int phoneNumber;

typedef struct Board_Struct{
    char** theBoard;
    int numRows;
    int numCols;
    int num_pieces;
    char blankChar;
}Board;



Board makeBoard(int numRows, int numCols, int num_pieces, char blankChar);
void placeBoardMove(Board board, CursorTrackedWindow* screen);
void cleanUpBoard(Board* board);



#endif //NCURSESCONNECTN_BOARD_H


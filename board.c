
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "CursorTrakedWindow.h"

Board makeBoard(int numRows, int numCols, int num_pieces, char blankChar) {
  Board board;

  board.theBoard = (char**)malloc(numRows * sizeof(char*));
  for (int i = 0; i < numRows; ++i) {
    board.theBoard[i] = (char*)malloc(numCols * sizeof(char));
    for (int j = 0; j < numCols; ++j) {
      board.theBoard[i][j] = blankChar;
    }
  }
  board.num_pieces = num_pieces;
  board.numRows = numRows;
  board.numCols = numCols;
  board.blankChar = blankChar;
  return board;
}

void placeBoardMove(Board board, CursorTrackedWindow* screen) {
  //print column header

  for (int row = 0; row < board.numRows; ++row) {
    for (int col = 0; col < board.numCols; ++col) {
      mvwaddch(screen->cursesWin, row, col, board.theBoard[row][col]);
    }
  }
  wrefresh(screen->cursesWin);
}

void cleanUpBoard(Board* board) {

  for (int row = 0; row < board->numRows; ++row) {
    free(board->theBoard[row]);
  }
  free(board->theBoard);
  board->theBoard = NULL;
  board->numRows = 0;
  board->numCols = 0;
}



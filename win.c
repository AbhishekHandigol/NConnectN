#include <stdio.h>
#include "win.h"


bool isGameOver(Board board) {
    return win(board) || tie(board);
}

bool win(Board board) {
    return horzWin(board) || vertWin(board) || diagWin(board);
}

bool horzWin(Board board) {
    int count = 1;
    for(int i = 0; i < board.numRows; i++) {
        for(int j = 0; j < board.numCols-1; j++) {
            if ((board.theBoard[i][j] != board.blankChar) && (board.theBoard[i][j] == board.theBoard[i][j+1])) {
                count++;
                //continue;
            }

            else {
                count = 1;
            }
            if (count >= board.num_pieces) {
                return true;
            }

        }
        count = 1;
    }
    return false;
}


bool vertWin(Board board) {
    int count = 1;
    for(int i = 0; i < board.numCols; i++) {
        for(int j = 0; j < board.numRows-1; j++) {
            if ((board.theBoard[j][i] != board.blankChar) && (board.theBoard[j][i] == board.theBoard[j+1][i])) {
                count++;
                //continue;
            }
            else {
                count = 1;
            }
            if (count >= board.num_pieces) {
                return true;
            }
        }
    }
    return false;
}

bool diagWin(Board board) {
    return leftDiagWin(board) || rightDiagWin(board);
}

/**
 * Check for a left diagonal win. This looks like
 * X
 *   X
 *     X
 * @param board
 * @return
 */
bool leftDiagWin(Board board) {
    int count;
    for(int row = 0; row < board.numRows-1; row++) {
        for(int col = 0; col < board.numCols-1; col++) {
            if (board.theBoard[row][col] != board.blankChar) {
                count = 1;
                for(int y = row, z = col; y < board.numRows-1 && z < board.numCols-1; y++, z++) {
                    if ((board.theBoard[y][z] == board.theBoard[y+1][z+1]) && (board.theBoard[y][z] != board.blankChar)){ //accessing what's not there
                        count++;
                        //continue;
                    }
                    if (count >= board.num_pieces) {
                        return true;
                    }

                }
            }
            count = 0;
        }
    }
    return false;
}

/**
 * Check for a right diagonal win
 * One that looks like
 *      X
 *    X
 *  X
 * @param board
 * @return
 */
bool rightDiagWin(Board board) {
    int count;
    for(int row = 0; row < board.numRows-1; row++) {
        for(int col = board.numCols-1; col > 0; col--) {
            if (board.theBoard[row][col] != board.blankChar)  {
                count = 1;
                for(int y = row, z = col; y+1 < board.numRows && z > 0; y++, z--) { //check
                    if ((board.theBoard[y][z] == board.theBoard[y+1][z-1]) && (board.theBoard[y][z] != board.blankChar)){
                        count++;
                        //continue;
                    }
                    if (count >= board.num_pieces) {
                        return true;
                    }
                }

            }
            count = 0;
        }
    }
    return false;
}

bool tie(Board board) {

    if(win(board)){
        return false;
    }

    for (int row = 0; row < board.numRows; ++row) {
        for (int col = 0; col < board.numCols; ++col) {
            if(board.theBoard[row][col] == board.blankChar){
                return false;
            }
        }
    }
    return true;
}

void declareWinner(FILE* fp, Board board, TurnType playerTurn, CursorTrackedWindow* window, CursorTrackedWindow* screen, CursorTrackedWindow* bottom) {
    if(win(board)) {
        //logscreen(fp, board, win, screen, bottom);
        //if someone one it would actually be the loser's turn
        //so account for this here
        int winner = playerTurn == Player1 ? Player2 : Player1;
        //winner++;
        if (winner == Player1) {
            char arr[] = {'P', 'l', 'a', 'y', 'e', 'r', ' ', '1', ' ', 'w', 'o', 'n', '!', '\0'};
            waddstr(bottom->cursesWin, arr);
        }//do we need to allocate space for this or free it afterwards?
        else if (winner == Player2) {
            char arr[] = {'P', 'l', 'a', 'y', 'e', 'r', ' ', '2', ' ', 'w', 'o', 'n', '!', '\0'};
            waddstr(bottom->cursesWin, arr);
        }


        wrefresh(bottom->cursesWin);
    } else if (board.num_pieces == 1) {
        char arr[] = {'P', 'l', 'a', 'y', 'e', 'r', ' ', '1', ' ', 'w', 'o', 'n', '!', '\0'};
        waddstr(bottom->cursesWin, arr);
        wrefresh(bottom->cursesWin);
    } else if (tie(board)) {
        char arr[] = {'T', 'i', 'e', ' ', 'G', 'a', 'm', 'e', '\0'};
        waddstr(bottom->cursesWin, arr);
    }
        logscreen(fp, board, window, screen);
        logannouncement(fp, board, bottom);
        wrefresh(bottom->cursesWin);

    fprintf(fp, "%c", '\n');
}
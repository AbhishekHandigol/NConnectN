#include <stdio.h>
#include "InputValidation.h"
#include "move.h"
#include "board.h"
#include "CursorTrakedWindow.h"
#include "win.h"


//cursor tracked is for upper cursor window now
Move getValidMove(FILE* fp, struct Board_Struct* board, TurnType playerTurn, CursorTrackedWindow* win, CursorTrackedWindow* screen, CursorTrackedWindow* bottom) { //moves the cursor around w input
    Move move;

    if (playerTurn == Player1) {
        move.marker = 'X';

        mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol,move.marker);
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
        logscreen(fp, *board, win, screen);
        logannouncement(fp, *board, bottom);
        wrefresh(win->cursesWin);
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
    }
    else {
        move.marker = 'O';

        mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol,move.marker);
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
        logscreen(fp, *board, win, screen);
        logannouncement(fp, *board, bottom);
        wrefresh(win->cursesWin);
        wmove(win->cursesWin, win->cursorRow, win->cursorCol);
    }


    while (true) {
        char input = wgetch(win->cursesWin);
        if (input == 'a' || input == 'j' || input == (KEY_LEFT & A_CHARTEXT)) {
            mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol, ' ');
            win->cursorCol -= 1;
            if(win->cursorCol < 0){
                win->cursorCol = board->numCols-1;
            }
            mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol, move.marker);
            wmove(win->cursesWin, win->cursorRow, win->cursorCol);
            int r = win->cursorRow;
            int c = win->cursorCol;
            logscreen(fp, *board, win, screen);
            logannouncement(fp, *board, bottom);
            wrefresh(win->cursesWin);
            wmove(win->cursesWin, r, c);

        } else if (input == 's' || input == 'k' || input == (KEY_RIGHT & A_CHARTEXT)) {
            mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol, ' ');
            int r = win->cursorRow;
            int c = win->cursorCol;
            win->cursorCol += 1;
            if(win->cursorCol >= board->numCols){
                win->cursorCol = 0;
            }
            mvwaddch(win->cursesWin, win->cursorRow, win->cursorCol, move.marker);
            wmove(win->cursesWin, win->cursorRow, win->cursorCol);
            logscreen(fp, *board, win, screen);
            logannouncement(fp, *board, bottom);
            wrefresh(win->cursesWin);
            wmove(win->cursesWin, r, c);
        } else if ((input == ' ' || input == '\n') && board->theBoard[win->cursorRow][win->cursorCol] == board->blankChar) {

            for (int i = board->numRows-1; i >= 0; i--) {
                if ((board->theBoard[i][win->cursorCol] != 'X') && (board->theBoard[i][win->cursorCol] != 'O')) {
                    board->theBoard[i][win->cursorCol] = move.marker;
                    break;
                }
            }
            wmove(win->cursesWin, win->cursorRow, win->cursorCol);
            move.marker = "XO"[playerTurn];
            return move;
        } else {
            logscreen(fp, *board, win, screen);
            logannouncement(fp, *board, bottom);
            wrefresh(win->cursesWin);
            wmove(win->cursesWin, win->cursorRow, win->cursorCol);
        }
        wrefresh(win->cursesWin);
        wrefresh(screen->cursesWin);
        wrefresh(bottom->cursesWin);
    }

}

TurnType checkColumn(struct Board_Struct board, TurnType playerTurn, CursorTrackedWindow* win){
    int count = 0;
    for (int i = board.numRows-1; i >= 0; i--) {
        if ((board.theBoard[i][win->cursorCol] == 'X') || (board.theBoard[i][win->cursorCol] == 'O')) {
            count++;
        }
    }
    if (count >= board.numRows) {
        if (playerTurn == Player1) {
            playerTurn = Player2;
        } else if (playerTurn == Player2) {
            playerTurn = Player1;
        }
    }
    return playerTurn;
}


bool isValidMove(Move move, struct Board_Struct* board, int numArgsRead, int numArgsNeeded) {
    return isValidFormat(numArgsRead, numArgsNeeded) &&
           isInRange(move.row, 0, board->numRows - 1) &&
           isInRange(move.col, 0, board->numCols - 1) &&
           board->theBoard[move.row][move.col] == board->blankChar;
}

const char* PlayerToString(TurnType player) {
    static const char p1[] = "Player1";
    static const char p2[] = "Player2";
    if (player == Player1) {
        return p1;
    } else {
        return p2;
    }
}
void logscreen(FILE* fp, Board board, CursorTrackedWindow* win, CursorTrackedWindow* screen) {
    for(int i = 0; i < board.numCols; i++) { //cursor tracked window, fills in the cursor window and outputs to the file
        chtype winChar = mvwinch(win->cursesWin, 0, i);
        char theChar = winChar & A_CHARTEXT;
        fprintf(fp, "%c", theChar);
    }
    fprintf(fp, "%c",'\n');
    for(int i = 0; i < getNumRows(screen); i++) { //cursor tracked window, fills in the cursor window and outputs to the file
        for(int j = 0; j < board.numCols; j++) {
            chtype winChar = mvwinch(screen->cursesWin, i, j);
            char theChar = winChar & A_CHARTEXT;
            fprintf(fp, "%c", theChar);
        }
        fprintf(fp, "%c",'\n');
    }
}

void logannouncement(FILE* fp, Board board, CursorTrackedWindow* bottom) {
    if(!isGameOver(board)) {
        fprintf(fp, "%c",'\n');
    }
    for(int i = 0; i < 15; i++) { //cursor tracked window, fills in the cursor window and outputs to the file
        chtype winChar = mvwinch(bottom->cursesWin, 0, i);
        char theChar = winChar & A_CHARTEXT;
        fprintf(fp, "%c", theChar);
    }
    wmove(bottom->cursesWin, 0, 0);
    fprintf(fp, "%c",'\n');
}
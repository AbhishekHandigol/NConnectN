#ifndef NCURSESCONNECTN_CURSORTRAKEDWINDOW_H
#define NCURSESCONNECTN_CURSORTRAKEDWINDOW_H

#include <ncurses.h>
#include <curses.h>




typedef struct CursorTrackedWindow_Struct{ //cursor top screen
    WINDOW* cursesWin;
    int cursorRow, cursorCol;
    //int num_rows, num_cols;
}CursorTrackedWindow;

CursorTrackedWindow newCursorTrackedWindow(int numRows, int numCols, int rowStart, int colStart); //both
void fillWindow(CursorTrackedWindow* win, char fillChar); //middle screen

int getNumRows(CursorTrackedWindow* win);
int getNumCols(CursorTrackedWindow* win);

void moveAndAddCharacter(CursorTrackedWindow* win, int row, int col, char toAdd);
void addCharacter(CursorTrackedWindow* win, char toAdd);
void CursorTrackedWindowMove(CursorTrackedWindow* win, int row, int col);


#endif //NCURSESCONNECTN_CURSORTRAKEDWINDOW_H
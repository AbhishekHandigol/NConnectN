#ifndef NCURSESCONNECTN_MOVE_H
#define NCURSESCONNECTN_MOVE_H
#include <stdbool.h>
#include "CursorTrakedWindow.h"
//#include "board.h"


typedef enum{Player1 = 0, Player2 = 1}TurnType;


typedef struct Move_Struct{ //move struct already implemented
    int row, col;
    char marker;
}Move;



struct Board_Struct;
bool isGameOver(struct Board_Struct board);

Move getValidMove(FILE* fp, struct Board_Struct* board, TurnType playerTurn, CursorTrackedWindow* win, CursorTrackedWindow* screen, CursorTrackedWindow* bottom);
TurnType checkColumn(struct Board_Struct board, TurnType playerTurn, CursorTrackedWindow* win);
bool isValidMove(Move move,  struct Board_Struct* board, int numArgsRead, int numArgsNeeded);
bool isValidMove(Move move,  struct Board_Struct* board, int numArgsRead, int numArgsNeeded);
const char* PlayerToString(TurnType player);
void logscreen(FILE* fp, struct Board_Struct board, CursorTrackedWindow* win, CursorTrackedWindow* screen);
void logannouncement(FILE* fp, struct Board_Struct board, CursorTrackedWindow* bottom);

#endif //NCURSESCONNECTN_MOVE_H
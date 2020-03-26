//
// Created by mfbut on 7/17/2018.
//

#ifndef NCURSESCONNECTN_WIN_H
#define NCURSESCONNECTN_WIN_H

#include <stdbool.h>
#include <ncurses.h>
#include "board.h"
#include "move.h"



bool isGameOver(Board board);
bool win(Board board);
bool horzWin(Board board);
bool vertWin(Board board);
bool diagWin(Board board);
bool leftDiagWin(Board board);
bool rightDiagWin(Board board);
bool tie(Board board);
void declareWinner(FILE* fp, Board board, TurnType playerTurn, CursorTrackedWindow* window, CursorTrackedWindow* screen, CursorTrackedWindow* bottom);

#endif //NCURSESCONNECTN_WIN_H
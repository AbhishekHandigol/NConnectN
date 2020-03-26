
#ifndef NCURSESCONNECTN_INPUTVALIDATION_H
#define NCURSESCONNECTN_INPUTVALIDATION_H
#include <stdbool.h>
#include <ncurses.h>
#include "move.h"
bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isInRange(int value, int lowerBound, int uppderBound);

#endif //NCURSESCONNECTN_INPUTVALIDATION_H
#ifndef TREASUREHUNTLIB_H
#define TREASUREHUNTLIB_H

enum {
    TREASURE = 0,
    DIR_RIGHT = 1,
    DIR_UP    = 2,
    DIR_LEFT  = 4,
    DIR_DOWN  = 8
};

void NextHunt(int &N, int &K);
int Query(int x, int y);

/*
Local testing helper only.
Call this before the first NextHunt() to load hunts from a file.

Accepted format:
    H
    N K
    x1 y1
    ...
    xK yK
    N K
    ...

where H is the number of hunts.

A second accepted format omits H and simply repeats:
    N K
    x1 y1
    ...
    xK yK
until EOF.
*/
void InitFromFile(const char *fileName);

#endif

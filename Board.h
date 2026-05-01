#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include <string>

using namespace std;

// ── Board ─────────────────────────────────────────────────────────────────────

class Board {
    Piece* grid[8][8];

public:
    struct Position { 
        int r, c; 
    };

    struct MoveList {
        Position moves[32];
        int count = 0;
    };

    Board();
    ~Board();

    void init();
    void display();
    
    Piece* getPiece(int r, int c);
    string getSquareName(int r, int c);
    MoveList getValidMoves(int r, int c);
    void makeMove(int fromR, int fromC, int toR, int toC);

    bool needsPromotion(int r, int c);
    void promotePawn(int r, int c, int choice);
};

#endif // BOARD_H

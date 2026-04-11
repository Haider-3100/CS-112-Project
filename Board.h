#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include "Display.h"

// ── Board ─────────────────────────────────────────────────────────────────────

class Board {
    Piece* grid[8][8];

public:
    Board() {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                grid[r][c] = nullptr;
        init();
    }

    ~Board() {
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                delete grid[r][c];
    }

    void init() {
        // black back rank
        grid[0][0] = new Rook("Black");
        grid[0][1] = new Knight("Black");
        grid[0][2] = new Bishop("Black");
        grid[0][3] = new Queen("Black");
        grid[0][4] = new King("Black");
        grid[0][5] = new Bishop("Black");
        grid[0][6] = new Knight("Black");
        grid[0][7] = new Rook("Black");

        // black pawns
        for (int c = 0; c < 8; c++)
            grid[1][c] = new Pawn("Black");

        // white pawns
        for (int c = 0; c < 8; c++)
            grid[6][c] = new Pawn("White");

        // white back rank
        grid[7][0] = new Rook("White");
        grid[7][1] = new Knight("White");
        grid[7][2] = new Bishop("White");
        grid[7][3] = new Queen("White");
        grid[7][4] = new King("White");
        grid[7][5] = new Bishop("White");
        grid[7][6] = new Knight("White");
        grid[7][7] = new Rook("White");
    }

    void display() {
        displayBoard(grid);
    }
};

#endif // BOARD_H

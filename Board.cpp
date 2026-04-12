#include "Board.h"
#include "Display.h"

// ── Board Implementation ──────────────────────────────────────────────────────

Board::Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            grid[r][c] = nullptr;
    init();
}

Board::~Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            delete grid[r][c];
}

void Board::init() {
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

void Board::display() {
    displayBoard(grid);
}

Piece* Board::getPiece(int r, int c) {
    return grid[r][c];
}

string Board::getSquareName(int r, int c) {
    string s = "";
    s += (char)('A' + c);
    s += (char)('8' - r);
    return s;
}

Board::MoveList Board::getValidMoves(int r, int c) {
    MoveList list;
    Piece* p = grid[r][c];
    if (!p) return list;

    for (int toR = 0; toR < 8; toR++) {
        for (int toC = 0; toC < 8; toC++) {
            if ((toR != r || toC != c) && p->isValidMove(r, c, toR, toC, grid)) {
                if (list.count < 32) {
                    list.moves[list.count] = {toR, toC};
                    list.count++;
                }
            }
        }
    }
    return list;
}

void Board::makeMove(int fromR, int fromC, int toR, int toC) {
    if (grid[toR][toC] != nullptr) {
        delete grid[toR][toC];  // Catch piece memory clear
    }
    grid[toR][toC] = grid[fromR][fromC]; 
    grid[fromR][fromC] = nullptr;        
}

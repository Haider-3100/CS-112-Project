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

bool Board::needsPromotion(int r, int c) {
    Piece* p = grid[r][c];
    if (p == nullptr) return false;
    if (p->getIdentity() != "Pawn") return false;
    // White pawns promote at row 0, Black pawns promote at row 7
    if (p->getColor() == "White" && r == 0) return true;
    if (p->getColor() == "Black" && r == 7) return true;
    return false;
}

void Board::promotePawn(int r, int c, int choice) {
    string col = grid[r][c]->getColor();
    delete grid[r][c];  // Remove the old Pawn

    switch (choice) {
        case 1: grid[r][c] = new Queen(col);  break;
        case 2: grid[r][c] = new Rook(col);   break;
        case 3: grid[r][c] = new Bishop(col);  break;
        case 4: grid[r][c] = new Knight(col);  break;
        default: grid[r][c] = new Queen(col);  break;  // Default to Queen
    }
}

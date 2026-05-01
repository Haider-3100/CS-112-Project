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
            if ((toR != r || toC != c) && p->isValidMove(r, c, toR, toC, grid) && isLegalMove(r, c, toR, toC)) {
                if (list.count < 32) {
                    list.moves[list.count] = {toR, toC};
                    list.count++;
                }
            }
        }
    }

    // Add castling moves if this piece is a King
    if (p->getIdentity() == "King") {
        string col = p->getColor();
        // Kingside castle: King moves 2 right
        if (canCastle(col, true) && list.count < 32) {
            list.moves[list.count] = {r, c + 2};
            list.count++;
        }
        // Queenside castle: King moves 2 left
        if (canCastle(col, false) && list.count < 32) {
            list.moves[list.count] = {r, c - 2};
            list.count++;
        }
    }

    return list;
}

void Board::makeMove(int fromR, int fromC, int toR, int toC) {
    Piece* piece = grid[fromR][fromC];

    // Detect castling: King moving exactly 2 columns
    if (piece != nullptr && piece->getIdentity() == "King" && abs(toC - fromC) == 2) {
        if (toC > fromC) {
            // Kingside castle: move Rook from col 7 to col 5
            grid[fromR][5] = grid[fromR][7];
            grid[fromR][7] = nullptr;
            grid[fromR][5]->setHasMoved(true);
        } else {
            // Queenside castle: move Rook from col 0 to col 3
            grid[fromR][3] = grid[fromR][0];
            grid[fromR][0] = nullptr;
            grid[fromR][3]->setHasMoved(true);
        }
    }

    // Normal move: delete captured piece if any
    if (grid[toR][toC] != nullptr) {
        delete grid[toR][toC];
    }
    grid[toR][toC] = grid[fromR][fromC]; 
    grid[fromR][fromC] = nullptr;

    // Mark the moved piece as having moved
    grid[toR][toC]->setHasMoved(true);
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

// ── Check / Checkmate detection ───────────────────────────────────────────────

Board::Position Board::findKing(string color) {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (grid[r][c] != nullptr &&
                grid[r][c]->getIdentity() == "King" &&
                grid[r][c]->getColor() == color)
                return {r, c};
    return {-1, -1};
}

bool Board::isInCheck(string color) {
    Position king = findKing(color);
    string enemy = (color == "White") ? "Black" : "White";

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (grid[r][c] != nullptr &&
                grid[r][c]->getColor() == enemy &&
                grid[r][c]->isValidMove(r, c, king.r, king.c, grid))
                return true;

    return false;
}

bool Board::isLegalMove(int fromR, int fromC, int toR, int toC) {
    Piece* moving   = grid[fromR][fromC];
    Piece* captured = grid[toR][toC];
    string myColor  = moving->getColor();

    // Temporarily make the move
    grid[toR][toC]     = moving;
    grid[fromR][fromC] = nullptr;

    bool safe = !isInCheck(myColor);

    // Undo the move
    grid[fromR][fromC] = moving;
    grid[toR][toC]     = captured;

    return safe;
}

// ── Castling ──────────────────────────────────────────────────────────────────

bool Board::canCastle(string color, bool kingside) {
    int row = (color == "White") ? 7 : 0;
    int kingCol = 4;
    int rookCol = kingside ? 7 : 0;

    // Rule 1: King must exist at starting square and never have moved
    Piece* king = grid[row][kingCol];
    if (king == nullptr || king->getIdentity() != "King" || king->getHasMoved())
        return false;

    // Rule 2: Rook must exist at starting square and never have moved
    Piece* rook = grid[row][rookCol];
    if (rook == nullptr || rook->getIdentity() != "Rook" || rook->getHasMoved())
        return false;

    // Rule 3: All squares between King and Rook must be empty
    int start = (kingCol < rookCol) ? kingCol + 1 : rookCol + 1;
    int end   = (kingCol < rookCol) ? rookCol     : kingCol;
    for (int c = start; c < end; c++) {
        if (grid[row][c] != nullptr)
            return false;
    }

    // Rule 4: King must NOT currently be in check
    if (isInCheck(color))
        return false;

    // Rule 5: King must not pass through or land on an attacked square
    // Check the square the King passes through
    int passCol = kingside ? 5 : 3;
    grid[row][passCol]  = king;
    grid[row][kingCol]  = nullptr;
    bool passSafe = !isInCheck(color);
    grid[row][kingCol]  = king;
    grid[row][passCol]  = nullptr;
    if (!passSafe) return false;

    // Check the square the King lands on
    int landCol = kingside ? 6 : 2;
    grid[row][landCol]  = king;
    grid[row][kingCol]  = nullptr;
    bool landSafe = !isInCheck(color);
    grid[row][kingCol]  = king;
    grid[row][landCol]  = nullptr;
    if (!landSafe) return false;

    return true;
}

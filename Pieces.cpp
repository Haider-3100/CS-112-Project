#include "Pieces.h"
#include <cmath> // for abs()

// ── Piece ─────────────────────────────────────────────────────────────────────
Piece::Piece(string identity, string color) : identity(identity), color(color), hasMoved(false) {}
Piece::~Piece() {}

string Piece::getIdentity() { 
    return identity; 
}

string Piece::getColor() { 
    return color; 
}

bool Piece::getHasMoved() {
    return hasMoved;
}

void Piece::setHasMoved(bool moved) {
    hasMoved = moved;
}

string Piece::getDisplay() {
    string name = identity;
    if (color == "White")
        for (char& ch : name) ch = toupper(ch);
    else
        for (char& ch : name) ch = tolower(ch);
    return name;
}

// ── King ──────────────────────────────────────────────────────────────────────
King::King(string color) : Piece("King", color) {}

bool King::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    int dR = abs(to_Row - from_Row);
    int dC = abs(to_Col - from_Col);
    if (dR > 1 || dC > 1) return false;
    if (dR == 0 && dC == 0) return false;
    if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() == color)
        return false;
    return true;
}

// ── Queen ─────────────────────────────────────────────────────────────────────
Queen::Queen(string color) : Piece("Queen", color) {}

bool Queen::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    int dR = abs(to_Row - from_Row);
    int dC = abs(to_Col - from_Col);
    bool straight = (from_Row == to_Row || from_Col == to_Col);
    bool diagonal = (dR == dC);
    if (!straight && !diagonal) return false;

    int stepR = (to_Row > from_Row) - (to_Row < from_Row);
    int stepC = (to_Col > from_Col) - (to_Col < from_Col);

    int r = from_Row + stepR;
    int c = from_Col + stepC;
    while (r != to_Row || c != to_Col) {
        if (grid[r][c] != nullptr) return false;
        r += stepR;
        c += stepC;
    }

    if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() == color)
        return false;

    return true;
}

// ── Rook ──────────────────────────────────────────────────────────────────────
Rook::Rook(string color) : Piece("Rook", color) {}

bool Rook::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    if (from_Row != to_Row && from_Col != to_Col) return false;
    int dR = (to_Row > from_Row) - (to_Row < from_Row);
    int dC = (to_Col > from_Col) - (to_Col < from_Col);

    int r = from_Row + dR;
    int c = from_Col + dC;
    while (r != to_Row || c != to_Col) {
        if (grid[r][c] != nullptr) return false; 
        r += dR;
        c += dC;
    }

    if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() == color)
        return false; 

    return true;
}

// ── Bishop ────────────────────────────────────────────────────────────────────
Bishop::Bishop(string color) : Piece("Bishop", color) {}

bool Bishop::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    int dR = abs(to_Row - from_Row);
    int dC = abs(to_Col - from_Col);
    if (dR != dC || dR == 0) return false;

    int stepR = (to_Row > from_Row) ? 1 : -1;
    int stepC = (to_Col > from_Col) ? 1 : -1;

    int r = from_Row + stepR;
    int c = from_Col + stepC;
    while (r != to_Row || c != to_Col) {
        if (grid[r][c] != nullptr) return false;
        r += stepR;
        c += stepC;
    }

    if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() == color)
        return false;

    return true;
}

// ── Knight ────────────────────────────────────────────────────────────────────
Knight::Knight(string color) : Piece("Knight", color) {}

bool Knight::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    int dR = abs(to_Row - from_Row);
    int dC = abs(to_Col - from_Col);

    bool lShape = (dR == 2 && dC == 1) || (dR == 1 && dC == 2);
    if (!lShape) return false;

    if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() == color)
        return false;

    return true;
}

// ── Pawn ──────────────────────────────────────────────────────────────────────
Pawn::Pawn(string color) : Piece("Pawn", color) {}

bool Pawn::isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) {
    int direction = (color == "White") ? -1 : 1;
    int startRow  = (color == "White") ?  6 : 1;
    int dR = to_Row - from_Row;
    int dC = abs(to_Col - from_Col);

    if (dC == 0 && dR == direction && grid[to_Row][to_Col] == nullptr) {
        return true;
    }
    if (dC == 0 && dR == 2 * direction && from_Row == startRow) {
        if (grid[from_Row + direction][from_Col] == nullptr && grid[to_Row][to_Col] == nullptr)
            return true;
    }
    if (dC == 1 && dR == direction) {
        if (grid[to_Row][to_Col] != nullptr && grid[to_Row][to_Col]->getColor() != color)
            return true;
    }

    return false;
}

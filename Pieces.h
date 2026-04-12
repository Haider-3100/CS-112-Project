#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <string>

using namespace std;

// ── Piece ─────────────────────────────────────────────────────────────────────

class Piece {
protected:
    string identity;  // "King", "Queen", "Rook", "Bishop", "Knight", "Pawn"
    string color;     // "White" or "Black"

public:
    Piece(string identity, string color);
    virtual ~Piece();

    string getIdentity();
    string getColor();

    // Override in each subclass with piece-specific movement rules
    virtual bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) = 0;

    // White pieces → UPPERCASE  e.g. "KING", "PAWN"
    // Black pieces → lowercase  e.g. "king", "pawn"
    virtual string getDisplay();
};

// ── Derived pieces ────────────────────────────────────────────────────────────

class King : public Piece {
public:
    King(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

class Queen : public Piece {
public:
    Queen(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

class Rook : public Piece {
public:
    Rook(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

class Bishop : public Piece {
public:
    Bishop(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

class Knight : public Piece {
public:
    Knight(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

class Pawn : public Piece {
public:
    Pawn(string color);
    bool isValidMove(int from_Row, int from_Col, int to_Row, int to_Col, Piece* grid[8][8]) override;
};

#endif // PIECES_H

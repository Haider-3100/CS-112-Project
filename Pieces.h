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
    Piece(string identity, string color)
        : identity(identity), color(color) {}

    virtual ~Piece() {}

    string getIdentity() { return identity; }
    string getColor()    { return color; }

    // Override in each subclass with piece-specific movement rules
    virtual bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) = 0;

    // White pieces → UPPERCASE  e.g. "KING", "PAWN"
    // Black pieces → lowercase  e.g. "king", "pawn"
    virtual string getDisplay() {
        string name = identity;
        if (color == "White")
            for (char& ch : name) ch = toupper(ch);
        else
            for (char& ch : name) ch = tolower(ch);
        return name;
    }
};

// ── Derived pieces ────────────────────────────────────────────────────────────

class King : public Piece {
public:
    King(string color) : Piece("King", color) {}
    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        return false; // TODO
    }
};

class Queen : public Piece {
public:
    Queen(string color) : Piece("Queen", color) {}
    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        return false; // TODO
    }
};

class Rook : public Piece {
public:
    Rook(string color) : Piece("Rook", color) {}

    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        // Rook moves in straight lines only (same row OR same column)
        if (fromR != toR && fromC != toC) return false;

        // Determine direction of movement (-1, 0, or 1)
        int dR = (toR > fromR) - (toR < fromR);
        int dC = (toC > fromC) - (toC < fromC);

        // Check that every square between from and to is empty
        int r = fromR + dR;
        int c = fromC + dC;
        while (r != toR || c != toC) {
            if (grid[r][c] != nullptr) return false;  // path blocked
            r += dR;
            c += dC;
        }

        // Destination must be empty or contain an enemy piece
        if (grid[toR][toC] != nullptr && grid[toR][toC]->getColor() == color)
            return false;  // can't capture own piece

        return true;
    }
};

class Bishop : public Piece {
public:
    Bishop(string color) : Piece("Bishop", color) {}
    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        return false; // TODO
    }
};

class Knight : public Piece {
public:
    Knight(string color) : Piece("Knight", color) {}
    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        return false; // TODO
    }
};

class Pawn : public Piece {
public:
    Pawn(string color) : Piece("Pawn", color) {}
    bool isValidMove(int fromR, int fromC, int toR, int toC, Piece* grid[8][8]) override {
        return false; // TODO
    }
};

#endif // PIECES_H

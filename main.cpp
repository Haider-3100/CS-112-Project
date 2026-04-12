#include "Board.h"
#include <iostream>
using namespace std;

// We use a primitive strict array struct instead of std::vector 
struct PieceList {
    Board::Position pieces[16]; // A player can have a maximum of 16 pieces in standard chess
    int count = 0;
};

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    Board board;
    string currentTurn = "White";

    while (true) {
        board.display();
        cout << "\n=== " << currentTurn << "'s Turn ===\n";

        // 1. Gather ALL pieces for the current player that actually have valid moves
        PieceList movablePieces;
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                Piece* p = board.getPiece(r, c);
                // Check if the square isn't empty and the piece belongs to the active player
                if (p != nullptr && p->getColor() == currentTurn) {
                    Board::MoveList possibleMoves = board.getValidMoves(r, c);
                    if (possibleMoves.count > 0) {
                        // This piece can move, so add its coordinates to our raw array list
                        if (movablePieces.count < 16) {
                            movablePieces.pieces[movablePieces.count] = {r, c};
                            movablePieces.count++;
                        }
                    }
                }
            }
        }

        // If count is 0, no pieces can move
        if (movablePieces.count == 0) {
            cout << "\n" << currentTurn << " has no valid moves! Game Over.\n";
            break;
        }

        // 2. Ask the user WHICH piece they want to move 
        cout << "Which piece would you like to move?\n";
        for (int i = 0; i < movablePieces.count; i++) {
            Board::Position sq = movablePieces.pieces[i];
            Piece* p = board.getPiece(sq.r, sq.c);
            // Display example: "Press 1 for Pawn at A2"
            cout << "Press " << i + 1 << " for " << p->getIdentity() << " at " << board.getSquareName(sq.r, sq.c) << "\n";
        }

        int pieceChoice;
        cout << "Your choice: ";
        if (!(cin >> pieceChoice) || pieceChoice < 1 || pieceChoice > movablePieces.count) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        // Arrays start at 0, so subtract 1
        Board::Position selectedSq = movablePieces.pieces[pieceChoice - 1]; 
        Piece* selectedPiece = board.getPiece(selectedSq.r, selectedSq.c);

        // 3. Show exactly where the chosen piece CAN move
        Board::MoveList possibleMoves = board.getValidMoves(selectedSq.r, selectedSq.c);
        
        cout << "\nWhere do you want to move the " << selectedPiece->getIdentity() << " at " << board.getSquareName(selectedSq.r, selectedSq.c) << "?\n";
        for (int i = 0; i < possibleMoves.count; i++) {
            Board::Position target = possibleMoves.moves[i];
            cout << "Press " << i + 1 << " for " << board.getSquareName(target.r, target.c) << "\n";
        }
        cout << "Press 0 to go back and pick a different piece.\n";
        
        int moveChoice;
        cout << "Your choice: ";
        if (!(cin >> moveChoice) || moveChoice < 0 || moveChoice > possibleMoves.count) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Returning to piece selection.\n";
            continue;
        }

        if (moveChoice == 0) continue; // They entered 0, restart loop to pick a different piece

        Board::Position destination = possibleMoves.moves[moveChoice - 1];

        // 4. Finally, process the physical move on the board
        board.makeMove(selectedSq.r, selectedSq.c, destination.r, destination.c);

        // 5. Alternate the turns securely
        currentTurn = (currentTurn == "White") ? "Black" : "White";
    }

    system("pause");
    return 0;
}
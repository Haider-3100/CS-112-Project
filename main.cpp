#include "Board.h"
#include <iostream>
#include <fstream>
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

    // Clear old move history and start a new log
    ofstream initLog("move_history.txt");
    if (initLog.is_open()) {
        initLog << "=== New Chess Game Started ===\n";
        initLog.close();
    }

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

        // If count is 0, no pieces can move — check if it's checkmate or stalemate
        if (movablePieces.count == 0) {
            if (board.isInCheck(currentTurn)) {
                string winner = (currentTurn == "White") ? "Black" : "White";
                cout << "\nCHECKMATE! " << winner << " wins!\n";
            } else {
                cout << "\nSTALEMATE! The game is a draw.\n";
            }
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

        // Write the move to our move history log file
        ofstream logFile("move_history.txt", ios::app);
        if (logFile.is_open()) {
            logFile << currentTurn << " " << selectedPiece->getIdentity() 
                    << " moved from " << board.getSquareName(selectedSq.r, selectedSq.c) 
                    << " to " << board.getSquareName(destination.r, destination.c) << "\n";
            logFile.close();
        }

        // Announce check if the opponent's King is now under attack
        string opponent = (currentTurn == "White") ? "Black" : "White";
        if (board.isInCheck(opponent))
            cout << "\nCHECK! " << opponent << "'s King is under attack!\n";

        // Check for Pawn Promotion
        if (board.needsPromotion(destination.r, destination.c)) {
            board.display();
            cout << "\nPawn promotion! Choose a piece:\n";
            cout << "1. Queen\n2. Rook\n3. Bishop\n4. Knight\n";
            int promoChoice;
            while (true) {
                cout << "Your choice: ";
                if (cin >> promoChoice && promoChoice >= 1 && promoChoice <= 4) {
                    break;
                }
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            }
            board.promotePawn(destination.r, destination.c, promoChoice);
        }

        // 5. Alternate the turns securely
        currentTurn = (currentTurn == "White") ? "Black" : "White";
    }

    system("pause");
    return 0;
}
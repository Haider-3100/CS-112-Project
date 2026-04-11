#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include "Pieces.h"
using namespace std;

// ── Display helpers ───────────────────────────────────────────────────────────

// Each cell is 8 chars wide, separated by ||
// Border segments: ++--------  (repeated 8 times) then ++

void printDivider() {
    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "++--------";
    cout << "++\n";
}

void displayBoard(Piece* grid[8][8]) {
    const int COL_W = 8;

    // Each column header is exactly 8 chars wide to align with cells
    string cols[] = {"   A    ","   B    ","   C    ","   D    ",
                     "   E    ","   F    ","   G    ","   H    "};

    cout << "\n";
    cout << "                 BLACK\n\n";

    // Column headers — same structure as rows: 3 spaces + ||col||col...||
    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "||" << cols[c];
    cout << "||\n";

    printDivider();

    for (int r = 0; r < 8; r++) {
        // Row number (3 chars: " R ") then cells separated by ||
        cout << " " << (8 - r) << " ";
        for (int c = 0; c < 8; c++) {
            cout << "||";
            if (grid[r][c]) {
                string label = grid[r][c]->getDisplay();
                int pad   = (COL_W - (int)label.size()) / 2;
                int extra = (COL_W - (int)label.size()) % 2;
                cout << string(pad, ' ') << label << string(pad + extra, ' ');
            } else {
                cout << "  ....  ";
            }
        }
        cout << "|| " << (8 - r) << "\n";
        printDivider();
    }

    // Column footers — same as header
    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "||" << cols[c];
    cout << "||\n";

    cout << "\n                 WHITE\n\n";

    // Legend
    cout << "  UPPERCASE = White pieces\n";
    cout << "  lowercase = Black pieces\n";
    cout << "  ....      = Empty square\n\n";
}

#endif // DISPLAY_H

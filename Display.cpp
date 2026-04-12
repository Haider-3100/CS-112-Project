#include "Display.h"
#include <iostream>
#include <string>

using namespace std;

void printDivider() {
    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "++--------";
    cout << "++\n";
}

void displayBoard(Piece* grid[8][8]) {
    const int COL_W = 8;
    string cols[] = {"   A    ","   B    ","   C    ","   D    ",
                     "   E    ","   F    ","   G    ","   H    "};

    cout << "\n                 BLACK\n\n";

    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "||" << cols[c];
    cout << "||\n";

    printDivider();

    for (int r = 0; r < 8; r++) {
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

    cout << "   ";
    for (int c = 0; c < 8; c++)
        cout << "||" << cols[c];
    cout << "||\n";

    cout << "\n                 WHITE\n\n";

    cout << "  UPPERCASE = White pieces\n";
    cout << "  lowercase = Black pieces\n";
    cout << "  ....      = Empty square\n\n";
}

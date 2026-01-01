#include <iostream>
#include <limits> // Required for clearing input buffer

using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
    cout << "\033[2J\033[1;1H"; 
    cout << "  Tic-Tac-Toe  " << endl << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
    cout << "     |     |     " << endl << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (slot < 1 || slot > 9) return false; // Check range
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

int checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;
    return 0;
}

int main() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> current_marker;
    current_player = 1;

    drawBoard();

    for (int i = 0; i < 9; i++) {
        int slot;
        cout << "Player " << current_player << " (" << current_marker << "), enter slot (1-9): ";
        
        // --- INPUT VALIDATION START ---
        if (!(cin >> slot)) { 
            cout << "Invalid input! Please enter a NUMBER between 1 and 9." << endl;
            cin.clear(); // Reset the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad characters
            i--; 
            continue;
        }
        // --- INPUT VALIDATION END ---

        if (!placeMarker(slot)) {
            cout << "Slot occupied or out of range! Try again." << endl;
            i--;
            continue;
        }

        drawBoard();
        
        if (checkWinner() != 0) {
            cout << "CONGRATULATIONS! Player " << current_player << " wins!" << endl;
            return 0;
        }

        current_player = (current_player == 1) ? 2 : 1;
        current_marker = (current_marker == 'X') ? 'O' : 'X';
    }

    cout << "It's a tie game!" << endl;
    return 0;
}
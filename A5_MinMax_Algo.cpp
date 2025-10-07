#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'O';
const char AI = 'X';
const char EMPTY = '_';

typedef vector<vector<char>> Board;

struct Move {
    int row, col;
};

// Display the board
void printBoard(const Board& board) {
    for (const auto& row : board) {
        for (char cell : row)
            cout << cell << " ";
        cout << endl;
    }
}

// Check for winner
char checkWinner(const Board& board) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return EMPTY;
}

// Check if moves are left
bool isMovesLeft(const Board& board) {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

// Minimax algorithm
int minimax(Board& board, bool isMaximizing) {
    char winner = checkWinner(board);
    if (winner == AI) return +10;
    if (winner == HUMAN) return -10;
    if (!isMovesLeft(board)) return 0;

    int bestScore = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == EMPTY) {
                board[i][j] = isMaximizing ? AI : HUMAN;
                int score = minimax(board, !isMaximizing);
                board[i][j] = EMPTY;
                bestScore = isMaximizing ? max(bestScore, score) : min(bestScore, score);
            }

    return bestScore;
}

// Find best move for AI
Move findBestMove(Board& board) {
    int bestVal = numeric_limits<int>::min();
    Move bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, false);
                board[i][j] = EMPTY;
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }

    return bestMove;
}

// Main game loop
int main() {
    Board board = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    cout << "Welcome to Tic-Tac-Toe (You = O, AI = X)\n";
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter your move (row and column: 0-based index): ";
        cin >> row >> col;

        if (board[row][col] != EMPTY) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = HUMAN;
        printBoard(board);

        if (checkWinner(board) == HUMAN) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        Move aiMove = findBestMove(board);
        board[aiMove.row][aiMove.col] = AI;
        cout << "AI played:\n";
        printBoard(board);

        if (checkWinner(board) == AI) {
            cout << "AI wins!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}

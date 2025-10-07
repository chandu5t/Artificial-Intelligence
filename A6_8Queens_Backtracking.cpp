#include <iostream>
#include <vector>
using namespace std;

const int N = 8;

bool isSafe(const vector<vector<int>>& board, int row, int col) {
    // Check column
    for (int i = 0; i < row; ++i)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; --i, ++j)
        if (board[i][j]) return false;

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int row) {
    if (row == N) return true;

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solveNQueens(board, row + 1)) return true;
            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row)
            cout << (cell ? "Q " : ". ");
        cout << endl;
    }
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueens(board, 0)) {
        cout << "Solution to 8-Queens:\n";
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

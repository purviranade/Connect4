
#include <stdio.h>

#define ROWS 6
#define COLS 7

void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '_';
        }
    }
}

void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
   
    printf("\n");
}

int dropToken(char board[ROWS][COLS], int col, char token) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '_') {
            board[i][col] = token;
            return 1;
        }
    }
    return 0;
}

int checkWin(char board[ROWS][COLS], char token) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j + 3 < COLS && board[i][j] == token &&
                board[i][j + 1] == token && board[i][j + 2] == token &&
                board[i][j + 3] == token) return 1;

            if (i + 3 < ROWS && board[i][j] == token &&
                board[i + 1][j] == token && board[i + 2][j] == token &&
                board[i + 3][j] == token) return 1;

            if (i + 3 < ROWS && j + 3 < COLS && board[i][j] == token &&
                board[i + 1][j + 1] == token && board[i + 2][j + 2] == token &&
                board[i + 3][j + 3] == token) return 1;

            if (i - 3 >= 0 && j + 3 < COLS && board[i][j] == token &&
                board[i - 1][j + 1] == token && board[i - 2][j + 2] == token &&
                board[i - 3][j + 3] == token) return 1;
        }
    }
    return 0;
}

int isDraw(char board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == '_') return 0;
    }
    return 1;
}

 int main() {
    char board[ROWS][COLS];
    char playAgain = 'y';
    int currentPlayer;
    int move, win, draw;

    while (playAgain == 'y') {
        initializeBoard(board);
        currentPlayer = 1;
        win = draw = 0;

        while (!win && !draw) {
            printBoard(board);
            printf("Please enter a move : ", currentPlayer);
            scanf("%d", &move);

            if (move < 1 || move > COLS || !dropToken(board, move - 1, (currentPlayer == 1) ? 'x' : 'o')) {
                printf("Invalid input.\n");
                continue;
            }

            win = checkWin(board, (currentPlayer == 1) ? 'x' : 'o');
            draw = isDraw(board);

            if (!win && !draw) currentPlayer = 3 - currentPlayer; // Switch player
        }

        printBoard(board);

        if (win) {
            printf("Player %d has won!\n", currentPlayer);
        } else if (draw) {
            printf("The game was a draw!\n");
        }

        printf("Would you like to play again? y/n: ");
        scanf(" %c", &playAgain);

        while (playAgain != 'y' && playAgain != 'n') {
            printf("Invalid input. Would you like to play again? y/n: ");
            scanf(" %c", &playAgain);
        }
    }

    printf("Thank you for playing!\n");
    return 0;
}

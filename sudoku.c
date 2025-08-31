#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

void parse(int board[9][9]) {
        FILE *file = fopen("grid.txt", "r");
        if (file == NULL) {
                perror("Error opening file"); 
                fclose(file); 
                exit(1); 
        }

        char line[256]; // 256 char buffer
        int r = 0; 
        while (r < 9 && fgets(line, sizeof(line), file) != NULL) {
                char* number = strtok(line, " "); 
                for (int c = 0; c < 9; c++) {
                        board[r][c] = atoi(number); 
                        number = strtok(NULL, " "); 
                }
                r++; 
        }

        fclose(file);
}

void printboard(int board[9][9]) {
        printf("\033c");
        printf("Sudoku Board:\n");
        for (int i = 0; i < 24; i++) printf("-"); 
        printf("\n");
        for (int i = 0; i < 9; i++)
        {
                for (int j = 0; j < 9; j++)
                {
                        if (j == 0) {
                                printf("| ");
                        }
                        printf("%d ", board[i][j]);
                        if (j % 3 == 2) {
                                printf("| "); 
                        }
                }
                printf("\n");
                if (i % 3 == 2) {
                        for (int i = 0; i < 24; i++) printf("-"); 
                        printf("\n");
                }
        }
}

bool isSafe(int board[9][9], int r, int c, int number) {
        for (int i = 0; i < 9; i++) {
                if (board[r][i] == number) {
                        return false; 
                }
        }
        for (int i = 0; i < 9; i++) {
                if (board[i][c] == number) {
                        return false; 
                }
        }
 
        int startRow = r - (r%3); 
        int startCol = c - (c%3); 

        // example, r = 1, c = 4 -> sr = 0, sc = 3

        for (int i = startRow; i < startRow+3; i++) {
                for (int j = startCol; j < startCol + 3; j++) {
                        if (board[i][j] == number) return false; 
                }
        }
        return true; 
}

bool nextEmpty(int board[9][9], int *r, int *c) {
        for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; (j)++) {
                        if (board[i][j] == 0) {
                                *r = i; 
                                *c = j; 
                                return true; 
                        }
                }
        }
        return false; 
}

bool solve(int board[9][9]) {
        printboard(board);
        int r, c; 
        if (!nextEmpty(board, &r, &c)) {
                return true; 
        }
        for (int i = 1; i <= 9; i++) {
                if (isSafe(board, r, c, i)) {
                        board[r][c] = i; 
                        if (solve(board)) {
                                return true;  
                        }
                        board[r][c] = 0; 
                }
        }
        return false; 
}

int main() {
        int board[9][9]; 
        parse(board); // Parses grid.txt into the BOARD 2D Array
        printboard(board); 
        // GOAL SOLVE USING BACKTRACKING
        solve(board); 
}
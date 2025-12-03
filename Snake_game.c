#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

// Directions
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

int x, y, foodX, foodY, score;
int tailX[MAX_SNAKE_LENGTH], tailY[MAX_SNAKE_LENGTH];
int nTail;
enum Direction dir;
int gameOver;

// Moves cursor to top-left (no flicker)
void MoveCursorHome() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position = {0, 0};
    SetConsoleCursorPosition(hOut, Position);
}

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;

    // Safe food spawn inside boundaries
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;

    score = 0;
    nTail = 0;   // IMPORTANT FIX
}

void Draw() {
    MoveCursorHome();

    // Top Border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O");                     // Head
            else if (i == foodY && j == foodX)
                printf("F");                     // Food
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                if (!print) printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    // Bottom Border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void Input() {
    if (_kbhit()) {
        char key = _getch();

        // Prevent reverse movement
        if ((key == 'a' || key == 'A') && dir != RIGHT) dir = LEFT;
        else if ((key == 'd' || key == 'D') && dir != LEFT) dir = RIGHT;
        else if ((key == 'w' || key == 'W') && dir != DOWN) dir = UP;
        else if ((key == 's' || key == 'S') && dir != UP) dir = DOWN;
        else if (key == 'x' || key == 'X') gameOver = 1;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0]

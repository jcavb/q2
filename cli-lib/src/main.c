#include <stdio.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;
int score = 0;

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");

    screenGotoxy(0, 0);
    printf("Score: %d", score);
}

void saveScore() {
    FILE *file = fopen("score.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", score);
        fclose(file);
    } else {
        printf("Error saving score!");
    }
}

void loadScore() {
    FILE *file = fopen("score.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &score);
        fclose(file);
    } else {
        score = 0;
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    loadScore(); 

    printHello(x, y);
    screenUpdate();

    while (ch != 10)
    {
        if (keyhit()) 
        {
            ch = readch();
            screenSetColor(YELLOW, DARKGRAY);
            screenGotoxy(35, 22);
            printf("Key code : %d ", ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX + 1) {
                incX = -incX;
                score++; 
            }

            int newY = y + incY;
            if (newY >= MAXY - 1 || newY <= MINY + 1) {
                incY = -incY;
                score++;
            }

            printHello(newX, newY);
            screenUpdate();
        }
    }

    saveScore();
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

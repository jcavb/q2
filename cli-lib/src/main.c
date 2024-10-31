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

    // Display score
    screenGotoxy(0, 0); // Ajuste a posição conforme necessário
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
        score = 0; // Comece do zero se o arquivo não existir
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    
    loadScore(); // Carregar pontuação salva

    printHello(x, y);
    screenUpdate();

    while (ch != 10) //enter
    {
        if (keyhit()) 
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX + 1) {
                incX = -incX;
                score++; // Incrementar pontuação na colisão
            }

            int newY = y + incY;
            if (newY >= MAXY - 1 || newY <= MINY + 1) {
                incY = -incY;
                score++; // Incrementar pontuação na colisão
            }

            printKey(ch);
            printHello(newX, newY);
            screenUpdate();
        }
    }

    saveScore(); // Salvar pontuação ao sair
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

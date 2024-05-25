/*
 * Created by Arthur Borges and Raul Costa on 14/05/2024
 * For a project in a grad class
 * Based on tgfb/cli-lib


  Para compilar os arquivos

  Escreva no terminal:

  1.   gcc -I./include src/*.c -o BrickOut

./BrickOut

  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"

typedef struct {
  int x;
  int y;
} Cart;
Cart cord;

#define COLUNA 52
#define LINHA 20

int ballPosition = 0;
void telaInicio();

void DesenhaMapa(char **mapa);

void moveBall()
{
    ballPosition++; // Move the ball position, you can update this logic based on your requirements
    printf("\033[%d;0H[]\n", ballPosition); // Print the ball at the new position
}


int main() {
  char **mapa;
  int i, j;
  screenInit(1);
  telaInicio();
  screenClear();
  

  mapa = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinamicamente a matriz do labirinto
  for (i = 0; i < LINHA; i++) {
      mapa[i] = (char *)calloc(COLUNA + 1, sizeof(char));
  }

  char mapa_init[LINHA][COLUNA + 1] = {
      " * * *                                              ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      " === === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === === ",
      "                                                    ",
      "                                                    ",
      "                                                    ",
      "                         []                         ",
      "                      --------                      ",
      "                                                    "};

  for (i = 0; i < LINHA; i++) {
      strcpy(mapa[i], mapa_init[i]);
  }
  DesenhaMapa(mapa);

  keyboardInit();
  timerInit(1000); // Initialize the timer with a period of 1000 milliseconds
  while (1)
  {
      if (keyhit())
      {
          break;
      }
      if (timerTimeOver())
      {
          timerUpdateTimer(1000);
      }
  }
  timerDestroy();
  keyboardDestroy(); 
  
  

  return 0;
}

void telaInicio() {
  screenClear();
  int offsetX = (MAXX) / 2;
  int offsetY = (MAXY-6) / 2;

  char ch = '\0';

  screenGotoxy(offsetX, offsetY);
  printf("BrickOut");

  screenGotoxy(offsetX-2, offsetY + 1);
  printf("Instruções:");

  screenGotoxy(offsetX-10, offsetY + 2);
  printf(" - Use as teclas A e D para mover a base");
  screenGotoxy(offsetX-15, offsetY + 3);
  printf(" - Pressione qualquer tecla para começar o jogo");
  screenGotoxy(offsetX-5, offsetY + 4);
  printf(" - Quebre Tijolos com a bola");
  //    printf(" - 3 poderes podem apareçer (1- base maior, 2- mais vidas,
  //    3-multiplicador de pontos)\n");
  screenGotoxy(offsetX-25, offsetY + 4);
  printf(" -Para sair no meio do jogo, pressione ESC, para pausar pressione ENTER");
  screenGotoxy(offsetX, offsetY + 5);
  printf("   Boa sorte!");

  getchar();
}

void DesenhaMapa(char **mapa) {

  screenClear();

  int offsetX = (MAXX - COLUNA) / 2;
  int offsetY = (MAXY - LINHA) / 2;

  for (int y = 0; y < LINHA; y++) {
    screenGotoxy(offsetX + 1, offsetY + y + 1);
    for (int x = 0; x < COLUNA; x++) {
      char ch = mapa[y][x];
      if (ch == '-') {
        screenSetColor(WHITE, BLACK);
      } else if (ch == '*') {
        screenSetColor(RED, LIGHTRED);
      } else if (ch == '=') {
        screenSetColor(WHITE, WHITE);
      } else if (ch == '[') {
        screenSetColor(GREEN, LIGHTGREEN);
      } else if (ch == ']') {
        screenSetColor(GREEN, LIGHTGREEN);
      } else {
        screenSetColor(BLACK, BLACK);
      }
      printf("%c", ch);
    }
  }
  screenUpdate();
}
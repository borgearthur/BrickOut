/*
 * Created by Arthur Borges and Raul Costa on 14/05/2024
 * For a project in a grad class
 * Based on tgfb/cli-lib


  Para compilar os arquivos

  Escreva no terminal:

  1.   gcc -I./include src/*.c -o BrickOut

  2.  ./BrickOut

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

void telaInicio();

void DesenhaMapa(char **mapa);


int main() {
  screenInit(1);
  telaInicio();
  screenClear();

  char mapa[LINHA][COLUNA + 1] = {
      "                                                    ",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      " 111 111 111 111 111 111 111 111 111 111 111 111 111",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      "111 111 111 111 111 111 111 111 111 111 111 111 111 ",
      "                                                    ",
      "                                                    ",
      "                                                    ",
      "                    2                               ",
      "                 0000000                            ",
      "                                                    "};

  DesenhaMapa(mapa);

  return 0;
}

void telaInicio() {
  screenClear();
  int offsetX = (MAXX - 40) / 2;
  int offsetY = (MAXY - 10) / 2;

  char ch = '\0';

  screenGotoxy(offsetX, offsetY);
  printf("BrickOut");

  screenGotoxy(offsetX, offsetY + 1);
  printf("Instruções:");

  screenGotoxy(offsetX, offsetY + 2);
  printf(" - Use as teclas A e D para mover a base\n");
  printf(" - Pressione qualquer tecla para começar o jogo\n");
  printf(" - Quebre Tijolos com a bola\n");
  //    printf(" - 3 poderes podem apareçer (1- base maior, 2- mais vidas,
  //    3-multiplicador de pontos)\n");
  printf(" -Para sair no meio do jogo, pressione ESC, para pausar pressione "
         "ENTER\n\n");
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
      if (ch == '0') {
        screenSetColor(BROWN, BLACK);
      } else if (ch == '1') {
        screenSetColor(WHITE, BLACK);
      } else if (ch == '2') {
        screenSetColor(YELLOW, BLACK);
      } else {
        screenSetColor(BLACK, BLACK);
      }
      printf("%c", ch);
    }
  }
  screenUpdate();
}
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

#define COLUNA 52
#define LINHA 20
#define MAXX 80 
#define MAXY 24


typedef struct Cord{
int x;
int y;
}Cord;

int ballPosition = 0;
void telaInicio();

void DesenhaMapa(char **mapa);

void moveBarraA(int *x);
void moveBarraD(int *x);

void moveBola(Cord *bola, int barra, Cord *dir) {
    if (bola->y == 19 && abs(bola->x - barra) <= 6) {
       dir->y = -dir->y;
    }
}


int main() {
  int offsetX = (MAXX - COLUNA) / 2;
  int offsetY = (MAXY - LINHA) / 2;
  char **mapa, ch;
  int i, j;

  int  vidas = 3;
  int pontos = 0;
  Cord bola;
  Cord dir;
  bola->x = offSetX + 30;
  bola->y = 19;
  dir->x = 0;
  dir->y = 1;
int barra = offsetX + 23;
  screenInit(1);
  telaInicio();
  screenClear();
  

  mapa = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinamicamente a matriz do labirinto
  for (i = 0; i < LINHA; i++) {
      mapa[i] = (char *)calloc(COLUNA + 1, sizeof(char));
  }

  char mapa_init[LINHA][COLUNA + 1] = {
      "3                                               000",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "=== === === === === === === === === === === === ===",
      "                                                   ",
      "                                                   ",
      "                                                   ",
      "                         *                         ",
      "                      -------                      ",
      "                                                   "};

  for (i = 0; i < LINHA; i++) {
      strcpy(mapa[i], mapa_init[i]);
  }
  DesenhaMapa(mapa);

  keyboardInit();
  timerInit(1000);
  while (1){
      if (keyhit()){
          ch = readch();
        if (ch == 27){
          break;
        }
        if (ch == 10){
          while(1){
            screenGotoxy(LINHA+3,3);
            printf("Pressione ENTER para despausar");
            screenUpdate();
            ch = readch();
            if (ch == 10){
              screenGotoxy(LINHA+3,3);
              printf("                              ");
              screenUpdate();
              break;
            }
          }
        }
        if (ch =='a'){
          if (barra-1>offsetX+1){
            moveBarraA(&barra);
          }
        }
        if (ch =='d'){
          if (barra+7<MAXX-offsetX){
          moveBarraD(&barra);
          }
        }
      }
      if (timerTimeOver()){
        
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
  printf("Instruções:\n");

  screenGotoxy(offsetX-15, offsetY + 2);
  printf(" - Use as teclas A e D para mover a base");
  screenGotoxy(offsetX-15, offsetY + 3);
  printf(" - Pressione qualquer tecla para começar o jogo");
  screenGotoxy(offsetX-15, offsetY + 4);
  printf(" - Quebre Tijolos com a bola");
  //    printf(" - 3 poderes podem apareçer (1- base maior, 2- mais vidas,
  //    3-multiplicador de pontos)\n");
  screenGotoxy(offsetX-15, offsetY + 4);
  printf(" -Para sair no meio do jogo, pressione ESC, para pausar pressione ENTER\n");
  screenGotoxy(offsetX, offsetY + 5);
  printf("Boa sorte!");
  
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
      } else if (ch == '=') {
        screenSetColor(WHITE, WHITE);
      } else if (ch == '*') {
        screenSetColor(GREEN, BLACK);
      } else {
        screenSetColor(BLACK, BLACK);
      }
      printf("%c", ch);
    }
    screenGotoxy(offsetX+1,3);
    screenSetColor(RED, BLACK);
    printf("%d",mapa[0][0]-48);
    screenGotoxy(MAXX-offsetX-1,3);
    screenSetColor(YELLOW, BLACK);
    printf("%d",mapa[0][COLUNA]);

  }
  screenUpdate();
}

void moveBarraA(int *x){
  screenSetColor(WHITE, WHITE);
  screenGotoxy((*x)-1, 20);
  printf("-");
  screenGotoxy((*x)+6, 20);
  printf(" ");
  (*x)--;
  screenUpdate();
}

void moveBarraD(int *x){
  screenSetColor(WHITE, WHITE);
  screenGotoxy((*x)+6, 20);
  printf("-");
  screenGotoxy((*x)-1, 20);
  printf(" ");
  (*x)++;
  screenUpdate();
  }

/*
 * Created by Arthur Borges and Raul Costa on 14/05/2024
 * For a project in a grad class
 * Based on tgfb/cli-lib


  Para compilar os arquivos

  Escreva no terminal:
  /*Primeiramente, certifique-se de que todas as bibliotecas necessárias e o arquivo main.c estejam no mesmo diretório em sua máquina local, conforme disponibilizado no GitHub. Em seguida, execute o comando a seguir:
  */

1.   gcc -I../include keyboard.c main.c screen.c timer.c -o BrickOut

2.    ./BrickOut

  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/keyboard.h"
#include "../include/screen.h"
#include "../include/timer.h"

#define COLUNA 52
#define LINHA 20

typedef struct Cord{
int x;
int y;
}Cord;

int ballPosition = 0;
void telaInicio();

void DesenhaMapa(char **mapa);

void moveBarraA(int *x);
void moveBarraD(int *x);

void moveBola(Cord *bola, int barra, Cord*dir, int *pontos, int *vidas);



int main() {
  int offsetX = (MAXX - COLUNA) / 2;
  int offsetY = (MAXY - LINHA) / 2;
  char **mapa, ch;
  int i, j;

  int  vidas = 3;
  int pontos = 0;
  Cord *bola = (Cord*)malloc(sizeof(Cord));
  Cord *dir = (Cord*)malloc(sizeof(Cord));
  bola->x = offsetX + 26;
  bola->y = 19;
  dir->x = 0;
  dir->y = 0;
int barra = offsetX + 23;
  screenInit(1);
  telaInicio();
  screenClear();


  mapa = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinamicamente a matriz do labirinto
  for (i = 0; i < LINHA; i++) {
      mapa[i] = (char *)calloc(COLUNA + 1, sizeof(char));
  }

  char mapa_init[LINHA][COLUNA + 1] = {
      "                                                   ",
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
      "                                                   ",
      "                      -------                      ",
      "                                                   "};

  for (i = 0; i < LINHA; i++) {
      strcpy(mapa[i], mapa_init[i]);
  }
  DesenhaMapa(mapa);
  keyboardInit();
  timerInit(100);
  while (1){
      if (keyhit()){
          ch = readch();
        if (ch == 27){
          break;
        } else if (ch == 10){
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
        } else if (ch ==97){
          if (barra-2>offsetX){
            moveBarraA(&barra);
          }
        } else if (ch ==100){
          if (barra+8<MAXX-offsetX){
          moveBarraD(&barra);
          }
        }
      }
      if (timerTimeOver()){
        timerUpdateTimer(100);
        moveBola(bola, barra, dir, &pontos, &vidas);


        screenGotoxy(offsetX+1,2);
        screenSetColor(RED, BLACK);
        printf("%d",vidas);

        screenGotoxy(MAXX-offsetX-4,2);
        screenSetColor(YELLOW, BLACK);
        printf("%d",pontos);

        if (vidas == 0){
          screenGotoxy(LINHA+30,2);
          printf("Score final:");
          screenGotoxy(offsetX,22);
          screenUpdate();
          break;
        }
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

  screenGotoxy(offsetX-20, offsetY + 2);
  printf(" - Use as teclas A e D para mover a base");
  screenGotoxy(offsetX-20, offsetY + 3);
  printf(" - Pressione qualquer tecla para começar o jogo");
  screenGotoxy(offsetX-20, offsetY + 4);
  printf(" - Quebre Tijolos com a bola");
  screenGotoxy(offsetX-20, offsetY + 5);
  printf(" - 2 poderes podem apareçer (1- mais vidas, 2-multiplicador de pontos)\n");
  screenGotoxy(offsetX-20, offsetY + 6);
  printf(" -Para sair no meio do jogo, pressione ESC, para pausar pressione ENTER\n");
  screenGotoxy(offsetX, offsetY +7);
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
        screenSetColor(WHITE, WHITE);
      } else if (ch == '=') {
        screenSetColor(WHITE, WHITE);
      } else if (ch == '*') {
        screenSetColor(GREEN, BLACK);
      } else {
        screenSetColor(BLACK, BLACK);
      }
      printf("%c", ch);
    }
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


void moveBola(Cord *bola, int barra, Cord*dir, int*pontos, int *vidas){
    char ch = 0;
    int offsetX = (MAXX - COLUNA) / 2;
    if (bola->y == 19 && (bola->x - barra)<=6 && (bola->x - barra)>=0){
      dir->y=-1;
      if (barra+3==bola->x){
        dir->x = 0;
      }else if (barra+3>bola->x){
        dir->x = -1;
      }else{
        dir->x = 1;
      }
    }
    else{
      int tempx = bola->x+dir->x;
      int tempy = bola->y+dir->y;
      screenGotoxy(tempx, tempy);
      if (ch == '='){
        *pontos += 10;
        srand(time(NULL));
        int random = rand() % 4;
        if (random == 0){
          (*vidas)++;
        }else if (random == 1){
          (*pontos) *= 2;
        }
        screenGotoxy(bola->x, bola->y-1);
            printf(" ");
            dir->y = 1;
          }
      if (bola->x==offsetX+2){
        dir->x = 1;
      }else if (bola->x==MAXX-offsetX-1){
        dir->x = -1;  
      }if (bola->y==3){
        dir->y = 1;
      }if (bola->y==21){
        (*vidas)--;
        dir->y = -1;
      }
    }
    screenGotoxy(bola->x, bola->y);
    printf(" ");
    bola->x += dir->x;
    bola->y += dir->y;
    screenGotoxy(bola->x, bola->y);
    screenSetColor(GREEN, BLACK);
    printf("*");
    screenUpdate();
  }

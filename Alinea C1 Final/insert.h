#ifndef INSERT
#define INSERT

#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "errorMessage.h"
#include "ship.h"
#include "map.h"
#include "search.h"


/*----------------------Insert Manual-------------------------*/
/* Coloca os barcos de forma manual*/
void insertManual(Map *m);

/*----------------------Insert Random-----------------------*/

/* Coloca todos os barcos de forma aleatoria. Não esquecer de inciar a semente*/
void insertRandom(Map *m);

/* Encontra uma posição e direção para colocar um barco*/
void findSomePlace(Map *m, Ship *ship, Point *p, char *dir);

/* Encontra uma direção no ponto p para colocar o barco*/
int findSomeDir(Map *m, Ship *ship, Point *p, char *dir);


/*----------------------------Check-------------------------------*/

/* Retorna 1 caso seja possivel colocar o navio na possição p, com direção dir.
   case contrario retorna 0*/
int placeIsPossible(Map *level, Ship *ship, Point *p, char dir);

/* Retorna 1 caso esteja disponivel a configuração, i.e se nas dadas
   posições que o navio tem que ocupar, estãolivre. Caso não seja possivel
   retorna 0*/
int confAvaliable(Map *m, Ship *ship, Point *ref, char dir);

/* Retorna 1 caso as posições a volta onde o navio ocupara estão vazias.
   Caso contrario retorna 0*/
int voidAroundPoint(Map *root, Point *p);


/*----------------------Insert Ship-----------------------*/
/* Insere um tipo de navio  na posição ref com direção dir.
   Atenção que esta função não verifica se é possivel colocar o navio nessa
   posição, esse trabalho tem que ser feito antes.*/
void insertShip(Map *root, Ship *ship, Point *ref, char dir);

/* Coloca um apontador para ship na posição p.
   Atenção que esta função não verifica se é possivel colocar esse apontador
   podendo apanhar um exit.*/
void insertPointer(Map *root, Point *p, Ship *ship);

/* Modifica o variavel shoot de cell da posição p. Caso não exista é criado
   uma nova celula*/
void insertShoot(Map *root, Point *p, char shoot);

/* Modifica a variavel bit de cell da possição p. Caso não existe é criado
   uma nova celula*/
void insertBit(Map *root, Point *p, char bit);

/*-----------------------Dispara-------------------------*/
/* Esta função dispara no mapa, map, no ponto p. Retorna 1 caso tenha
   sido bem sucedido, caso contrario 0*/
int shoot(Map *map, Point *p);

/* Faz update da historia de disparos. Iremos fazer update do disparo
   na posição p. Caso cond=0 significa que o tiro falhou, se cond = 1
   significa que foi bem sucedido.*/
void updateHistory(Map *map, Point *p, int cond);

/* Retorna 1 se o disparo no ponto p fez afundar algum navio, caso
   contrario 0*/
int sunk(Map *map, Point *p);

/* Esta é uma função de teste. Devera somente ser usada na função sunk.*/
int testCondition(Map *map, Point *p);

/*---------------------Generate next/random-------------------------*/

/* Gera uma direção aleatoria:
 e -> East
 w -> West
 n -> North
 s -> South*/
void randomDir(char *dir);

/* Roda uma direção no sentido contrario ao ponteiros do relogio*/
void rotateDir(char *dir);

/* Gera um ponto aleatorio e mete a informaçãp em p*/
void randomPoint(Map *m, Point *p);


/*--------------------------Move Point------------------------------*/

/* Anda com o ponto para a esquerda. Caso saia do mapa ele é realocado
   noutra posição*/
void movePointLeft(Map *level, Point *p);

/* Anda com um ponto segundo um vertor de deslocação. A nova informação
   é colocada em *p*/
void movePointInDir(Point *ref, Point *vec, Point *p, char dir);

#endif

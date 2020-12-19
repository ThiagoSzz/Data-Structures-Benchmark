/* Arquivos com as funções de cada estrutura */

#include "desempenho_LSE.h"
#include "desempenho_AVL.h"
#include "desempenho_ABP.h"

/* Definições de valores */

//quantidade de dados a serem consultados
//para modificar, troque o valor "30" por qualquer outro entre (0, 32.768], respeitando a quantidade de dados inserida na estrutura
#define qtdValoresConsulta 30

/* Estruturas */

typedef struct{

    double tempoInsere; //armazena o tempo levado para a inserção de uma quantidade de dados em uma estrutura
    double tempoConsulta; //armazena o tempo levado para a consulta de uma quantidade de dados em uma estrutura

    long int compInsere; //armazena a quantidade de comparações feita pela operação de inserção em uma estrutura
    long int compConsulta; //armazena a quantidade de comparações feita pela operação de consulta em uma estrutura
}MEDIDAS;

/* Esqueleto das funções */

void quickSort(int *a, int esq, int dir);
double timer(double tempo, char momento[6]);
MEDIDAS coletaInfoLSE(char tipo[10], int quantidade, int listaValConsulta[], ptLSE *ptLista);
MEDIDAS coletaInfoABP(char tipo[10], int quantidade, int listaValConsulta[], pNodoA *arvABP);
MEDIDAS coletaInfoAVL(char tipo[10], int quantidade, int listaValConsulta[], pAVL *arvAVL);
void analisaResultados(MEDIDAS LSEo, MEDIDAS LSEa, MEDIDAS ABPo, MEDIDAS ABPa, MEDIDAS AVLo, MEDIDAS AVLa);

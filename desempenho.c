/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "desempenho.h"

/* Fun��es */

/* Objetivo: ordenar os elementos n�mericos de um array em ordem crescente utilizando o algoritmo Quick Sort

   Entradas:
   @par�metro *a := ponteiro para o primeiro elemento do array a ser ordenado,
   @par�metro esq := posi��o do in�cio e
   @par�metro dir := posi��o do fim a ser ordenado

   Sa�da: ponteiro para o primeiro elemento do array ordenado

   Exemplos: quickSort(dadosGerados, 0, 5000-1) --> ordena um array de n�meros com 5.000 elementos
             quickSort(dadosGerados, 0, 10000-1) --> ordena um array de n�meros com 10.000 elementos
             quickSort(dadosGerados, 0, 100000-1) --> ordena um array de n�meros com 100.000 elementos
             quickSort(dadosGerados, 0, 1000000-1) --> ordena um array de n�meros com 1.000.000 elementos */

void quickSort(int *a, int esq, int dir){

    int i, j;
    int x, y;

    i = esq; //in�cio da menor sub-lista
    j = dir; //final da maior sub-lista
    x = a[(esq + dir)/2]; //piv�

    while(i <= j){ //enquanto o tamanho das sub-listas n�o for igual
        while(a[i] < x && i < dir){ //e enquanto os menores

            i++;
        }
        while(a[j] > x && j > esq){ //e os maiores elementos da lista n�o forem encontrados na lista maior,
                                    //continua incrementando ou decrementando as vari�veis at� encontr�-los
            j--;
        }

        if(i <= j){ //ap�s encontr�-los, atualiza os valores para o menor ao in�cio e para o maior ao final
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > esq){ //se a posi��o do elemento a ser comparado for maior que a posi��o do primeiro elemento da lista

        quickSort(a, esq, j); //repete o ordenamento utilizando a m�dia entre os dois valores como piv�
    }
    if(i < dir){ //se a posi��o do elemento a ser comparado for menor que a posi��o do �ltimo elemento da lista

        quickSort(a, i, dir); //repete o ordenamento utilizando a m�dia entre os dois valores como piv�
    }

    //caso contr�rio, a ordena��o est� pronta
}

/* Objetivo: calcular o tempo de execu��o de uma parte do c�digo

   Entradas:
   @par�metro tempo := vari�vel [double] para armazenar o tempo
   @par�metro momento[6] := campo [string] para indicar se deve iniciar ou finalizar o timer

   Sa�da: indicar� quanto tempo a sua CPU demorou para executar o c�digo entre a primeira e a segunda execu��o da fun��o

   Exemplos: time = tempo(time, "inicio") --> inicia o timer
             time = tempo(time, "fim") --> finaliza o timer */

double timer(double tempo, char momento[6]){

    LARGE_INTEGER tempoAux; //vari�vel para armazenar os tempos

    if(strcmp(momento, "inicio") == 0){

        QueryPerformanceCounter(&tempoAux); //inicia o timer
        tempo = tempoAux.QuadPart;
    }
    else if(strcmp(momento, "fim") == 0){

        QueryPerformanceCounter(&tempoAux); //finaliza o timer
        tempo = (tempoAux.QuadPart - tempo)/(double)10000; //coleta o tempo decorrido do inicio ao fim e divide pela frequencia
    }

    return tempo; //retorna o tempo
}

/* Objetivo: coletar os tempos de execu��o e as quantidades de compara��es feitas para as opera��es de
             inser��o e de consulta sobre uma Lista Simplesmente Encadeada (LSE)

   Entradas:
   @par�metro tipo[10] := string que indicara se os dados devem ou n�o ser ordenados
   @par�metro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @par�metro listaValConsulta[] := lista contendo os valores a serem consultados
   @par�metro *ptLista := ponteiro para o primeiro elemento da lista

   Sa�da: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoLSE(char tipo[10], int quantidade, int listaValConsulta[], ptLSE *ptLista){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de compara��es feitas

    int i;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que ser�o gerados pela fun��o "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0; //como a inser��o � no in�cio, o campo "compInsere" permanecer� 0, j� que n�o h� compara��es feitas

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de gera��o dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inser��o na LSE

    for(i=0; i<quantidade; i++){ //insere os dados na lista

        ptLista = insereInicio(ptLista, dadosGerados[i]);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inser��o na LSE

    printf("."); //imprime ponto para indicar que passou a fase de inser��o dos dados

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na LSE

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na LSE

        consultaLista(ptLista, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na LSE

    medidas.compConsulta = aux[0]; //e atualiza a estrutura com a quantidade de compara��es feitas na consulta

    printf("."); //imprime ponto para indicar que passou a fase de consulta dos dados

    ptLista = destroiLista(ptLista); //destr�i a lista para liberar mem�ria

    return medidas; //retorna os dados coletados
}

/* Objetivo: coletar os tempos de execu��o e as quantidades de compara��es feitas para as opera��es de
             inser��o e de consulta sobre uma �rvore Bin�ria de Pesquisa (ABP)

   Entradas:
   @par�metro tipo[10] := string que indicara se os dados devem ou n�o ser ordenados
   @par�metro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @par�metro listaValConsulta[] := lista contendo os valores a serem consultados
   @par�metro *arvABP := ponteiro para o primeiro elemento da �rvore

   Sa�da: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoABP(char tipo[10], int quantidade, int listaValConsulta[], pNodoA *arvABP){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de compara��es feitas

    int i;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que ser�o gerados pela fun��o "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0;

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de gera��o dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inser��o na ABP

    for(i=0; i<quantidade; i++){ //insere os dados na ABP

        arvABP = insereABP(arvABP, dadosGerados[i], aux);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inser��o na ABP

    medidas.compInsere = aux[0]; //atualiza a estrutura com a qtd. de compara��es
    printf("."); //imprime ponto para indicar que passou a fase de inser��o dos dados

    aux[0]=0; //"re-inicializa" a vari�vel que ir� armazenar a qtd. de compara��es

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na ABP

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na ABP

        consultaABP(arvABP, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na ABP

    medidas.compConsulta = aux[0]; //atualiza a estrutura com a qtd. de compara��es
    printf("."); //imprime ponto para indicar que passou a fase de consulta de dados

    arvABP = liberaABP(arvABP); //destr�i a �rvore para liberar mem�ria

    return medidas; //retorna os dados coletados
}

/* Objetivo: coletar os tempos de execu��o e as quantidades de compara��es feitas para as opera��es de
             inser��o e de consulta sobre uma Lista Simplesmente Encadeada (LSE)

   Entradas:
   @par�metro tipo[10] := string que indicara se os dados devem ou n�o ser ordenados
   @par�metro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @par�metro listaValConsulta[] := lista contendo os valores a serem consultados
   @par�metro *arvAVL := ponteiro para o primeiro elemento da �rvore

   Sa�da: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoAVL(char tipo[10], int quantidade, int listaValConsulta[], pAVL *arvAVL){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de compara��es feitas

    int i;
    int *ok;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que ser�o gerados pela fun��o "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0;

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de gera��o dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inser��o na AVL

    for(i=0; i<quantidade; i++){ //insere os dados na AVL

        arvAVL = insereAVL(arvAVL, dadosGerados[i], &ok, aux);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inser��o na AVL

    medidas.compInsere = aux[0]; //atualiza a estrutura com a qtd. de compara��es
    printf("."); //imprime ponto para indicar que passou a fase de gera��o dos dados

    aux[0]=0; //"re-inicializa" a vari�vel que ir� armazenar a qtd. de compara��es

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na AVL

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na AVL

        consultaAVL(arvAVL, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na AVL

    medidas.compConsulta = aux[0]; //atualiza a estrutura com a qtd. de compara��es
    printf("."); //imprime ponto para indicar que passou a fase de consulta de dados

    arvAVL = liberaAVL(arvAVL); //destr�i a �rvore para liberar mem�ria

    return medidas; //retorna os dados coletados
}

/* Objetivo: analisar o retorno dos dados das fun��es respons�veis pela coleta de informa��es da avalia��o de desempenho
             das estruturas LSE, ABP e AVL com inser��o de dados ordenada e desordenada e imprimir qual estrutura obteve o
             melhor resultado

   Entradas:
   @par�metro LSEo := estrutura contendo os dados coletados pela avalia��o de desempenho da LSE com inser��o ordenada
   @par�metro LSEa := estrutura contendo os dados coletados pela avalia��o de desempenho da LSE com inser��o desordenada
   @par�metro ABPo := estrutura contendo os dados coletados pela avalia��o de desempenho da ABP com inser��o ordenada
   @par�metro ABPa := estrutura contendo os dados coletados pela avalia��o de desempenho da ABP com inser��o desordenada
   @par�metro AVLo := estrutura contendo os dados coletados pela avalia��o de desempenho da AVL com inser��o ordenada
   @par�metro AVLa := estrutura contendo os dados coletados pela avalia��o de desempenho da AVL com inser��o desordenada

   Sa�da: nenhuma */

void analisaResultados(MEDIDAS LSEo, MEDIDAS LSEa, MEDIDAS ABPo, MEDIDAS ABPa, MEDIDAS AVLo, MEDIDAS AVLa){

    //array contendo os tempos de inser��o ordenada e desordenada das tr�s estruturas
    double arrayTemposInsere[6]={LSEo.tempoInsere, LSEa.tempoInsere, ABPo.tempoInsere, ABPa.tempoInsere, AVLo.tempoInsere, AVLa.tempoInsere};
    //array contendo os tempos de consulta ap�s inser��o ordenada e desordenada das tr�s estruturas
    double arrayTemposConsulta[6]={LSEo.tempoConsulta, LSEa.tempoConsulta, ABPo.tempoConsulta, ABPa.tempoConsulta, AVLo.tempoConsulta, AVLa.tempoConsulta};
    //vari�vel auxiliar para a verifica��o do menor elemento de cada array acima
    double menorElementoTempos;

    //array contendo a qtd. de compara��es resultante da inser��o ordenada e desordenada das tr�s estruturas
    long int arrayComparacoesInsere[6]={LSEo.compInsere, LSEa.compInsere, ABPo.compInsere, ABPa.compInsere, AVLo.compInsere, AVLa.compInsere};
    //array contendo a qtd. de compara��es resultante da consulta ap�s inser��o ordenada e desordenada das tr�s estruturas
    long int arrayComparacoesConsulta[6]={LSEo.compConsulta, LSEa.compConsulta, ABPo.compConsulta, ABPa.compConsulta, AVLo.compConsulta, AVLa.compConsulta};
    //vari�vel auxiliar para a verifica��o do menor elemento de cada array acima
    long int menorElementoComparacoes;

    int i;

    //Compara��o dos tempos de insere
    menorElementoTempos = arrayTemposInsere[0]; //escolhe um valor qualquer para compara��o

    for(i=0; i<6; i++){ //enquanto n�o iterar os 6 elementos

        if(menorElementoTempos > arrayTemposInsere[i]){ //se o atual menor elemento n�o for maior que o valor comparado

            menorElementoTempos = arrayTemposInsere[i]; //atualiza a vari�vel de compara��o
        }
    }

    //imprime qual estrutura obteve o menor tempo de execu��o de inser��o
    if(menorElementoTempos == LSEo.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da LSE ordenada");
    else if(menorElementoTempos == LSEa.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da LSE aleatoria");
    else if(menorElementoTempos == ABPo.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da ABP ordenada");
    else if(menorElementoTempos == ABPa.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da ABP aleatoria");
    else if(menorElementoTempos == AVLo.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da AVL ordenada");
    else if(menorElementoTempos == AVLa.tempoInsere)
        printf("\n|| O menor tempo de execucao de insere foi da AVL aleatoria");
    printf(" --> %fms", menorElementoTempos); //e o menor valor

    //Compara��o dos tempos de consulta
    menorElementoTempos = arrayTemposConsulta[0]; //escolhe um valor qualquer para compara��o

    for(i=0; i<6; i++){ //enquanto n�o iterar os 6 elementos

        if(menorElementoTempos > arrayTemposConsulta[i]){ //se o atual menor elemento n�o for maior que o valor comparado

            menorElementoTempos = arrayTemposConsulta[i]; //atualiza a vari�vel de compara��o
        }
    }

    //imprime qual estrutura obteve o menor tempo de execu��o de consulta
    if(menorElementoTempos == LSEo.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da LSE ordenada");
    else if(menorElementoTempos == LSEa.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da LSE aleatoria");
    else if(menorElementoTempos == ABPo.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da ABP ordenada");
    else if(menorElementoTempos == ABPa.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da ABP aleatoria");
    else if(menorElementoTempos == AVLo.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da AVL ordenada");
    else if(menorElementoTempos == AVLa.tempoConsulta)
        printf("\n|| O menor tempo de execucao de consulta foi da AVL aleatoria");
    printf(" --> %fms", menorElementoTempos); //e o menor valor

    //Compara��o da qtd. de compara��es de insere
    menorElementoComparacoes = arrayComparacoesInsere[0]; //escolhe um valor qualquer para compara��o

    for(i=0; i<6; i++){ //enquanto n�o iterar os 6 valores

        if(menorElementoComparacoes > arrayComparacoesInsere[i]){ //se o atual menor elemento n�o for maior que o valor comparado

            menorElementoComparacoes = arrayComparacoesInsere[i]; //atualiza a vari�vel de compara��o
        }
    }

    //imprime qual estrutura obteve a menor quantidade de compara��es feitas
    if(menorElementoComparacoes == LSEo.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da LSE ordenada");
    else if(menorElementoComparacoes == LSEa.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da LSE aleatoria");
    else if(menorElementoComparacoes == ABPo.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da ABP ordenada");
    else if(menorElementoComparacoes == ABPa.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da ABP aleatoria");
    else if(menorElementoComparacoes == AVLo.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da AVL ordenada");
    else if(menorElementoComparacoes == AVLa.compInsere)
        printf("\n|| A menor quantidade de comparacoes de insere foi da AVL aleatoria");
    printf(" --> %ld comp.", menorElementoComparacoes); //e o menor valor

    //Compara��o da qtd. de compara��es de consulta
    menorElementoComparacoes = arrayComparacoesConsulta[0];

    for(i=0; i<6; i++){ //enquanto n�o iterar os 6 valores

        if(menorElementoComparacoes > arrayComparacoesConsulta[i]){ //se o atual menor elemento n�o for maior que o valor comparado

            menorElementoComparacoes = arrayComparacoesConsulta[i]; //atualiza a vari�vel de compara��o
        }
    }

    //imprime qual estrutura obteve a menor quantidade de compara��es feitas
    if(menorElementoComparacoes == LSEo.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da LSE ordenada");
    else if(menorElementoComparacoes == LSEa.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da LSE aleatoria");
    else if(menorElementoComparacoes == ABPo.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da ABP ordenada");
    else if(menorElementoComparacoes == ABPa.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da ABP aleatoria");
    else if(menorElementoComparacoes == AVLo.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da AVL ordenada");
    else if(menorElementoComparacoes == AVLa.compConsulta)
        printf("\n|| A menor quantidade de comparacoes de consulta foi da AVL aleatoria");
    printf(" --> %ld comp.", menorElementoComparacoes); //e o menor valor
}

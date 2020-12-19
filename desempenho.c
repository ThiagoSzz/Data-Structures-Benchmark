/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "desempenho.h"

/* Funções */

/* Objetivo: ordenar os elementos númericos de um array em ordem crescente utilizando o algoritmo Quick Sort

   Entradas:
   @parâmetro *a := ponteiro para o primeiro elemento do array a ser ordenado,
   @parâmetro esq := posição do início e
   @parâmetro dir := posição do fim a ser ordenado

   Saída: ponteiro para o primeiro elemento do array ordenado

   Exemplos: quickSort(dadosGerados, 0, 5000-1) --> ordena um array de números com 5.000 elementos
             quickSort(dadosGerados, 0, 10000-1) --> ordena um array de números com 10.000 elementos
             quickSort(dadosGerados, 0, 100000-1) --> ordena um array de números com 100.000 elementos
             quickSort(dadosGerados, 0, 1000000-1) --> ordena um array de números com 1.000.000 elementos */

void quickSort(int *a, int esq, int dir){

    int i, j;
    int x, y;

    i = esq; //início da menor sub-lista
    j = dir; //final da maior sub-lista
    x = a[(esq + dir)/2]; //pivô

    while(i <= j){ //enquanto o tamanho das sub-listas não for igual
        while(a[i] < x && i < dir){ //e enquanto os menores

            i++;
        }
        while(a[j] > x && j > esq){ //e os maiores elementos da lista não forem encontrados na lista maior,
                                    //continua incrementando ou decrementando as variáveis até encontrá-los
            j--;
        }

        if(i <= j){ //após encontrá-los, atualiza os valores para o menor ao início e para o maior ao final
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > esq){ //se a posição do elemento a ser comparado for maior que a posição do primeiro elemento da lista

        quickSort(a, esq, j); //repete o ordenamento utilizando a média entre os dois valores como pivô
    }
    if(i < dir){ //se a posição do elemento a ser comparado for menor que a posição do último elemento da lista

        quickSort(a, i, dir); //repete o ordenamento utilizando a média entre os dois valores como pivô
    }

    //caso contrário, a ordenação está pronta
}

/* Objetivo: calcular o tempo de execução de uma parte do código

   Entradas:
   @parâmetro tempo := variável [double] para armazenar o tempo
   @parâmetro momento[6] := campo [string] para indicar se deve iniciar ou finalizar o timer

   Saída: indicará quanto tempo a sua CPU demorou para executar o código entre a primeira e a segunda execução da função

   Exemplos: time = tempo(time, "inicio") --> inicia o timer
             time = tempo(time, "fim") --> finaliza o timer */

double timer(double tempo, char momento[6]){

    LARGE_INTEGER tempoAux; //variável para armazenar os tempos

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

/* Objetivo: coletar os tempos de execução e as quantidades de comparações feitas para as operações de
             inserção e de consulta sobre uma Lista Simplesmente Encadeada (LSE)

   Entradas:
   @parâmetro tipo[10] := string que indicara se os dados devem ou não ser ordenados
   @parâmetro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @parâmetro listaValConsulta[] := lista contendo os valores a serem consultados
   @parâmetro *ptLista := ponteiro para o primeiro elemento da lista

   Saída: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoLSE(char tipo[10], int quantidade, int listaValConsulta[], ptLSE *ptLista){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de comparações feitas

    int i;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que serão gerados pela função "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0; //como a inserção é no início, o campo "compInsere" permanecerá 0, já que não há comparações feitas

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de geração dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inserção na LSE

    for(i=0; i<quantidade; i++){ //insere os dados na lista

        ptLista = insereInicio(ptLista, dadosGerados[i]);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inserção na LSE

    printf("."); //imprime ponto para indicar que passou a fase de inserção dos dados

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na LSE

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na LSE

        consultaLista(ptLista, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na LSE

    medidas.compConsulta = aux[0]; //e atualiza a estrutura com a quantidade de comparações feitas na consulta

    printf("."); //imprime ponto para indicar que passou a fase de consulta dos dados

    ptLista = destroiLista(ptLista); //destrói a lista para liberar memória

    return medidas; //retorna os dados coletados
}

/* Objetivo: coletar os tempos de execução e as quantidades de comparações feitas para as operações de
             inserção e de consulta sobre uma Árvore Binária de Pesquisa (ABP)

   Entradas:
   @parâmetro tipo[10] := string que indicara se os dados devem ou não ser ordenados
   @parâmetro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @parâmetro listaValConsulta[] := lista contendo os valores a serem consultados
   @parâmetro *arvABP := ponteiro para o primeiro elemento da árvore

   Saída: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoABP(char tipo[10], int quantidade, int listaValConsulta[], pNodoA *arvABP){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de comparações feitas

    int i;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que serão gerados pela função "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0;

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de geração dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inserção na ABP

    for(i=0; i<quantidade; i++){ //insere os dados na ABP

        arvABP = insereABP(arvABP, dadosGerados[i], aux);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inserção na ABP

    medidas.compInsere = aux[0]; //atualiza a estrutura com a qtd. de comparações
    printf("."); //imprime ponto para indicar que passou a fase de inserção dos dados

    aux[0]=0; //"re-inicializa" a variável que irá armazenar a qtd. de comparações

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na ABP

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na ABP

        consultaABP(arvABP, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na ABP

    medidas.compConsulta = aux[0]; //atualiza a estrutura com a qtd. de comparações
    printf("."); //imprime ponto para indicar que passou a fase de consulta de dados

    arvABP = liberaABP(arvABP); //destrói a árvore para liberar memória

    return medidas; //retorna os dados coletados
}

/* Objetivo: coletar os tempos de execução e as quantidades de comparações feitas para as operações de
             inserção e de consulta sobre uma Lista Simplesmente Encadeada (LSE)

   Entradas:
   @parâmetro tipo[10] := string que indicara se os dados devem ou não ser ordenados
   @parâmetro quantidade := quantidade de elementos para ser gerada e inserida na estrutura
   @parâmetro listaValConsulta[] := lista contendo os valores a serem consultados
   @parâmetro *arvAVL := ponteiro para o primeiro elemento da árvore

   Saída: estrutura contendo as medidas coletadas descritas acima */

MEDIDAS coletaInfoAVL(char tipo[10], int quantidade, int listaValConsulta[], pAVL *arvAVL){

    MEDIDAS medidas; //estrutura para armazenar as info.

    long int aux[1]={0}; //ponteiro para armazenar a qtd. de comparações feitas

    int i;
    int *ok;
    int *dadosGerados; //primeiro elemento do array de tamanho "quantidade"
    dadosGerados = malloc(quantidade * sizeof(int));

    srand(time(0)); //randomiza os valores que serão gerados pela função "rand()"

    medidas.compInsere = 0; //inicializa os membros da estrutura MEDIDAS
    medidas.compConsulta = 0;

    for(i=0; i<quantidade; i++){ //incorpora os dados gerados ao array

        dadosGerados[i] = rand();
    }

    if(strcmp(tipo, "ordenados") == 0){ //se for pedido, ordena os dados

        quickSort(dadosGerados, 0, quantidade-1);
    }

    printf("."); //imprime ponto para indicar que passou a fase de geração dos dados

    medidas.tempoInsere = timer(medidas.tempoInsere, "inicio"); //inicializa o timer que armazena o tempo de inserção na AVL

    for(i=0; i<quantidade; i++){ //insere os dados na AVL

        arvAVL = insereAVL(arvAVL, dadosGerados[i], &ok, aux);
    }

    medidas.tempoInsere = timer(medidas.tempoInsere, "fim"); //finaliza o timer que armazena o tempo de inserção na AVL

    medidas.compInsere = aux[0]; //atualiza a estrutura com a qtd. de comparações
    printf("."); //imprime ponto para indicar que passou a fase de geração dos dados

    aux[0]=0; //"re-inicializa" a variável que irá armazenar a qtd. de comparações

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "inicio"); //inicializa o timer que armazena o tempo de consulta na AVL

    for(i=0; i<qtdValoresConsulta; i++){ //consulta a quantidade "qtdValoresConsulta" de dados na AVL

        consultaAVL(arvAVL, listaValConsulta[i], aux);
    }

    medidas.tempoConsulta = timer(medidas.tempoConsulta, "fim"); //finaliza o timer que armazena o tempo de consulta na AVL

    medidas.compConsulta = aux[0]; //atualiza a estrutura com a qtd. de comparações
    printf("."); //imprime ponto para indicar que passou a fase de consulta de dados

    arvAVL = liberaAVL(arvAVL); //destrói a árvore para liberar memória

    return medidas; //retorna os dados coletados
}

/* Objetivo: analisar o retorno dos dados das funções responsáveis pela coleta de informações da avaliação de desempenho
             das estruturas LSE, ABP e AVL com inserção de dados ordenada e desordenada e imprimir qual estrutura obteve o
             melhor resultado

   Entradas:
   @parâmetro LSEo := estrutura contendo os dados coletados pela avaliação de desempenho da LSE com inserção ordenada
   @parâmetro LSEa := estrutura contendo os dados coletados pela avaliação de desempenho da LSE com inserção desordenada
   @parâmetro ABPo := estrutura contendo os dados coletados pela avaliação de desempenho da ABP com inserção ordenada
   @parâmetro ABPa := estrutura contendo os dados coletados pela avaliação de desempenho da ABP com inserção desordenada
   @parâmetro AVLo := estrutura contendo os dados coletados pela avaliação de desempenho da AVL com inserção ordenada
   @parâmetro AVLa := estrutura contendo os dados coletados pela avaliação de desempenho da AVL com inserção desordenada

   Saída: nenhuma */

void analisaResultados(MEDIDAS LSEo, MEDIDAS LSEa, MEDIDAS ABPo, MEDIDAS ABPa, MEDIDAS AVLo, MEDIDAS AVLa){

    //array contendo os tempos de inserção ordenada e desordenada das três estruturas
    double arrayTemposInsere[6]={LSEo.tempoInsere, LSEa.tempoInsere, ABPo.tempoInsere, ABPa.tempoInsere, AVLo.tempoInsere, AVLa.tempoInsere};
    //array contendo os tempos de consulta após inserção ordenada e desordenada das três estruturas
    double arrayTemposConsulta[6]={LSEo.tempoConsulta, LSEa.tempoConsulta, ABPo.tempoConsulta, ABPa.tempoConsulta, AVLo.tempoConsulta, AVLa.tempoConsulta};
    //variável auxiliar para a verificação do menor elemento de cada array acima
    double menorElementoTempos;

    //array contendo a qtd. de comparações resultante da inserção ordenada e desordenada das três estruturas
    long int arrayComparacoesInsere[6]={LSEo.compInsere, LSEa.compInsere, ABPo.compInsere, ABPa.compInsere, AVLo.compInsere, AVLa.compInsere};
    //array contendo a qtd. de comparações resultante da consulta após inserção ordenada e desordenada das três estruturas
    long int arrayComparacoesConsulta[6]={LSEo.compConsulta, LSEa.compConsulta, ABPo.compConsulta, ABPa.compConsulta, AVLo.compConsulta, AVLa.compConsulta};
    //variável auxiliar para a verificação do menor elemento de cada array acima
    long int menorElementoComparacoes;

    int i;

    //Comparação dos tempos de insere
    menorElementoTempos = arrayTemposInsere[0]; //escolhe um valor qualquer para comparação

    for(i=0; i<6; i++){ //enquanto não iterar os 6 elementos

        if(menorElementoTempos > arrayTemposInsere[i]){ //se o atual menor elemento não for maior que o valor comparado

            menorElementoTempos = arrayTemposInsere[i]; //atualiza a variável de comparação
        }
    }

    //imprime qual estrutura obteve o menor tempo de execução de inserção
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

    //Comparação dos tempos de consulta
    menorElementoTempos = arrayTemposConsulta[0]; //escolhe um valor qualquer para comparação

    for(i=0; i<6; i++){ //enquanto não iterar os 6 elementos

        if(menorElementoTempos > arrayTemposConsulta[i]){ //se o atual menor elemento não for maior que o valor comparado

            menorElementoTempos = arrayTemposConsulta[i]; //atualiza a variável de comparação
        }
    }

    //imprime qual estrutura obteve o menor tempo de execução de consulta
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

    //Comparação da qtd. de comparações de insere
    menorElementoComparacoes = arrayComparacoesInsere[0]; //escolhe um valor qualquer para comparação

    for(i=0; i<6; i++){ //enquanto não iterar os 6 valores

        if(menorElementoComparacoes > arrayComparacoesInsere[i]){ //se o atual menor elemento não for maior que o valor comparado

            menorElementoComparacoes = arrayComparacoesInsere[i]; //atualiza a variável de comparação
        }
    }

    //imprime qual estrutura obteve a menor quantidade de comparações feitas
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

    //Comparação da qtd. de comparações de consulta
    menorElementoComparacoes = arrayComparacoesConsulta[0];

    for(i=0; i<6; i++){ //enquanto não iterar os 6 valores

        if(menorElementoComparacoes > arrayComparacoesConsulta[i]){ //se o atual menor elemento não for maior que o valor comparado

            menorElementoComparacoes = arrayComparacoesConsulta[i]; //atualiza a variável de comparação
        }
    }

    //imprime qual estrutura obteve a menor quantidade de comparações feitas
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

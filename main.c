/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "desempenho.h"

/* Fun��o principal */

int main(void){

    MEDIDAS LSE_ord[4]={0}, ABP_ord[4]={0}, AVL_ord[4]={0}; //estruturas para armazenar as medidas das ED com inser��o ordenada
    MEDIDAS LSE_ale[4]={0}, ABP_ale[4]={0}, AVL_ale[4]={0}; //estruturas para armazenar as medidas das ED com inser��o desordenada
    MEDIDAS aux; //estrutura auxiliar para coletar o retorno das fun��es

    int i;
    int quantidade; //quantidade de dados a ser gerada
    int iteracaoQuantidade=0; //vari�vel para iterar a avalia��o das quatro quantidades de dados geradas
    int iteracaoBenchmark=1; //vari�vel para iterar a repeti��o da coleta de dados tr�s vezes
    int listaValConsulta[qtdValoresConsulta]={}; //array contendo os valores a serem consultados pelas estruturas

    ptLSE *ptLista = criaLista(); //inicializa a lista
    pNodoA *arvABP = NULL; //inicializa a ABP
    pAVL *arvAVL = NULL; //inicializa a AVL

    srand(time(0)); //randomiza��o dos dados gerados pela fun��o "rand()"

    for(i=0; i<qtdValoresConsulta; i++){ //coloca os valores gerados na lista

        listaValConsulta[i] = rand();
    }

    do{
        do{

            switch(iteracaoQuantidade){ //itera as quatro quantidades de dados gerados

                case 0: //5.000 n�meros
                printf("\n|| Iniciando os calculos da qtd. 5.000");
                printf("\n|| Loop: %d", iteracaoBenchmark);
                quantidade = 5000;
                break;

                case 1: //10.000 n�meros
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n|| Iniciando os calculos da qtd. 10.000");
                printf("\n|| Loop: %d", iteracaoBenchmark);
                quantidade = 10000;
                break;

                case 2: //100.000 n�meros
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n|| Iniciando os calculos da qtd. 100.000");
                printf("\n|| Loop: %d", iteracaoBenchmark);
                quantidade = 100000;
                break;

                case 3: //1.000.000 n�meros
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n|| Iniciando os calculos da qtd. 1.000.000");
                printf("\n|| Loop: %d", iteracaoBenchmark);
                quantidade = 1000000;
                break;
            }

            //avalia��o de desempenho da LSE com inser��o ordenada de dados
            printf("\n|| Dados ordenados    Status");
            printf("\n|| LSE calculando  ");
            aux = coletaInfoLSE("ordenados", quantidade, listaValConsulta, ptLista);
            LSE_ord[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            LSE_ord[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                LSE_ord[iteracaoQuantidade].compInsere = 0; //como a LSE s� insere ao in�cio, nenhuma compara��o em inser��o � feita
                LSE_ord[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            //avalia��o de desempenho da ABP com inser��o ordenada de dados
            printf("\n|| ABP calculando  ");
            aux = coletaInfoABP("ordenados", quantidade, listaValConsulta, arvABP);
            ABP_ord[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            ABP_ord[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                ABP_ord[iteracaoQuantidade].compInsere = aux.compInsere;
                ABP_ord[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            //avalia��o de desempenho da AVL com inser��o ordenada de dados
            printf("\n|| AVL calculando  ");
            aux = coletaInfoAVL("ordenados", quantidade, listaValConsulta, arvAVL);
            AVL_ord[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            AVL_ord[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                AVL_ord[iteracaoQuantidade].compInsere = aux.compInsere;
                AVL_ord[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            //avalia��o de desempenho da LSE com inser��o desordenada de dados
            printf("\n|| Dados aleatorios   Status");
            printf("\n|| LSE calculando  ");
            aux = coletaInfoLSE("aleatorio", quantidade, listaValConsulta, ptLista);
            LSE_ale[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            LSE_ale[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                LSE_ale[iteracaoQuantidade].compInsere = 0;
                LSE_ale[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            //avalia��o de desempenho da ABP com inser��o desordenada de dados
            printf("\n|| ABP calculando  ");
            aux = coletaInfoABP("aleatorio", quantidade, listaValConsulta, arvABP);
            ABP_ale[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            ABP_ale[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                ABP_ale[iteracaoQuantidade].compInsere = aux.compInsere;
                ABP_ale[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            //avalia��o de desempenho da AVL com inser��o desordenada de dados
            printf("\n|| AVL calculando  ");
            aux = coletaInfoAVL("aleatorio", quantidade, listaValConsulta, arvAVL);
            AVL_ale[iteracaoQuantidade].tempoInsere += aux.tempoInsere;
            AVL_ale[iteracaoQuantidade].tempoConsulta += aux.tempoConsulta;
            if(iteracaoBenchmark == 1){ //coleta a qtd. de compara��es somente se for no primeiro loop, j� que o valor � fixo

                AVL_ale[iteracaoQuantidade].compInsere = aux.compInsere;
                AVL_ale[iteracaoQuantidade].compConsulta = aux.compConsulta;
            }
            printf("  ok");

            iteracaoQuantidade++; //incrementa a vari�vel de itera��o da quantidade de dados gerados sendo analisada
        }while(iteracaoQuantidade != 4); //enquanto a vari�vel de itera��o (iniciada em 0) n�o atingir a quarta itera��o, continua

        system("cls");
        iteracaoQuantidade=0; //reinicia a vari�vel de itera��o das quatro quantidades de dados gerados
        iteracaoBenchmark++; //incrementa a vari�vel de itera��o dos tr�s loops
    }while(iteracaoBenchmark != 4); //enquanto a vari�vel de itera��o (iniciada em 1) n�o atingir a quarta itera��o, continua

    for(i=0; i<4; i++){ //efetua o c�lculo da m�dia dos valores coletados nas tr�s itera��es

        // Tempos do insere
        LSE_ord[i].tempoInsere = LSE_ord[i].tempoInsere/3.0;
        LSE_ale[i].tempoInsere = LSE_ale[i].tempoInsere/3.0;

        ABP_ord[i].tempoInsere = ABP_ord[i].tempoInsere/3.0;
        ABP_ale[i].tempoInsere = ABP_ale[i].tempoInsere/3.0;

        AVL_ord[i].tempoInsere = AVL_ord[i].tempoInsere/3.0;
        AVL_ale[i].tempoInsere = AVL_ale[i].tempoInsere/3.0;

        // Tempos da consulta
        LSE_ord[i].tempoConsulta = LSE_ord[i].tempoConsulta/3.0;
        LSE_ale[i].tempoConsulta = LSE_ale[i].tempoConsulta/3.0;

        ABP_ord[i].tempoConsulta = ABP_ord[i].tempoConsulta/3.0;
        ABP_ale[i].tempoConsulta = ABP_ale[i].tempoConsulta/3.0;

        AVL_ord[i].tempoConsulta = AVL_ord[i].tempoConsulta/3.0;
        AVL_ale[i].tempoConsulta = AVL_ale[i].tempoConsulta/3.0;
    }

    for(i=0; i<4; i++){ //inicia a impress�o dos resultados

        switch(i){ //itera as quatro quantidades de dados gerados

            case 0:
            quantidade=5000;
            break;

            case 1:
            quantidade=10000;
            break;

            case 2:
            quantidade=100000;
            break;

            case 3:
            quantidade=1000000;
            break;
        }

        printf("----------------------------------------------\n");
        printf("\n|| Desempenho da >LSE< [%d elementos]", quantidade);
        //impress�o dos resultados da estrutura LSE com inser��o ordenada
        printf("\n|| Dados ordenados: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", LSE_ord[i].tempoInsere, LSE_ord[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", LSE_ord[i].tempoConsulta, LSE_ord[i].compConsulta);
        //impress�o dos resultados da estrutura LSE com inser��o desordenada
        printf("\n|| Dados aleatorios: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", LSE_ale[i].tempoInsere, LSE_ale[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", LSE_ale[i].tempoConsulta, LSE_ale[i].compConsulta);

        printf("\n|| Desempenho da >ABP< [%d elementos]: ", quantidade);
        //impress�o dos resultados da estrutura ABP com inser��o ordenada
        printf("\n|| Dados ordenados: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", ABP_ord[i].tempoInsere, ABP_ord[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", ABP_ord[i].tempoConsulta, ABP_ord[i].compConsulta);
        //impress�o dos resultados da estrutura ABP com inser��o desordenada
        printf("\n|| Dados aleatorios: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", ABP_ale[i].tempoInsere, ABP_ale[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", ABP_ale[i].tempoConsulta, ABP_ale[i].compConsulta);

        printf("\n|| Desempenho da >AVL< [%d elementos]: ", quantidade);
        //impress�o dos resultados da estrutura AVL com inser��o ordenada
        printf("\n|| Dados ordenados: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", AVL_ord[i].tempoInsere, AVL_ord[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", AVL_ord[i].tempoConsulta, AVL_ord[i].compConsulta);
        //impress�o dos resultados da estrutura AVL com inser��o desordenada
        printf("\n|| Dados aleatorios: ");
        printf("\n|| Insercao: %fms e %ld comparacoes", AVL_ale[i].tempoInsere, AVL_ale[i].compInsere);
        printf("\n|| Consulta: %fms e %ld comparacoes\n", AVL_ale[i].tempoConsulta, AVL_ale[i].compConsulta);

        //analisa e imprime quais estruturas obtiveram o melhor resultado para a quantidade de dados gerados atual
        analisaResultados(LSE_ord[i], LSE_ale[i], ABP_ord[i], ABP_ale[i], AVL_ord[i], AVL_ale[i]);

        printf("\n\n");
    }

    return 0; //fim
}

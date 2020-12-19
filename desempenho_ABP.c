/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_ABP.h"

/* Funções */

/* Objetivo: inserir valores em uma ABP

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro ch := valor a ser inserido na árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore com o novo nodo inserido */

pNodoA* insereABP(pNodoA *a, tipoinfo ch, long int qtdComparacoes[])
{

    qtdComparacoes[0]+=1;
    if (a == NULL)
    {
        a =  (pNodoA*) malloc(sizeof(pNodoA));
        a->info = ch;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else
    {
        qtdComparacoes[0]+=2;
        if (ch < a->info){
            a->esq = insereABP(a->esq,ch, qtdComparacoes);
        }
        else if (ch > a->info){
            qtdComparacoes[0]+=1;
            a->dir = insereABP(a->dir,ch, qtdComparacoes);
        }

    }

    return a;
}

/* Objetivo: consultar um nodo na árvore

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro chave := valor a ser consultado na árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: sub-árvore cuja raíz é o nodo consultado ou "NULL" se o valor não fizer parte da árvore */

pNodoA* consultaABP(pNodoA *a, tipoinfo chave, long int qtdComparacoes[])
{
    qtdComparacoes[0]+=1;
    if (a!=NULL)
    {
        qtdComparacoes[0]+=1;
        if (a->info == chave)
        {
            return a;
        }
        else
        {
            qtdComparacoes[0]+=2;
            if (a->info > chave)
            {
                return consultaABP(a->esq,chave, qtdComparacoes);
            }
            else if (a->info < chave)
            {
                qtdComparacoes[0]+=1;
                return consultaABP(a->dir,chave, qtdComparacoes);
            }
            else
            {
                qtdComparacoes[0]+=2;
                return a;
            }

        }
    }
    else
    {
        qtdComparacoes[0]+=1;
        return NULL;
    }
}

/* Objetivo: liberar a memória alocada pela criação de uma árvore

   Entrada:
   @parâmetro *a := ponteiro para a raíz da árvore

   Saída: "NULL", indicando árvore vazia */

pNodoA* liberaABP (pNodoA *a)
{
    if (a!=NULL)
    {
        liberaABP(a->esq); /* exclui nodos a esquerda */
        liberaABP(a->dir); /* exclui nodos a direita */
        free(a); /* libera raiz */
    }

    return NULL;
}

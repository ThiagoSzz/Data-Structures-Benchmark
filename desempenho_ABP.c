/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_ABP.h"

/* Fun��es */

/* Objetivo: inserir valores em uma ABP

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro ch := valor a ser inserido na �rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore com o novo nodo inserido */

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

/* Objetivo: consultar um nodo na �rvore

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro chave := valor a ser consultado na �rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: sub-�rvore cuja ra�z � o nodo consultado ou "NULL" se o valor n�o fizer parte da �rvore */

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

/* Objetivo: liberar a mem�ria alocada pela cria��o de uma �rvore

   Entrada:
   @par�metro *a := ponteiro para a ra�z da �rvore

   Sa�da: "NULL", indicando �rvore vazia */

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

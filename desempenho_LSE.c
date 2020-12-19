/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_LSE.h"

/* Fun��es */

/* Objetivo: inicializar uma LSE

   Entrada: nenhuma

   Sa�da: "NULL", indicando lista vazia */


ptLSE *criaLista (void)
{
    return NULL;
}

/* Objetivo: consulta um valor na lista

   Entrada:
   @par�metro *ptLista := ponteiro para o primeiro elemento da lista
   @par�metro num := valor a ser consultado na lista
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: o endere�o do valor na lista, ou "NULL" se n�o fizer parte da lista */

ptLSE* consultaLista (ptLSE *ptLista, int num, long int qtdComparacoes[])
{
    ptLSE* ptaux=ptLista;

    qtdComparacoes[0]+=1;
    if(ptLista == NULL)
    {
        //printf("Lista vazia \n");
    }
    else
    {
        qtdComparacoes[0]+=1;
        for(ptaux=ptLista; ptaux!= NULL; ptaux = ptaux ->prox)
        {
            qtdComparacoes[0]+=1;
            if(ptaux->numero==num)
            {
                //printf("Item encontrado na lista \n");
                return ptaux;
            }
        }
    }

    return NULL;
}

/* Objetivo: liberar a mem�ria alocada pela cria��o de uma lista

   Entrada:
   @par�metro *ptLista := ponteiro para o primeiro elemento da lista

   Sa�da: "NULL", indicando lista vazia */

ptLSE* destroiLista(ptLSE *ptLista){

   ptLSE *ptaux; //ponteiro auxiliar para percorrer a lista

   while (ptLista != NULL)
   {
         ptaux = ptLista;
         ptLista = ptLista->prox;
         free(ptaux);
   }

   free(ptLista);
   return NULL;
}

/* Objetivo: inserir um valor ao in�cio da lista

   Entrada:
   @par�metro *ptLista := ponteiro para o primeiro elemento da lista
   @par�metro num := valor a ser inserido na lista

   Sa�da: lista com o novo valor inserido */

ptLSE* insereInicio(ptLSE *ptLista, int num)
{
    ptLSE* novo;

    novo = (ptLSE*) malloc(sizeof(ptLSE));
    novo->prox = ptLista;
    ptLista = novo;

    return ptLista;
}

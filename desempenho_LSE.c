/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_LSE.h"

/* Funções */

/* Objetivo: inicializar uma LSE

   Entrada: nenhuma

   Saída: "NULL", indicando lista vazia */


ptLSE *criaLista (void)
{
    return NULL;
}

/* Objetivo: consulta um valor na lista

   Entrada:
   @parâmetro *ptLista := ponteiro para o primeiro elemento da lista
   @parâmetro num := valor a ser consultado na lista
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: o endereço do valor na lista, ou "NULL" se não fizer parte da lista */

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

/* Objetivo: liberar a memória alocada pela criação de uma lista

   Entrada:
   @parâmetro *ptLista := ponteiro para o primeiro elemento da lista

   Saída: "NULL", indicando lista vazia */

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

/* Objetivo: inserir um valor ao início da lista

   Entrada:
   @parâmetro *ptLista := ponteiro para o primeiro elemento da lista
   @parâmetro num := valor a ser inserido na lista

   Saída: lista com o novo valor inserido */

ptLSE* insereInicio(ptLSE *ptLista, int num)
{
    ptLSE* novo;

    novo = (ptLSE*) malloc(sizeof(ptLSE));
    novo->prox = ptLista;
    ptLista = novo;

    return ptLista;
}

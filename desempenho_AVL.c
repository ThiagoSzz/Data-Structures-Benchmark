/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_AVL.h"

/* Funções */

/* Objetivo: inserir nodos em uma AVL

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro x := informação a ser inserida na AVL
   @parâmetro *ok := ponteiro que indica se há necessidade de fazer rotações
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore com o nodo inserido */

pAVL* insereAVL (pAVL *a, TipoInfo x, int *ok, long int qtdComparacoes[])
{
    qtdComparacoes[0]+=1;
    if (a == NULL)
    {
        a = (pAVL*) malloc(sizeof(pAVL));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->fat = 0;
        *ok = 1;
    }
    else
    {
        qtdComparacoes[0]+=2;
        if (x < a->info)
        {
            qtdComparacoes[0]+=1;
            a->esq = insereAVL(a->esq,x,ok, qtdComparacoes);
            if (*ok)
            {
                qtdComparacoes[0]+=1;
                switch (a->fat)
                {
                case -1:
                    a->fat = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->fat = 1;
                    break;
                case  1:
                    a=Caso1(a,ok, qtdComparacoes);
                    break;
                }
            }
        }
        else
        {
            qtdComparacoes[0]+=2;
            a->dir = insereAVL(a->dir,x,ok, qtdComparacoes);
            if (*ok)
            {
                qtdComparacoes[0]+=1;
                switch (a->fat)
                {
                case  1:
                    a->fat = 0;
                    *ok = 0;
                    break;
                case  0:
                    a->fat = -1;
                    break;
                case -1:
                    a = Caso2(a,ok, qtdComparacoes);
                    break;
                }
            }
        }
    }

    return a;
}

/* Objetivo: realiza uma rotação simples à direita
             como a função não realiza comparações, não é necessário atualizar o ponteiro com a qtd. de comparações

   Entrada:
   @parâmetro *pt := ponteiro para a raíz da árvore

   Saída: árvore rotacionada */

pAVL* rot_simples_dir (pAVL *pt)
{
    pAVL* ptu;
    ptu= pt->esq;
    pt->esq= ptu->dir;
    ptu->dir= pt;
    pt->fat=0;
    pt=ptu;
    return pt;
}

/* Objetivo: realiza uma rotação simples à esquerda
             como a função não realiza comparações, não é necessário atualizar o ponteiro com a qtd. de comparações

   Entrada:
   @parâmetro *pt := ponteiro para a raíz da árvore

   Saída: árvore rotacionada */

pAVL* rot_simples_esq (pAVL *pt)
{
    pAVL* ptu;
    ptu = pt->dir;
    pt->dir= ptu->esq;
    ptu->esq= pt;
    pt->fat=0;
    pt = ptu;
    return pt;
}

/* Objetivo: realiza uma rotação dupla à direita

   Entradas:
   @parâmetro *pt := ponteiro para a raíz da árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore rotacionada */

pAVL* rot_dupla_dir (pAVL *pt, long int qtdComparacoes[])
{
    pAVL *ptu,*ptv;
    ptu= pt->esq;
    ptv= ptu->dir;
    ptu->dir= ptv->esq;
    ptv->esq= ptu;
    pt->esq= ptv->dir;
    ptv->dir= pt;

    qtdComparacoes[0] += 1;
    if(ptv->fat == 1)
        pt->fat= -1;
    else{
        qtdComparacoes[0] += 1;
        pt->fat=0;
    }

    qtdComparacoes[0] += 1;
    if(ptv->fat == -1)
        ptu->fat= 1;
    else{
        qtdComparacoes[0] += 1;
        ptu->fat=0;
    }

    pt=ptv;

    return pt;
}


/* Objetivo: realiza uma rotação dupla à esquerda

   Entradas:
   @parâmetro *pt := ponteiro para a raíz da árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore rotacionada */

pAVL* rot_dupla_esq (pAVL *pt, long int qtdComparacoes[])
{
    pAVL *ptu,*ptv;
    ptu= pt->dir;
    ptv= ptu->esq;
    ptu->esq= ptv->dir;
    ptv->dir= ptu;
    pt->dir= ptv->esq;
    ptv->esq= pt;

    qtdComparacoes[0] += 1;
    if(ptv->fat == -1)
        pt->fat= 1;
    else{
        qtdComparacoes[0] += 1;
        pt->fat=0;
    }

    qtdComparacoes[0] += 1;
    if(ptv->fat == 1)
        ptu->fat= -1;
    else{
        qtdComparacoes[0] += 1;
        ptu->fat=0;
    }

    pt=ptv;

    return pt;
}

/* Objetivo: a partir do cálculo do fator, decide se a rotação será dupla ou simples à esquerda

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro *ok := ponteiro que indica se há necessidade de fazer rotações
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore balanceada */

pAVL* Caso1(pAVL *a, int *ok, long int qtdComparacoes[])
{
    int fat_sube=0;

    fat_sube = Calc_fator(a->esq, qtdComparacoes);

    qtdComparacoes[0] += 1;
    if(fat_sube==1)
        a=rot_simples_dir(a);
    else{
        qtdComparacoes[0] += 1;
        a=rot_dupla_dir(a, qtdComparacoes);
    }

    a->fat=0;
    *ok = 0;
    return a;
}

/* Objetivo: a partir do cálculo do fator, decide se a rotação será dupla ou simples à direita

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro *ok := ponteiro que indica se há necessidade de fazer rotações
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: árvore balanceada */

pAVL* Caso2(pAVL *a,int *ok, long int qtdComparacoes[])
{
    int fat_subd=0;

    fat_subd= Calc_fator(a->dir, qtdComparacoes);

    qtdComparacoes[0] += 1;
    if(fat_subd==-1)
        a=rot_simples_esq(a);
    else{
        qtdComparacoes[0] += 1;
        a=rot_dupla_esq(a, qtdComparacoes);
    }

    a->fat=0;
    *ok = 0;
    return a;
}


/* Objetivo: calcular a altura de uma árvore

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: altura da árvore */

int Altura (pAVL *a, long int qtdComparacoes[])
{
     int Alt_Esq, Alt_Dir;

     qtdComparacoes[0] += 1;
     if (a == NULL)
        return 0;
     else
     {
         qtdComparacoes[0] += 1;
         Alt_Esq = Altura (a->esq, qtdComparacoes);
         Alt_Dir = Altura (a->dir, qtdComparacoes);

         qtdComparacoes[0] += 1;
         if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
         else{
            qtdComparacoes[0] += 1;
            return (1 + Alt_Dir);
         }
     }
}

/* Objetivo: calcular o fator de uma árvore ou sub-árvore

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore ou sub-árvore
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: fator do nodo raíz da árvore ou sub-árvore */

int Calc_fator(pAVL *a, long int qtdComparacoes[])
{
    return (Altura(a->esq, qtdComparacoes) - Altura(a->dir, qtdComparacoes));
}

/* Objetivo: consultar um valor em uma AVL

   Entradas:
   @parâmetro *a := ponteiro para a raíz da árvore
   @parâmetro chave := valor a ser consultado
   @parâmetro qtdComparacoes[] := ponteiro que irá armazenar a quantidade de comparações feita na função

   Saída: sub-árvore contendo o nodo encontrado como raíz, ou "NULL" se não for encontrado na AVL */


pAVL* consultaAVL(pAVL *a,TipoInfo chave, long int qtdComparacoes[])
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
                return consultaAVL(a->esq,chave,qtdComparacoes);
            }
            else if (a->info < chave)
            {
                qtdComparacoes[0]+=1;
                return consultaAVL(a->dir,chave,qtdComparacoes);
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

/* Objetivo: liberar a memória alocada pela criação de uma AVL

   Entrada:
   @parâmetro *a := ponteiro para a raíz da árvore

   Saída: "NULL", indicando árvore vazia */


pAVL* liberaAVL (pAVL *a){
    if (a!=NULL)
    {
        liberaAVL(a->esq); /* exclui nodos a esquerda */
        liberaAVL(a->dir); /* exclui nodos a direita */
        free(a); /* libera raiz */
    }

 return NULL;
}

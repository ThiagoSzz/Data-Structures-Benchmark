/* Bibliotecas e arquivos */

#include <stdio.h>
#include <stdlib.h>

#include "desempenho_AVL.h"

/* Fun��es */

/* Objetivo: inserir nodos em uma AVL

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro x := informa��o a ser inserida na AVL
   @par�metro *ok := ponteiro que indica se h� necessidade de fazer rota��es
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore com o nodo inserido */

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

/* Objetivo: realiza uma rota��o simples � direita
             como a fun��o n�o realiza compara��es, n�o � necess�rio atualizar o ponteiro com a qtd. de compara��es

   Entrada:
   @par�metro *pt := ponteiro para a ra�z da �rvore

   Sa�da: �rvore rotacionada */

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

/* Objetivo: realiza uma rota��o simples � esquerda
             como a fun��o n�o realiza compara��es, n�o � necess�rio atualizar o ponteiro com a qtd. de compara��es

   Entrada:
   @par�metro *pt := ponteiro para a ra�z da �rvore

   Sa�da: �rvore rotacionada */

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

/* Objetivo: realiza uma rota��o dupla � direita

   Entradas:
   @par�metro *pt := ponteiro para a ra�z da �rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore rotacionada */

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


/* Objetivo: realiza uma rota��o dupla � esquerda

   Entradas:
   @par�metro *pt := ponteiro para a ra�z da �rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore rotacionada */

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

/* Objetivo: a partir do c�lculo do fator, decide se a rota��o ser� dupla ou simples � esquerda

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro *ok := ponteiro que indica se h� necessidade de fazer rota��es
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore balanceada */

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

/* Objetivo: a partir do c�lculo do fator, decide se a rota��o ser� dupla ou simples � direita

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro *ok := ponteiro que indica se h� necessidade de fazer rota��es
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: �rvore balanceada */

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


/* Objetivo: calcular a altura de uma �rvore

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: altura da �rvore */

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

/* Objetivo: calcular o fator de uma �rvore ou sub-�rvore

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore ou sub-�rvore
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: fator do nodo ra�z da �rvore ou sub-�rvore */

int Calc_fator(pAVL *a, long int qtdComparacoes[])
{
    return (Altura(a->esq, qtdComparacoes) - Altura(a->dir, qtdComparacoes));
}

/* Objetivo: consultar um valor em uma AVL

   Entradas:
   @par�metro *a := ponteiro para a ra�z da �rvore
   @par�metro chave := valor a ser consultado
   @par�metro qtdComparacoes[] := ponteiro que ir� armazenar a quantidade de compara��es feita na fun��o

   Sa�da: sub-�rvore contendo o nodo encontrado como ra�z, ou "NULL" se n�o for encontrado na AVL */


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

/* Objetivo: liberar a mem�ria alocada pela cria��o de uma AVL

   Entrada:
   @par�metro *a := ponteiro para a ra�z da �rvore

   Sa�da: "NULL", indicando �rvore vazia */


pAVL* liberaAVL (pAVL *a){
    if (a!=NULL)
    {
        liberaAVL(a->esq); /* exclui nodos a esquerda */
        liberaAVL(a->dir); /* exclui nodos a direita */
        free(a); /* libera raiz */
    }

 return NULL;
}

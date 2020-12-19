/* Estruturas */

typedef int TipoInfo;

struct NodoA
{
    TipoInfo info;
    int fat;
    struct NodoA * esq;
    struct NodoA * dir;
}; typedef struct NodoA pAVL;

/* Funções */

pAVL* insereAVL (pAVL *a, TipoInfo x, int *ok, long int qtdComparacoes[]);
int Altura (pAVL *a, long int qtdComparacoes[]);
int Calc_fator (pAVL *a, long int qtdComparacoes[]);
pAVL* Caso1(pAVL* a,int *ok, long int qtdComparacoes[]);
pAVL* Caso2(pAVL* a,int *ok, long int qtdComparacoes[]);
pAVL* rot_simples_esq (pAVL* pt);
pAVL* rot_simples_dir (pAVL* pt);
pAVL* rot_dupla_esq (pAVL* pt, long int qtdComparacoes[]);
pAVL* rot_dupla_dir (pAVL* pt, long int qtdComparacoes[]);
pAVL* consultaAVL(pAVL *a,TipoInfo chave, long int qtdComparacoes[]);
pAVL* liberaAVL (pAVL* a);


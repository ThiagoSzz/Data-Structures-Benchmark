/* Estruturas */

typedef int tipoinfo;

struct TNodoA{
        tipoinfo info;
        struct TNodoA *esq;
        struct TNodoA *dir;
};

typedef struct TNodoA pNodoA;

/* Esqueleto das funções */

pNodoA* insereABP(pNodoA *a, tipoinfo ch, long int qtdComparacoes[]);
pNodoA* consultaABP(pNodoA *a, tipoinfo chave, long int qtdComparacoes[]);
pNodoA* liberaABP (pNodoA* a);


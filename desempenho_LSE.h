/* Estruturas */

typedef struct tipoNo ptLSE;

struct tipoNo
{
    int numero;
    ptLSE *prox;
};

/* Esqueleto das fun��es */

ptLSE *criaLista (void);
ptLSE* consultaLista (ptLSE* ptLista, int num, long int qtdComparacoes[]);
ptLSE* destroiLista(ptLSE* ptLista);
ptLSE* insereInicio(ptLSE *ptLista, int num);


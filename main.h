#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct data
{
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct jogador
{
    char*nome;
    char*clube;
    char*estado;
    int index;
} JOGADOR;

typedef struct lista
{
    char*op;
    int index;
    float valor;
    DATA data;
    struct lista*pprev;
    struct lista*pnext;
} LISTA;

typedef struct fundo
{
    float mealheiro;
    int plantel_atual;
    int plantel_ativo;
    int plantel_total;
    int qtd_op;
    JOGADOR*pstart;
    LISTA*pfirst;
    LISTA*plast;
} FUNDO;

void init_fundo(FUNDO*pf,int nJOGADOR);
void menu(FUNDO*pf);


void gerenciador_entradas(FUNDO*f, DATA data);

    char** expande_malloc_char(char**principal, int qtd);
    void entra(FUNDO*f,JOGADOR*pj,DATA data,int n);
    void nova_operacao(FUNDO *f, float valor, DATA data, char*id,int i);
    void duplica_tam_JOGADOR(FUNDO*f);

void gerenciador_saidas(FUNDO*f, DATA data);
    void saida(FUNDO*pf,char*nome,DATA data,float valor);
    int retorna_index_ativo(FUNDO*f, char*nome);

void recolhe_paga(FUNDO*f, float valor,DATA data,char*op);


void pesquisa(FUNDO*f,char op);
    JOGADOR* pesquisa_nome(FUNDO*f,char*nome,JOGADOR *paux,int *i,char op);
void pesquisa_jogador(FUNDO*f, char op);


DATA data_op();








#endif // MAIN_H_INCLUDED

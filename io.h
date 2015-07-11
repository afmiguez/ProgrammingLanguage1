#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED


void imprime_txt(JOGADOR *pj, char* op,int valor,DATA data);
void imprime_bin(JOGADOR *pj, char* op,int valor,DATA data);
void imprime_jogadores(FUNDO*f);
void imprime_operacoes(FUNDO*f);
void imprime_pesquisa(FUNDO*f,char*op);
void load_entrada_saida(FUNDO*pf,FILE*fp,DATA data, int val,char*op);
void load_txt(FUNDO*pf,char*file);
void save_txt(int qtd_op,char*file);
void save_bin(int qtd_op,char*file);
void load_bin(FUNDO*pf,char*file);
void load_entrada_saida_bin(FUNDO*pf,FILE*fp,DATA data, int val,char*op);


#endif // IO_H_INCLUDED

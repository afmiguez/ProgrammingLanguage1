#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

int checa_str(JOGADOR*pj, int lo, int pos);
void exch(JOGADOR*pj, int i, int j);
void insert_string(JOGADOR*pj, int pos);
int menor_string(char str1[], char str2[]);
void swapdlnodes(FUNDO* f, LISTA* node1, LISTA* node2);
void selection_sort(FUNDO *f, char *tipo, char *ordem);

void mergesort(JOGADOR v[], int n,char ordem[]);
void merger_recursive(JOGADOR v[],JOGADOR aux[], int lo, int hi,char ordem[]);
void merger(JOGADOR v[],JOGADOR aux[], int lo, int mid, int hi,char ordem[]);

#endif // SORT_H_INCLUDED

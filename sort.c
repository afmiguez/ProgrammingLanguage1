#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "main.h"
#include "io.h"
#include "sort.h"

#define MAX 256

void insert_string(JOGADOR*pj, int pos)
{
    int i=pos,k=0;
    for(i=pos; i>0; i--)
    {
        k=0;
        while(k<i)
        {
            if(checa_str(pj,k,i)==0&&i>k)
            {
                exch(pj,k,i);
            }
            k++;
        }
    }
}

int checa_str(JOGADOR*pj, int i, int j)
{
    char str1[MAX]="", str2[MAX]="";
    strcpy(str1,(pj+i)->nome);
    strcpy(str2,(pj+j)->nome);
    return menor_string(str1,str2);
}

int menor_string(char str1[], char str2[])
{
    int d=0;
    if(str1==NULL)
    {
        return 0;
    }
    if (str2==NULL)
    {
        return 1;
    }
    while(d<strlen(str1))
    {
        if(str1[d]<str2[d])
        {
            return 1;
        }
        else if(str1[d]==str2[d])
        {
            d++;
        }
        else
        {
            break;
        }
    }
    if(d==strlen(str1))
    {
        return 1;
    }
    return 0;
}

int menor_data(LISTA op1,LISTA op2)
{
    if(op1.data.ano<op2.data.ano)
    {
        return 0;
    }
    if(op2.data.ano<op1.data.ano)
    {
        return 1;
    }
    if(op1.data.ano==op2.data.ano)
    {
        if(op1.data.mes<op2.data.mes)
        {
            return 0;
        }
        if (op2.data.mes<op1.data.mes)
        {
            return 1;
        }
        if(op1.data.mes==op2.data.mes)
        {
            if(op1.data.dia<=op2.data.dia)
            {
                return 0;
            }
            if(op2.data.ano<op1.data.dia)
            {
                return 1;
            }
        }
    }
    return 0;
}

void exch(JOGADOR*pj, int i, int j)
{
    char *t=(pj+i)->nome;
    (pj+i)->nome=(pj+j)->nome;
    (pj+j)->nome=t;

    t=(pj+i)->clube;
    (pj+i)->clube=(pj+j)->clube;
    (pj+j)->clube=t;
}

void swapdlnodes(FUNDO* f, LISTA* node1, LISTA* node2)
{
    LISTA* aux=NULL;
    //printf("(lista=%d,n1=%d,n2=%d)",lista->item,node1->item,node2->item); //debug info

    if (node2->pnext == node1)
    {
        //return swapdlnodes(lista,node2,node1); //outra alternativa
        aux = node1;
        node1 = node2;
        node2 = aux;
    }

    // actualiza cabeça da lista
    if (f->pfirst == node1)
    {
        f->pfirst = node2;
    }
    else if (f->pfirst == node2)
    {
        f->pfirst = node1;
    }

    if (f->plast == node1)
    {
        f->plast = node2;
    }
    else if (f->plast == node2)
    {
        f->plast = node1;
    }
    // considera dois casos: nos contiguos ou não
    if (node1->pnext == node2)
    {
        node1->pnext = node2->pnext;
        node2->pnext = node1;
        if (node1->pprev != NULL)
        {
            node1->pprev->pnext = node2;
        }
        node2->pprev = node1->pprev;
        node1->pprev = node2;
        if (node1->pnext != NULL)
        {
            node1->pnext->pprev = node1;
        }
    }
    else
    {
        if (node1->pprev != NULL)
        {
            node1->pprev->pnext = node2;
        }
        if (node2->pprev != NULL)
        {
            node2->pprev->pnext = node1;
        }
        aux = node1->pnext;
        node1->pnext = node2->pnext;
        node2->pnext = aux;
        if (node1->pnext != NULL)
        {
            node1->pnext->pprev = node1;
        }
        if (node2->pnext != NULL)
        {
            node2->pnext->pprev = node2;
        }
        aux = node1->pprev;
        node1->pprev = node2->pprev;
        node2->pprev = aux;
    }
}

void selection_sort(FUNDO *f, char *criterio, char *ordem)
{
    LISTA *paux1, *paux2, *paux3=NULL;
    for (paux1=f->pfirst; paux1->pnext!=0; paux1=paux1->pnext)
    {
        paux2=paux1;
        for(paux3=paux1->pnext; paux3!=0; paux3=paux3->pnext)
        {
            if(strcmp(criterio,"data")==0)
            {
                if(strcmp(ordem, "crescente")==0)
                {
                    if(menor_data(*paux3, *paux2)==0)
                    {
                        paux2=paux3;
                    }
                }
                else //para implementar a ordem decrescente
                {
                    if(menor_data(*paux3,*paux2)==1)
                    {
                        //paux3=paux2;
                        paux2=paux3;
                    }
                }
            }
            else
            {
                if(strcmp(ordem, "crescente")==0)
                {
                    if(paux3->valor<paux2->valor)
                    {
                        paux2=paux3;
                    }

                }
                else //para implementar a ordem decrescente
                {
                    if(paux2->valor<paux3->valor)
                    {
                        //paux3=paux2;
                        paux2=paux3;
                    }

                }
            }
        }
        swapdlnodes(f,paux1,paux2);
        paux1=paux2;
    }
}

void mergesort(JOGADOR v[], int n,char ordem[])
{
    JOGADOR*aux=(JOGADOR*)malloc(sizeof(JOGADOR)*n);
    merger_recursive(v,aux,0,n-1,ordem);
    free(aux);
}

void merger_recursive(JOGADOR v[],JOGADOR aux[], int lo, int hi,char ordem[])
{
    if(hi<=lo)
    {
        return;
    }
    int mid=(lo+hi)/2;
    merger_recursive(v,aux,lo,mid,ordem);
    merger_recursive(v,aux,mid+1,hi,ordem);
    merger(v,aux,lo,mid,hi,ordem);

}
void merger(JOGADOR v[],JOGADOR aux[], int lo, int mid, int hi,char ordem[])
{
    int i=lo,k=0,j=mid+1;
    for(k=lo;k<=hi; k++)
    {
        aux[k]=v[k];
    }
    for(k=lo;k<=hi;k++)
    {
        if(i>mid)
        {
            v[k]=aux[j++];
        }
        else if (j>hi)
        {
            v[k]=aux[i++];
        }
        //else if(aux[i]<aux[j])
        else if(strcmp(ordem,"crescente")==0)
        {
            if(menor_string((aux+i)->nome,(aux+j)->nome)==0)
            {
                v[k]=aux[i++];
            }

        }
        else if(strcmp(ordem,"crescente")==0)
        {
            if(menor_string((aux+j)->nome,(aux+i)->nome)==0)
            {
                v[k]=aux[i++];
            }
        }
        else
        {
            v[k]=aux[j++];
        }
    }
}


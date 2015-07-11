#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "main.h"
#include "io.h"
#include "sort.h"

#define MAX 256

/**                    imprime_txt()                                */
/** função que guarda em tempo real de execução as operações        */
/** realizadas pelo fundo. O formato "a" garante que sempre será    */
/** aberto e as novas operações sempre estarão após às antigas.     */
/** Como forma de garantir a consistência do ficheiro saldo.txt,    */
/** a cada fim de ele é aberto com o modo "w" para realizar a       */
/** limpeza de todos os dados                                       */

void imprime_txt(JOGADOR *pj, char* op,int valor,DATA data)
{
    FILE *fp=NULL;
    int i =0;
    if((fp=fopen("saldo.txt","a"))==NULL)
    {
        fprintf(stdout,"\nimprime_txt():erro abrir ficheiro \"saldo.txt\"");
        return;
    }

    if(strcmp(op,"ENTRAM")==0) //imprime ENTRAM
    {
       fprintf(fp, "\nENTRAM %d %d/%d/%d", valor,data.dia,data.mes,data.ano);
        for (i=0; i<valor; i++)
        {
            fprintf(fp,"\n%s, %s", (pj+i)->nome,(pj+i)->clube);
        }
    }
    else if(strcmp(op,"SAEM")==0) //imprime SAEM
    {
        if(valor>0)
        {
            fprintf(fp,"\nSAEM %d %d/%d/%d",valor,data.dia,data.mes,data.ano);
            for (i=0; i<valor; i++)
            {
                fprintf(fp,"\n%s, %s", (pj+i)->nome,(pj+i)->clube);
            }
        }
    }
    else if(strcmp(op,"RECOLHE")==0) //imprime RECOLHE
    {
        fprintf(fp,"\nRECOLHE %d %d/%d/%d", valor,data.dia,data.mes,data.ano);
    }
    else if(strcmp(op,"PAGA")==0) //imprime PAGA
    {
        fprintf(fp,"\nPAGA %d %d/%d/%d", valor,data.dia,data.mes,data.ano);
    }
    fclose(fp);
}


void imprime_bin(JOGADOR *pj, char* op,int valor,DATA data)
{
    FILE *fp=NULL;
    int i =0,size1=0,size2=0,sep='/';
    if((fp=fopen("saldo.bin","ab"))==NULL)
    {
        fprintf(stdout,"\nimprime_bin():erro abrir ficheiro \"saldo.bin\"");
        return;
    }
    if((strcmp(op,"ENTRAM")==0)||(strcmp(op,"SAEM")==0)) //escreve operação ENTRAM/SAEM
    {
	   size1=strlen(op)+1; //prepara escrita da string op
	   fwrite(&size1,sizeof(int),1,fp); //escreve tamanho da string op
	   fwrite(op,sizeof(char),size1,fp); //escreve string op

	   //fseek(fp,1,SEEK_CUR);

	   fwrite(&valor,sizeof(int),1,fp); //escreve conteudo de valor

	   //fseek(fp,1,SEEK_CUR);

	   fwrite(&data.dia,sizeof(int),1,fp); //escreve conteudo de data.dia

	   //fseek(fp,1,SEEK_CUR);

	   fwrite(&data.mes,sizeof(int),1,fp); //escreve conteudo de data.dia

	   //fseek(fp,1,SEEK_CUR);

	   fwrite(&data.ano,sizeof(int),1,fp); //escreve conteudo de data.dia

        for (i=0; i<valor; i++) //escreve nomes de atletas e seus clubes
        {
			size1=strlen((pj+i)->nome)+1;
			size2=strlen((pj+i)->clube)+1;
			fwrite(&size1,sizeof(int),1,fp);
			fwrite((pj+i)->nome,sizeof(char),size1,fp);
			fwrite(&size2,sizeof(int),1,fp);
			fwrite((pj+i)->clube,sizeof(char),size2,fp);
        }
    }
    else if((strcmp(op,"RECOLHE")==0)||(strcmp(op,"PAGA")==0)) //escreve operação RECOLHE/PAGA
    {
		size1=strlen(op)+1;
		fwrite(&size1,sizeof(int),1,fp);
		fwrite(op,sizeof(char),size1,fp);
		fwrite(&valor,sizeof(int),1,fp);
		fwrite(&data.dia,sizeof(int),1,fp);
        //fwrite(&sep,sizeof(char),1,fp);
        fwrite(&data.mes,sizeof(int),1,fp);
        //fwrite(&sep,sizeof(char),1,fp);
        fwrite(&data.ano,sizeof(int),1,fp);
    }
    fclose(fp);
}

void imprime_jogadores(FUNDO*f)
{
    FILE *fp=NULL;
    int i=0;
    fp=fopen("JOGADOR.txt", "w");
    for (i=0; i<f->plantel_atual; i++)
    {
        fprintf(fp, "nome: %s ", (f->pstart+i)->nome);
        fprintf(fp, "clube: %s ", (f->pstart+i)->clube);
        fprintf(fp, "estado: %s ", (f->pstart+i)->estado);
        fprintf(fp, "indice: %d\n", (f->pstart+i)->index);
    }
    fclose(fp);
}

void imprime_operacoes(FUNDO*f)
{
    FILE *fp=NULL;
    LISTA*paux=f->pfirst;
    if((fp=fopen("operacoes.txt","a"))==NULL)
    {
        fprintf(stdout,"imprime_operacoes():erro abrir ficheiro \"operacoes.txt\"\n");
        return;
    }
    while(paux!=NULL)
    {
        fprintf(fp, "operação: %s ", paux->op);
        fprintf(fp, "data: %d/%d/%d ", paux->data.dia,paux->data.mes,paux->data.ano);
        fprintf(fp, "jogador: %s ", (f->pstart+(paux->index))->nome);
        fprintf(fp, "valor: %f\n", paux->valor);

        paux=paux->pnext;
    }
    fprintf(fp, "\n");
    fclose(fp);
}

void imprime_pesquisa(FUNDO*f,char*op)
{
    LISTA*paux=f->pfirst;
    FILE *fp=NULL;
    if((fp=fopen("pesquisa.txt","w"))==NULL)
    {
        fprintf(stdout,"imprime_pesquisa():erro abrir ficheiro \"pesquisa.txt\"\n");
        return;
    }
    if(strcmp(op,"jogador")==0)
    {
        while(paux!=NULL)
        {
            if(strstr(paux->op,"ENTRAM")!=NULL||strstr(paux->op,"SAEM")!=NULL)
            {
                fprintf(fp, "operação: %s ", paux->op);
                fprintf(fp, "data: %d/%d/%d ", paux->data.dia,paux->data.mes,paux->data.ano);
                fprintf(fp, "jogador: %s ", (f->pstart+(paux->index))->nome);
                fprintf(fp, "valor: %f\n", paux->valor);
            }
            paux=paux->pnext;
        }
        fprintf(fp,"\n");
    }
    else
    {
        while(paux!=NULL)
        {
            if(strstr(paux->op,"RECOLHE")!=NULL||strstr(paux->op,"PAGA")!=NULL)
            {
                fprintf(fp, "operação: %s ", paux->op);
                fprintf(fp, "data: %d/%d/%d ", paux->data.dia,paux->data.mes,paux->data.ano);
                fprintf(fp, "jogador: %s ", (f->pstart+(paux->index))->nome);
                fprintf(fp, "valor: %f\n", paux->valor);
            }

            paux=paux->pnext;
        }
        fprintf(fp,"\n");
    }
}

void load_txt(FUNDO*pf,char*file)
{
    FILE *fp=0;
    DATA data;
    int qtd_op=0,i=0,val=0;
    char op[MAX]="";


    if((fp=fopen(file,"r"))==NULL)
    {
        fprintf(stdout,"load_txt():erro abrir ficheiro %s\n",file);
        return;
    }
    fscanf(fp, "%d", &qtd_op);
    for(i=0;i<qtd_op;i++)
    {
        fscanf(fp, "%s %d %d/%d/%d\n", op,&val,&data.dia,&data.mes,&data.ano);

        if(strcmp(op,"ENTRAM")==0||strcmp(op,"SAEM")==0)
        {
            if(val>200)
            {
                printf("Valor de entrada/saída de JOGADOR acima do permitido\n");
                return;
            }
            load_entrada_saida(pf,fp,data,val,op);
            pf->qtd_op++;
        }
        else if(strcmp(op,"RECOLHE")==0)
        {
            if(val>200)
            {
                printf("Valor de recolha de dinheiro acima do permitido\n");
                return;
            }
            recolhe_paga(pf,val,data,op);
            pf->qtd_op++;
        }
        else if(strcmp(op,"PAGA")==0)
        {
            if(val>2000)
            {
                printf("Valor de pagamento acima do permitido\n");
                return;
            }
            recolhe_paga(pf,val,data,op);
            pf->qtd_op++;
        }
    }
    fclose(fp);
}

void load_entrada_saida(FUNDO*pf,FILE*fp,DATA data, int val,char*op)
{
    int j=0;
    float valor=0;
    char str1[MAX]="", str2[MAX]="";
    JOGADOR *paux=(JOGADOR*)malloc(sizeof(JOGADOR)*val);



    for(j=0;j<val;j++)
    {
            fscanf(fp,"%[^,] , %[^\n]\n",str1,str2); //o formato %[^,] faz com que a string seja lida até que apareça a vírgula. O formato %[^\n] faz o mesmo até que apareça o new line

            (paux+j)->nome=(char*)malloc(strlen(str1)+1);
            strcpy((paux+j)->nome,str1);


            (paux+j)->clube=(char*)malloc(strlen(str2)+1);
            strcpy((paux+j)->clube,str2);

    }
    if(strcmp(op,"ENTRAM")==0)
    {
        insert_string(paux,val-1);  //FUNÇÃO QUE ORDENA O BLOCO DE JOGADOR A SER INSERIDO NA ESTRUTURA

        pf->plantel_ativo+=val;
        entra(pf,paux,data,val);     //REALIZA A INCLUSÃO DOS NOVOS JOGADOR NA ESTRUTURA DEFINITIVA

        imprime_txt(paux,"ENTRAM",val,data);    //IMPRIME EM TXT O RESUMO DA OPERAÇÃO REALIZADA
        imprime_bin(paux,"ENTRAM",val,data);
    }
    else if(strcmp(op,"SAEM")==0)
    {
        valor=pf->mealheiro/pf->plantel_ativo;
        for(j=0;j<val;j++)
        {
            saida(pf,(paux+j)->nome,data,valor);
        }
        pf->plantel_ativo-=val;
        imprime_txt(paux,"SAEM",val,data);
        imprime_bin(paux,"SAEM",val,data);
    }
}

void save_txt(int qtd_op,char*file)
{
    FILE*fp1=NULL,*fp2=NULL;
    char ch;
    if((fp1=fopen("saldo.txt","r"))==NULL)
    {
        fprintf(stdout,"\nsave_txt():erro abrir ficheiro \"saldo.txt\"");
        return;
    }
    if((fp2=fopen(file,"w"))==NULL)
    {
        fprintf(stdout,"\nsave_txt():erro abrir ficheiro %s",file);
        return;
    }
    fprintf(fp2,"%d",qtd_op);
    while(1)
    {
       ch = fgetc(fp1);

       if(ch==EOF)
          break;
       else
          putc(ch,fp2);
    }
    fprintf(fp2,"\n%d",0);
    fclose(fp1);
    fclose(fp2);
}

void save_bin(int qtd_op,char*file)
{
    FILE*fp1=NULL,*fp2=NULL;
    int i=0;
    if((fp1=fopen("saldo.bin","rb"))==NULL)
    {
        fprintf(stdout,"\nsave_bin():erro abrir ficheiro \"saldo.bin\"");
        return;
    }
    if((fp2=fopen(file,"wb"))==NULL)
    {
        fprintf(stdout,"\nsave_bin:erro abrir ficheiro %s",file);
        return;
    }
	fwrite(&qtd_op,sizeof(int),1,fp2);
    while(1)
    {
       i  =  fgetc(fp1);

			if(!feof(fp1))
				fputc(i, fp2);
			else
				break;
    }
    i=0;
	fwrite(&i,sizeof(int),1,fp2);
    fclose(fp1);
    fclose(fp2);
}

void load_bin(FUNDO*pf,char*file)
{
    FILE *fp=0;
    DATA data;
    int qtd_op=0,i=0,val=0,n=0,size1=0;
    char *op=NULL, sep='/';


    if((fp=fopen(file,"rb"))==NULL)
    {
        fprintf(stdout,"load_bin():erro abrir ficheiro %s\n",file);
        return;
    }
    //fscanf(fp, "%d", &qtd_op);
	n=fread(&qtd_op,sizeof(int),1,fp);
	if(n!=1)
	{
		printf("load_bin():ocorreu erro ao ler qtd_op\n");
		return;
	}

    for(i=0;i<qtd_op;i++)
    {
        //fscanf(fp, "%s %d %d/%d/%d\n", op,&val,&data.dia,&data.mes,&data.ano);
		n=fread(&size1,sizeof(int),1,fp);
		if(n==1)
		{
			op=(char*)malloc(sizeof(char)*size1+1);
		}
		else
		{
			printf("load_bin():ocorreu erro ao tentar ler o tamanho da string op\n");
			return;
		}
		n=fread(op,sizeof(char)*size1,size1,fp);
		if(n!=size1)
		{
			printf("load_bin():ocorreu erro ao tentar copiar o conteudo da string op\n");
			return;
		}
		n=fread(&val,sizeof(int),1,fp);
		if(n!=1)
		{
			printf("load_bin():ocorreu erro ao tentar copiar o conteudo de \"valor\"\n");
			return;
		}
		n=fread(&data.dia,sizeof(int),1,fp);
		if(n!=1)
		{
			printf("load_bin():ocorreu erro ao tentar copiar o conteudo de \"data.dia\"\n");
			return;
		}
		//n=fread(&sep,sizeof(char),1,fp); //avançar o stream
		n=fread(&data.mes,sizeof(int),1,fp);
		if(n!=1)
		{
			printf("load_bin():ocorreu erro ao tentar copiar o conteudo de \"data.mes\"\n");
			return;
		}
		//n=fread(&sep,sizeof(char),1,fp); //avançar o stream
		n=fread(&data.ano,sizeof(int),1,fp);
		if(n!=1)
		{
			printf("load_bin():ocorreu erro ao tentar copiar o conteudo de \"data.ano\"\n");
			return;
		}

        if(strcmp(op,"ENTRAM")==0||strcmp(op,"SAEM")==0)
        {
            if(val>200)
            {
                printf("Valor de entrada/saída de JOGADOR acima do permitido\n");
                return;
            }
            load_entrada_saida_bin(pf,fp,data,val,op);
            pf->qtd_op++;
        }
        else if(strcmp(op,"RECOLHE")==0)
        {
            if(val>200)
            {
                printf("Valor de recolha de dinheiro acima do permitido\n");
                return;
            }
            recolhe_paga(pf,val,data,op);
            pf->qtd_op++;
        }
        else if(strcmp(op,"PAGA")==0)
        {
            if(val>2000)
            {
                printf("Valor de pagamento acima do permitido\n");
                return;
            }
            recolhe_paga(pf,val,data,op);
            pf->qtd_op++;
        }
    }
    fclose(fp);
}

void load_entrada_saida_bin(FUNDO*pf,FILE*fp,DATA data, int val,char*op)
{
    int j=0,size1=0,size2=0,n=0;
    float valor=0;
    JOGADOR *paux=(JOGADOR*)malloc(sizeof(JOGADOR)*val);

    for(j=0;j<val;j++)
    {
            //fscanf(fp,"%[^,] , %[^\n]\n",str1,str2); //o formato %[^,] faz com que a string seja lida até que apareça a vírgula. O formato %[^\n] faz o mesmo até que apareça o new line
			n=fread(&size1,sizeof(int),1,fp);
			if(n==1)
			{
				(paux+j)->nome=(char*)malloc(size1);
			}
			else
			{
				printf("load_entrada_saida_bin():ocorreu erro ao tentar copiar o tamanho do nome do jogador\n");
				return;
			}
			n=fread((paux+j)->nome,sizeof(char)*size1,size1,fp);
			if(n!=size1)
			{
				printf("load_entrada_saida_bin():ocorreu erro ao tentar copiar o nome do jogador\n");
				return;
			}
			n=fread(&size2,sizeof(int),1,fp);
			if(n==1)
			{
				(paux+j)->clube=(char*)malloc(size2);
			}
			else
			{
				printf("load_entrada_saida_bin():ocorreu erro ao tentar copiar o tamanho do nome do clube\n");
				return;
			}
			n=fread((paux+j)->clube,sizeof(char)*size2,size2,fp);
			if(n!=size1)
			{
				printf("load_entrada_saida_bin():ocorreu erro ao tentar copiar o nome do jogador\n");
				return;
			}
    }
    if(strcmp(op,"ENTRAM")==0)
    {
        insert_string(paux,val-1);  //FUNÇÃO QUE ORDENA O BLOCO DE JOGADOR A SER INSERIDO NA ESTRUTURA

        pf->plantel_ativo+=val;
        entra(pf,paux,data,val);     //REALIZA A INCLUSÃO DOS NOVOS JOGADOR NA ESTRUTURA DEFINITIVA

        imprime_txt(paux,"ENTRAM",val,data);    //IMPRIME EM TXT O RESUMO DA OPERAÇÃO REALIZADA
        imprime_bin(paux,"ENTRAM",val,data);
    }
    else if(strcmp(op,"SAEM")==0)
    {
        valor=pf->mealheiro/pf->plantel_ativo;
        for(j=0;j<val;j++)
        {
            saida(pf,(paux+j)->nome,data,valor);
        }
        pf->plantel_ativo-=val;
        imprime_txt(paux,"SAEM",val,data);
        imprime_bin(paux,"SAEM",val,data);
    }
}

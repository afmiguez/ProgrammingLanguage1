#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "main.h"
#include "io.h"
#include "sort.h"

#define MAX 256

int main()
{
    FILE *fp=NULL;
    setlocale(LC_ALL, "");
    FUNDO f= {0,0,0,0,0,NULL,NULL,NULL};
    init_fundo(&f,6);
    menu(&f);
    /*load_txt(&f,"carrega2.txt");
    save_bin(7,"abc.bin");
    load_bin(&f,"abc.bin");
    printf("meh");
    fp=fopen("abc.bin","wb");
    fclose(fp);*/

    return 0;
}

DATA data_op()
{
    DATA data= {0,0,0};
    printf("Insira o dia da operação\n");
    scanf("%d",&data.dia);
    printf("Insira o mês da operação\n");
    scanf("%d",&data.mes);
    printf("Insira o ano da operação\n");
    scanf("%d",&data.ano);
    return data;
}

void menu(FUNDO*pf)
{
    char op,ordem[MAX]="",file[MAX]="";
    FILE *fp=NULL;
    float valor=0;
    DATA data= {0,0,0};
    do
    {
        system("cls");
        printf("Selecione uma das opções a seguir:\na)Entrada de jogadores\nb)Saída de jogadores\nc)Recolha de valores\nd)Pagamento\ne)Pesquisa\nf)Escrever jogadores\ng)Ordenar bolsa de jogadores\nh)Carregar Estado\ni)Salvar fundo\ns)Sair\n");
        do
        {
            op=getch();
        }
        while(op!='a'&&op!='A'&&op!='b'&&op!='B'&&op!='c'&&op!='C'&&op!='d'&&op!='D'&&op!='e'&&op!='E'&&op!='f'&&op!='F'&&op!='g'&&op!='G'&&op!='h'&&op!='H'&&op!='i'&&op!='I'&&op!='s'&&op!='S');
        if(op=='a'||op=='A')
        {
            data=data_op();
            gerenciador_entradas(pf,data);
            pf->qtd_op++;
        }
        else if(op=='b'||op=='B')
        {
            data=data_op();
            gerenciador_saidas(pf,data);
            pf->qtd_op++;
        }
        else if(op=='c'||op=='C')
        {
            data=data_op();
            printf("Insira o valor a ser recolhido\n");
            scanf("%f",&valor);
            recolhe_paga(pf,valor,data,"RECOLHE");
            pf->qtd_op++;
        }
        else if(op=='d'||op=='D')
        {
            data=data_op();
            printf("Insira o valor a ser pago\n");
            scanf("%f",&valor);
            recolhe_paga(pf,valor,data,"PAGA");
            pf->qtd_op++;
        }
        else if(op=='e'||op=='E')
        {
            printf("Escolha o critério de pesquisa:\na)Jogador\nb)Operação");
            do
            {
                op=getch();
            }
            while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            pesquisa(pf,op);
            system("pause");

        }
        else if(op=='f'||op=='F')
        {
            imprime_jogadores(pf);
        }
        else if(op=='g'||op=='G')
        {
            printf("Escolha a ordem que deseja:\na)Crescente\nb)Decrescente");
            do
            {
                op=getch();

            }
            while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            if(op=='a'||op=='A')
            {
                strcpy(ordem,"crescente");
            }
            else
            {
                strcpy(ordem,"decrescente");
            }
            mergesort(pf->pstart,pf->plantel_atual,ordem);
        }
        else if(op=='h'||op=='H')
        {
            printf("Deseja carregar ficheiros de teste?(s/n)\n");
            do
            {
                op=getch();
            }
            while(op!='s'&&op!='S'&&op!='n'&&op!='N');

            if(op=='s'||op=='S')
            {
                printf("Escolha qual ficheiro deseja utilizar\na:\nb:\nc:");
                do
                {
                    op=getch();

                }
                while(op!='a'&&op!='A'&&op!='b'&&op!='B'&&op!='c'&&op!='C');

                if(op=='a'||op=='A')
                {
                    strcpy(file,"carrega1.txt");
                }
                else if(op=='b'||op=='B')
                {
                    strcpy(file,"carrega2.txt");
                }
                else if(op=='c'||op=='C')
                {
                    strcpy(file,"carrega3.txt");
                }
            }
            else
            {
                printf("Insira o nome do ficheiro que deseja carregar (sem extensão)\n");
                gets(file);
                strcat(file,".txt");
            }
            load_txt(pf,file);
        }
        else if(op=='i'||op=='I')
        {
            printf("Insira o nome do ficheiro em que deseja guardar as informações do fundo (sem extensão)\n");
            gets(file);
            printf("Escolha o formato em que deseja guardar as informações:\na)texto\nb)binário");
            do
            {
                op=getch();
            }while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            if(op=='a'||op=='A')
            {
                strcat(file,".txt");
                save_txt(pf->qtd_op,file);
            }
            else
            {
                strcat(file,".bin");
                save_bin(pf->qtd_op,file);
            }

        }
        else if(op=='j'||op=='J')
        {
            printf("Insira o nome do ficheiro em que deseja guardar as informações do fundo (sem extensão)\n");
            gets(file);
            strcat(file,".bin");
            save_bin(pf->qtd_op,file);
        }
    }
    while(op!='s'&&op!='S');
    fp=fopen("saldo.txt","w"); //limpa as informações do ficheiro saldo.txt quando acaba o programa
    fclose(fp);
}

void pesquisa(FUNDO*pf, char op)
{
    char tipo[MAX]="",ordem[MAX]="",criterio[MAX]="";
    if(op=='a')
    {
        printf("Escolha o criterio de pesquisa:\na)Nome inteiro\nb)Parte do nome\nc)Clube\nd)Estado\n");
        do
        {
            op=getch();
        }
        while(op!='a'&&op!='A'&&op!='b'&&op!='B'&&op!='c'&&op!='C'&&op!='d'&&op!='D');
        pesquisa_jogador(pf,op);
    }
    else
    {
        printf("Escolha o tipo de operações:\na)Entrada/saída\nb)Recolha/pagamento\n");
        do
        {
            op=getch();
        }
        while(op!='a'&&op!='A'&&op!='b'&&op!='B');
        if(op=='a')
        {
            strcpy(tipo,"jogador");
            strcpy(criterio,"data");
            printf("Escolha a ordem:\na)Crescente\nb)Decrescente");
            do
            {
                op=getch();
            }
            while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            if(op=='a')
            {
                strcpy(ordem,"crescente");
            }
            else
            {
                strcpy(ordem,"decrescente");
            }
        }
        else
        {
            strcpy(tipo,"dinheiro");
            printf("Escolha o tipo:\na)Data\nb)Valor");
            do
            {
                op=getch();
            }
            while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            if(op=='a')
            {
                strcpy(criterio,"data");
            }
            else
            {
                strcpy(criterio,"valor");
            }
            printf("Escolha a ordem:\na)Crescente\nb)Decrescente");
            do
            {
                op=getch();
            }
            while(op!='a'&&op!='A'&&op!='b'&&op!='B');
            if(op=='a')
            {
                strcpy(ordem,"crescente");
            }
            else
            {
                strcpy(ordem,"decrescente");
            }
        }

        selection_sort(pf,criterio,ordem);
        imprime_pesquisa(pf,tipo);
    }

}

//////////////////////////////////////////////////////////////////////////////////////
//                          gerenciador_entradas()                                  //
//  armazena um número indeterminado de JOGADOR e seus respectivos clubes em        //
//  apontador de apontadores para strings (char**nome e char**clube), de modo a     //
//  possibilitar a inclusão simultanea de JOGADOR.                                  //
//  a quantidade  de JOGADOR e clubes é guardada em qtd_jog que servirá tanto       //
//  como indice para  os nomes no apontador de apontadores, como multiplicador      //
//  para o malloc da estrutura auxiliar que será passada para ordenação alfabetica  //
//  e posteriormente passada para a função entra que realiza a inclusão sucessiva   //
//  de todos os JOGADOR.                                                            //
//////////////////////////////////////////////////////////////////////////////////////
void gerenciador_entradas(FUNDO*pf, DATA data)
{
    int qtd_jog=0,i=0;
    JOGADOR* paux=NULL;
    char** nome=(char**)malloc(1),str[MAX]="", **clube=(char**)malloc(1),op;
    //ciclo que realiza o armazenamento dos nomes e clubes a serem incluídos
    do
    {
        //expand_malloc_char aumenta a quantidade de strings a ser armazenadas através de apontador de apontadores
        nome=expande_malloc_char(nome,qtd_jog);
        clube=expande_malloc_char(clube,qtd_jog);

        printf("Por favor insira o nome do %dº jogador\n",qtd_jog+1);
        /**/ /** ÍNICIO CÓDIGO DEFINITIVO*/
        //gets(str);
        /**/ /** FIM CÓDIGO DEFINITIVO*/

        /**/ /**INICIO BLOCO DE TESTES**/
        switch(qtd_jog)
        {
        case 0:
            strcpy(str,"bernardo");
            break;
        case 1:
            strcpy(str,"cr7");
            break;
        case 2:
            strcpy(str,"abc");
            break;
        case 3:
            strcpy(str,"bart");

        }
        /**/ /**FIM BLOCO DE TESTES**/

        //inclusão do nome do jogador no indice referido por qtd_jog (começa em 0 e vai até n-1 nº de JOGADOR)
        *(nome+qtd_jog)=(char*)malloc(strlen(str)+1);
        strcpy(*(nome+qtd_jog),str);

        printf("Por favor insira o nome do clube do %dº jogador\n", qtd_jog+1);

        /**/ /** ÍNICIO CÓDIGO DEFINITIVO*/
        //gets(str);
        /**/ /** FIM CÓDIGO DEFINITIVO*/

        /**/ /**INICIO BLOCO DE TESTES**/
        switch(qtd_jog)
        {
        case 0:
            strcpy(str,"real");
            break;
        case 1:
            strcpy(str,"teste");
            break;
        case 2:
            strcpy(str,"teste2");
            break;
        case 3:
            strcpy(str,"teste3");
        }
        /**/ /**FIM BLOCO DE TESTES**/

        *(clube+qtd_jog)=(char*)malloc(strlen(str)+1);
        strcpy(*(clube+qtd_jog),str);

        /**/ /** ÍNICIO CÓDIGO DEFINITIVO*/
        /*do
        {
            printf("Deseja inserir mais um jogador? (s/n)\n");
            op=getch();
        }
        while(op!='s'&&op!='S'&&op!='n'&&op!='N');*/
        /**/ /** FIM CÓDIGO DEFINITIVO*/
        qtd_jog++;

    }/**CICLO PARA TESTES*/ while(qtd_jog<4);
    /**CICLO DEFINITIVO*///while(op!='n'&&op!='N');

    //criação da estrutura auxiliar paux que será preenchida com os nomes dos JOGADOR e clubes
    paux=(JOGADOR*)malloc(sizeof(JOGADOR)*qtd_jog);
    for(i=0; i<qtd_jog; i++)
    {
        (paux+i)->clube=*(clube+i);
        (paux+i)->nome=*(nome+i);
    }

    insert_string(paux,qtd_jog-1);  //FUNÇÃO QUE ORDENA O BLOCO DE JOGADOR A SER INSERIDO NA ESTRUTURA
    pf->plantel_ativo+=qtd_jog;
    imprime_txt(paux,"ENTRAM",qtd_jog,data);    //IMPRIME EM TXT O RESUMO DA OPERAÇÃO REALIZADA
    imprime_bin(paux,"ENTRAM",qtd_jog,data);


    entra(pf,paux,data,qtd_jog);     //REALIZA A INCLUSÃO DOS NOVOS JOGADOR NA ESTRUTURA DEFINITIVA

    //free(nome);
    //free(clube);
}

//////////////////////////////////////////////////////
//              expand_malloc_char                  //
//  aumenta a quantidade de strings a ser           //
//  armazenadas através de apontador de apontadores //
//////////////////////////////////////////////////////

char** expande_malloc_char(char**principal, int qtd)
{
    int i =0;
    char**paux=(char**)malloc(qtd);
    for(i=0; i<qtd; i++)
    {
        *(paux+i)=*(principal+i);
    }
    //free(principal);
    principal=paux;
    return principal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//                                         entra ()                                             //
//  realiza a inclusão dos JOGADOR no vetor f->pstart verifica se o tamanho máximo já foi       //
//  atingido e duplica em caso de verdade a inclusão dos novos JOGADOR será feita em            //
//  estrutura auxiliar (paux) precedida de comparação entre os nomes dos JOGADOR da estrutura   //
//  passada como argumento (pj) e os nomes dos JOGADOR já existentes (str) de modo a realizar   //
//  inclusão já ordenada dos nome                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////

void entra(FUNDO*f,JOGADOR*pj,DATA data,int novos_jog)
{
    char*str_nome=NULL,*str_clube=NULL,*str_estado=NULL,*aux1=NULL,*aux2=NULL;
    int i=0,j=0,k=0,antiga_qtd_jog=f->plantel_atual,nova_qtd_jog=antiga_qtd_jog+novos_jog;
    JOGADOR *paux=(JOGADOR*)malloc(sizeof(JOGADOR)*(nova_qtd_jog)),*str=NULL;

    //  ciclo que verifica se f->plantel_total, ou seja, a quantidade máxima de JOGADOR já foi alcançada
    //  enquanto isso se verificar, a quantidade total será duplicada.
    while(f->plantel_total<nova_qtd_jog)
    {
        duplica_tam_JOGADOR(f);
    }

    // apontador auxiliar para o vetor dinamico (JOGADOR já incluídos)
    str=f->pstart;

    //  ciclo que será executado tantas vezes quanto a soma entre os JOGADOR novos e os já existentes
    while(k<nova_qtd_jog)
    {
        if(i==antiga_qtd_jog) //    condição para evitar erro na chamada de menor_string
        {
            aux1=NULL;
        }
        else
        {
            aux1=(str+i)->nome; //  string a ser comparada
        }
        if(j==novos_jog) // condição para evitar erro na chamada de menor_string
        {
            aux2=NULL;
        }
        else
        {
            aux2=(pj+j)->nome; //   string a ser comparada
        }
        if(menor_string(aux1,aux2))//   compara o nome dos JOGADOR já existentes com o nome dos novos JOGADOR
        {
            //  caso em que o nome já existente é o menor
            (paux+k)->nome=(str+i)->nome;
            (paux+k)->clube=(str+i)->clube;
            (paux+k)->estado=(str+i)->estado;
            (paux+k)->index=(str+i)->index;

            i++;

        }
        else
        {
            //  caso em que o nome do novo jogador é o menor
            str_nome=(char*)malloc(strlen((pj+j)->nome)+1);
            strcpy(str_nome,((pj+j)->nome));
            (paux+k)->nome=str_nome;

            str_clube=(char*)malloc(strlen((pj+j)->clube)+1);
            strcpy(str_clube,(pj+j)->clube);
            (paux+k)->clube=str_clube;

            str_estado=(char*)malloc(strlen("ativo")+1);
            strcpy(str_estado,"ativo");
            (paux+k)->estado=str_estado;

            (paux+k)->index=f->plantel_atual;

            //  registra a nova operação como sendo de entrada de jogador com indice j
            nova_operacao(f,1,data,"ENTRAM",j);

            j++;

            f->plantel_atual+=1;
        }
        k++;
    }
    free(str);
    free(f->pstart);
    f->pstart=paux;
    if(f->mealheiro!=0) //  indica que não é a primeira entrada de JOGADOR, então há recolha de valor proporcional ao já existente
    {
        nova_operacao(f,(f->mealheiro)/(f->plantel_ativo),data,"RECOLHE",i);
    }
}

void duplica_tam_JOGADOR(FUNDO*f)
{
    int i=0;
    f->plantel_total*=2;
    JOGADOR*pj=(JOGADOR*)malloc(sizeof(JOGADOR)*f->plantel_total);
    for(i=0; i<f->plantel_atual; i++)
    {
        (pj+i)->clube=(f->pstart+i)->clube;
        (pj+i)->estado=(f->pstart+i)->estado;
        (pj+i)->index=(f->pstart+i)->index;
        (pj+i)->nome=(f->pstart+i)->nome;
    }
    free(f->pstart);
    f->pstart=pj;
}


//////////////////////////////////////////////////////////////////
//                          nova_operacao()                     //
//  cria um novo nó na estrutura LISTA apontado pela estrutura  //
//  FUNDO, sendo que a inserção é sempre feita no final.        //
//  A operação de cada nó é determinado pelo valor passado      //
//  pelo argumento id                                           //
//////////////////////////////////////////////////////////////////
void nova_operacao(FUNDO *f, float valor, DATA data, char*id,int index)
{
    //f->qtd_op++;
    char aux[MAX]="", *str=NULL;
    LISTA*paux=(LISTA*)malloc(sizeof(LISTA));

    /*
        inclusão das informações do novo elemento da lista
    */
    paux->data=data;
    paux->index=index;
    paux->pnext=NULL;


    sprintf(aux,"%s %.0f",id,valor);


    str=(char*)malloc(strlen(aux)+1);
    strcpy(str,aux);
    paux->op=str;
    paux->valor=valor;
    /*
        inserção do novo elemento na lista ligada
    */
    if(f->pfirst!=NULL&&f->plast!=NULL) //lista não está vazia
    {
        f->plast->pnext=paux;
        paux->pprev=f->plast;
        f->plast=paux;
    }
    else
    {
        f->pfirst=paux;
        f->pfirst->pprev=NULL;
        f->plast=paux;
        f->plast->pnext=NULL;
    }
    if (strcmp(id,"RECOLHE")==0) //id==0 significa que a operação é RECOLHE
    {
        f->mealheiro+=valor;
    }
    else if(strcmp(id,"PAGA")==0) //id==1 significa que a operação é PAGA
    {
        f->mealheiro-=valor;
    }
}

//////////////////////////////////////////////////////////////////
//                   gerenciador_saidas()                       //
//  registra a saída simultanea de vários JOGADOR armazenando //
//  número indeterminado de nomes e respectivos clubes através  //
//  apontador de apontadores e em seguida verificando se os     //
//  nomes indicados estão ou não ativos na lista de JOGADOR   //
//  através da função retorna_index_ativo()

void gerenciador_saidas(FUNDO*pf, DATA data)
{
    int i=0,qtd_jog=0;
    float valor=0;
    char** nome=(char**)malloc(1),str[MAX]="",op,**clube=(char**)malloc(1);
    JOGADOR*paux=NULL;
    do
    {
        nome=expande_malloc_char(nome,qtd_jog);
        clube=expande_malloc_char(clube,qtd_jog);
        printf("Por favor insira o nome do %dº jogador\n",qtd_jog+1);
        gets(str);

        if((i=retorna_index_ativo(pf,str))!=-1) //verifica se o nome consta como ativo no fundo
        {
            *(nome+qtd_jog)=(char*)malloc(strlen(str)+1);
            strcpy(*(nome+qtd_jog),str);

            strcpy(str,(pf->pstart+i)->clube);
            *(clube+qtd_jog)=(char*)malloc(strlen(str)+1);
            strcpy(*(clube+qtd_jog),str);
            qtd_jog++;
        }

        else
        {
            printf("O jogador %s não participa do fundo\n",str);
        }

        do
        {
            printf("Deseja retirar mais um jogador? (s/n)\n");
            op=getch();
        }
        while(op!='s'&&op!='S'&&op!='n'&&op!='N');
    }
    while(op!='n'&&op!='N');

    //estrutura auxiliar a ser passada para a função saida()
    paux=(JOGADOR*)malloc(sizeof(JOGADOR)*qtd_jog);
    for(i=0; i<qtd_jog; i++)
    {
        (paux+i)->clube=*(clube+i);
        (paux+i)->nome=*(nome+i);

    }
    free(nome);
    free(clube);


    valor=pf->mealheiro/pf->plantel_ativo;
    //ciclo de chamadas sucessivas da função saída
    for (i=0; i<qtd_jog; i++)
    {
        saida(pf,(paux+i)->nome,data,valor);
    }
    pf->plantel_ativo-=qtd_jog;

    imprime_txt(paux,"SAEM",qtd_jog,data);
    imprime_bin(paux,"SAEM",qtd_jog,data);
}

//////////////////////////////////////////////////////
//           retorna_index_ativo()                  //
//  através de uma série de comparações, retorna    //
//  o index de jogador ativo.                       //
//  se o jogador não existir ou não estiver ativo   //
//  retorna -1                                      //
//////////////////////////////////////////////////////

int retorna_index_ativo(FUNDO*f, char*nome)
{
    JOGADOR*paux=f->pstart;
    int i=0;
    for(i=0; i<f->plantel_atual; i++,paux++)
    {
        if(strcmp(paux->nome,nome)==0&&strcmp(paux->estado,"ativo")==0)
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////
//                saida()                               //
//  verifica o indice do nome passado como argumento e  //
//  realiza registro em LISTA da operação de saída e    //
//  retira de pf->mealheiro o valor proporcional ao     //
//  seu total dividido pela quantidade de participantes.//
//  o jogador passa a ter estado "inativo"              //
//////////////////////////////////////////////////////////

void saida(FUNDO*pf,char*nome,DATA data,float valor)
{
    int i=0;
    char * str_estado=NULL;
    i=retorna_index_ativo(pf,nome);


    nova_operacao(pf,1,data,"SAEM",i); //registra em LISTA a operação de saída do jogador do fundo
    recolhe_paga(pf,valor,data,"PAGA UM"); //reduz f->mealheiro no valor referente a um pagamento
    str_estado=(char*)malloc(strlen("inativo")+1);
    strcpy(str_estado,"inativo");
    (pf->pstart+i)->estado=str_estado;

}

void pesquisa_jogador(FUNDO*f, char op)
{
    int i=0;
    JOGADOR *paux=f->pstart;
    char parametro[MAX]="";

    if(op=='a')
    {
        printf("Por favor insira o nome do jogador\n");
        gets(parametro);
        printf("Resultado da pesquisa com o nome %s:\n", parametro);

        paux=pesquisa_nome(f,parametro,paux,&i,op);
        if(paux!=NULL)
        {
            printf("Nome: %s Clube: %s Estado: %s\n", paux->nome ,paux->clube,paux->estado);
        }
    }
    else if(op=='b')
    {
        printf("Por favor insira o nome do jogador\n");
        gets(parametro);

        printf("Resultado da pesquisa com o nome %s:\n", parametro);
        while(paux!=NULL)
        {
            paux=pesquisa_nome(f,parametro,paux,&i,op);
            if(paux!=NULL)
            {
                printf("Nome: %s Clube: %s Estado: %s\n", paux->nome ,paux->clube,paux->estado);
                paux++;
                i++;
            }
        }
    }
    else if(op=='c')
    {
        printf("Por favor insira o nome do clube\n");
        gets(parametro);
        printf("Resultado da pesquisa com o clube %s:\n", parametro);

        paux=pesquisa_nome(f,parametro,paux,&i,op);
        if(paux!=NULL)
        {
            printf("Nome: %s Clube: %s Estado: %s\n", paux->nome ,paux->clube,paux->estado);
        }
    }
    else if(op=='d')
    {
        printf("Por favor escolha o estado:\na)ativo\nb)inativo\n");
        do
        {
            op=getch();
        }
        while(op!='a'&&op!='A'&&op!='b'&&op!='B');

        if(op=='a')
        {
            strcpy(parametro,"ativo");
        }
        else
        {
            strcpy(parametro,"inativo");
        }
        op='d';
        printf("Resultado da pesquisa com o estado %s:\n", parametro);
        while(paux!=NULL)
        {
            paux=pesquisa_nome(f,parametro,paux,&i,op);
            if(paux!=NULL)
            {
                printf("Nome: %s Clube: %s Estado: %s\n", paux->nome ,paux->clube,paux->estado);
                paux++;
                i++;
            }
        }
    }
}


JOGADOR* pesquisa_nome(FUNDO*f,char*nome,JOGADOR *paux,int *i, char op)
{
    if(op=='a')
    {
        while(*(i)<f->plantel_atual)
        {
            if(strcmp(paux->nome,nome)==0)
            {
                return paux;
            }
            paux++;
            *(i)+=1;
        }
        return NULL;
    }
    else if (op=='b')
    {
        while(*(i)<f->plantel_atual)
        {
            if(strstr(paux->nome,nome)!=NULL)
            {
                return paux;
            }
            paux++;
            *(i)+=1;
        }
        return NULL;
    }
    else if(op=='c')
    {
        while(*(i)<f->plantel_atual)
        {
            if(strcmp(paux->clube,nome)==0)
            {
                return paux;
            }
            paux++;
            *(i)+=1;
        }
        return NULL;
    }
    else
    {
        while(*(i)<f->plantel_atual)
        {
            if(strcmp(paux->estado,nome)==0)
            {
                return paux;
            }
            paux++;
            *(i)+=1;
        }
        return NULL;
    }
}

//////////////////////////////////////////////////////////////
//                      recolhe_paga                        //
//  centraliza as tarefas de recolher e de pagar, fazendo   //
//  registro em ficheiro (imprime_txt()) e criando novos    //
//  nós na estrutura LISTA (nova_operacao())                //
//////////////////////////////////////////////////////////////


void recolhe_paga(FUNDO*pf, float valor,DATA data,char*op)
{
    int i=0;
    if(strcmp(op,"RECOLHE")==0)
    {
        imprime_txt(NULL,"RECOLHE",valor,data);
        imprime_bin(NULL,"RECOLHE",valor,data);
        for(i=0; i<pf->plantel_atual; i++)
        {
            nova_operacao(pf,valor,data,op,i);
        }
    }
    else if(strcmp(op,"PAGA")==0)
    {
        imprime_txt(NULL,"PAGA",valor,data);
        imprime_bin(NULL,"RECOLHE",valor,data);
        for(i=0; i<pf->plantel_atual; i++)
        {
            nova_operacao(pf,valor/pf->plantel_ativo,data,op,i);
        }
    }
    //opção chamada apenas no caso de saída, caso em que a operação em LISTA corresponde ao(s) índice(s)
    //daquele(s) que saiu(ram)
    else if(strcmp(op,"PAGA UM")==0)
    {
        nova_operacao(pf,valor,data,"PAGA",i);
    }
}

void init_fundo(FUNDO*pf, int nJOGADOR)
{
    int i=0;
    pf->plantel_total=nJOGADOR;
    JOGADOR*fj=(JOGADOR*)malloc(sizeof(JOGADOR)*nJOGADOR);
    for(i=0; i<nJOGADOR; i++)
    {
        (fj+i)->clube="";
        (fj+i)->estado="";
        (fj+i)->index=0;
        (fj+i)->nome="";
    }
    pf->pstart=fj;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "j4emlinha_dados.h"
#include "j4emlinha_gui.h"
/*
Autor: Gustavo Almeida
Local: Pojuca - Ba
Data: 22/06/2013
Esta aplicação é um jogo conhecido como 4 em linha.
*/
void jcomp(){
    ddsjogo1 rec1;
    zerarddsjogo1(&rec1);
    rec1.complvl = menudinamico(3);
    do{
        system("cls");
        vertela(1);
        vertela(4);
        fflush(stdin);
        gets(rec1.nomej1);
    }while(strlen(rec1.nomej1)>20);
    Mesadejogo ms1;
    zerarMesa(&ms1);
    carregandotela(9);
}

int trocaj(int j){
    switch(j){
    case 1:
        return 2;
        break;
    case 2:
        return 1;
        break;
    }
}

void jvsjog(){
    listarectotal recdt;
    ddsjogo2 rec2;
    zerarddsjogo2(&rec2);
    do{
        system("cls");
        vertela(1);
        vertela(5);
        fflush(stdin);
        gets(rec2.nomej1);
    }while(strlen(rec2.nomej1)>20);
    do{
        vertela(6);
        fflush(stdin);
        gets(rec2.nomej2);
    }while(strlen(rec2.nomej2)>20);
    Mesadejogo ms2;
    zerarMesa(&ms2);
    int col2,jogd = 1;
    carregandotela(7);
    frame_de_jogo:
        col2 = atua_tljogo(ms2.posicoes,jogd);
        if(col2 == -1){
            goto fim_de_jogo;
        }
        if(colunacheia(&ms2,col2-1)){
            if(verificavencedor(ms2) == 3){
                goto frame_de_jogo;
            }else{
                rec2.nemp++;
            }
        }else {
            insereDisco(&ms2,col2,jogd);
            if(verificavencedor(ms2) == 3){
                jogd = trocaj(jogd);
                goto frame_de_jogo;
            }else{
                col2 = atua_tljogo(ms2.posicoes,jogd);
                if(verificavencedor(ms2) == 1){
                    rec2.vitj1++;
                    printf("\n %s Venceu!\nJogar novamente?(s/n)",rec2.nomej1);
                    if(_getch() == 's'){
                        zerarMesa(&ms2);
                        goto frame_de_jogo;
                    }
                }else if(verificavencedor(ms2)==2){
                    rec2.vitj2++;
                    printf("\n %s Venceu!\nJogar novamente?(s/n)",rec2.nomej2);
                    if(_getch() == 's'){
                        zerarMesa(&ms2);
                        goto frame_de_jogo;
                    }
                }
                goto fim_de_jogo;
            }
        }
    fim_de_jogo:
        printf("Parabens, o jogador x ganhou a partida");
        recdt = recuperarecordes();
        if(recdt.rec2.ultimo == -1){
            recdt.rec2.recs[0] = rec2;
            recdt.rec2.ultimo++;
        }else{
            recdt =  posicionar2(recdt, rec2);
        }
        gravarecordes(&recdt);
        printf("Fim de Jogo");
}

int main()
{
    int resultmenu = 0;
    criatelas(0);
    tamanhotela(120,400);
    pontozero:
    vertela(1);
    printf("                                              Pressione ENTER para jogar");
    system("pause>NULL");
    resultmenu = menudinamico(2);

    switch (resultmenu){
    case 1:
        jcomp();
        break;
    case 2:
        jvsjog();
        break;
    case 3:
        system("cls");
        vertela(7);
        printf("\n\nPara voltar aperte enter\n");
        system("pause>");
        system("cls");
        goto pontozero;
        break;
    case 5:
        printf("Obrigado por jogar, ate a proxima");
        Sleep(3*1000);
        system("exit");
    }

    /*printf("Deseja ver alguma pagina?(0-n/1-s):\n");
    scanf("%d",&pg);
    while(pg != 0){
        printf("\nDigite o numero da pagina(0-sair):\n");
        scanf("%d",&pg);
        system("cls");
        vertela(pg);
    }*/
    return 0;
}

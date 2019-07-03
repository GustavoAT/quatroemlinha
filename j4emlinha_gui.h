#include <windows.h>
#include <conio.h>

/*
Autor: Gustavo Almeida
Local: Pojuca - Ba
Data: 22/06/2013
Biblioteca gráfica do jogo.
*/

typedef struct{
    char *caract;
}lin_carac;

typedef struct{
    char *sd;
    int seins;
    int wins;
    int nt;
}tptransf;

typedef struct{
    lin_carac recdados[3][20];
}listaderecordes;

//Métodos
void criatelas(int forcado);
void tamanhotela(int largura,int altura);
void vertela(int nrtela);
int menudinamico(int ntela);
void carregandotela(int seg);
void atua_tlrecordes(listaderecordes lis);
int atua_tljogo(int mesa[6][7],int jogseta);
void telavencedor(char Nomev[]);

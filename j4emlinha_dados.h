#define MAXRECD 10
#define NLIN 6
#define NCOL 7

/*
Autor: Gustavo Almeida
Local: Pojuca - Ba
Data: 22/06/2013
Biblioteca de tratamento dos dados do jogo.
*/

//Recipiente logico do jogo, serve de fonte para gerar o gráfico.
typedef struct{
    int posicoes[NLIN][NCOL];
    int apontadores[NCOL];
}Mesadejogo;

typedef struct{
    int pont;
    int npart;
    int complvl;
    char nomej1[20];
}ddsjogo1;

typedef struct{
    int vitj1;// Numero de partidas vencidas pelo jogador 1
    int vitj2;// Número de partidas vencidas pelo jogador 2
    int nemp;
    char nomej1[20];
    char nomej2[20];
}ddsjogo2;

typedef struct{
    ddsjogo1 recs[MAXRECD];
    int ultimo;
}listarec1;

typedef struct{
    ddsjogo2 recs[MAXRECD];
    int ultimo;
}listarec2;

typedef struct{
    listarec1 rec1;
    listarec2 rec2;
}listarectotal;

//Métodos
//Zera a mesa para próxima partida
void zerarMesa(Mesadejogo *ms);
void zerarddsjogo1(ddsjogo1 *ds);
void zerarddsjogo2(ddsjogo2 *ds);

int colunacheia(Mesadejogo *ms, int coluna);
//Insere um disco na coluna especificada, se possível
void insereDisco(Mesadejogo *ms,int coluna,int jogador);
int verificavencedor(Mesadejogo ms); //1 - Jogador1, 2 - Jogador2,0 - empate,3 - continuar

int calculapontuacao(int qdiscos);
void somapartida1(ddsjogo1 *jg, int pontua);
void somapartida2(ddsjogo2 *jg, int jvenc);

FILE *arquivorecs();
void gravarecordes(listarectotal *lr);
listarectotal recuperarecordes();
listarectotal posicionar1(listarectotal lr, ddsjogo1 dados);
listarectotal posicionar2(listarectotal lr, ddsjogo2 dados);


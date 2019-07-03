#include <stdio.h>
#include <stdlib.h>
#include "j4emlinha_dados.h"
/*
Autor: Gustavo Almeida
Local: Pojuca - Ba
Data: 22/06/2013
Especificação dos métodos da biblioteca que trata dos dados do jogo.
*/

void zerarMesa(Mesadejogo *ms){
    int ln;
    int cl;
    for(cl = 0;cl < NCOL;cl++){
        for(ln = 0;ln < NLIN;ln++){
            ms->posicoes[ln][cl] = 0;
        }
        ms->apontadores[cl] = NLIN - 1;
    }
}

void zerarddsjogo1(ddsjogo1 *ds){
    ds->pont = 0;
    ds->npart = 0;
}

void zerarddsjogo2(ddsjogo2 *ds){
    ds->nemp = 0;
    ds->vitj1 = 0;
    ds->vitj2 = 0;
}

int colunacheia(Mesadejogo *ms,int coluna){
    if(ms->apontadores[coluna] < 0){
        return 1;
    }else{
        return 0;
    }
}

void insereDisco(Mesadejogo *ms,int coluna,int jogador){
    ms->posicoes[ms->apontadores[coluna]][coluna] = jogador;
    ms->apontadores[coluna]--;
}

int verificavencedor(Mesadejogo ms){
    int cl,ln;
    int jo,qt,qt2,ndsc;
    for(ln = 5;ln >= 0;ln--){
        for(cl = 0;cl <= 3;cl++){
            if(ms.posicoes[ln][cl]!=0){
                jo = ms.posicoes[ln][cl];
                qt = cl+1;
                ndsc = 1;
                while(jo == ms.posicoes[ln][qt]){
                    ndsc++;
                    qt++;
                    if(ndsc == 4){
                    return jo;
                    }
                }
            }

        }
    }
    for(cl = 0;cl <= 6;cl++){
        for(ln = 5;ln >= 3;ln--){
                if(ms.posicoes[ln][cl]!=0){
                    jo = ms.posicoes[ln][cl];
                    qt = ln+1;
                    ndsc = 1;
                    while(jo == ms.posicoes[qt][cl]){
                        ndsc++;
                        qt++;
                        if(ndsc==4){
                        return jo;
                        }
                    }
                }

            }
        }
        for(cl = 3;cl <= 6;cl++){
          for(ln = 5;ln >= 3;ln--){
                if(ms.posicoes[ln][cl]!=0){
                    jo = ms.posicoes[ln][cl];
                    qt = ln-1;
                    qt2 = cl-1;
                    ndsc = 1;
                    while(jo == ms.posicoes[qt][qt2]){
                        ndsc++;
                        qt--;
                        qt2--;
                        if(ndsc==4){
                        return jo;
                        }
                    }
                }

            }
        }
        for(ln = 0;ln <= 3;ln++){
          for(cl = 3;cl <= 6;cl++){
                if(ms.posicoes[ln][cl]!=0){
                    jo = ms.posicoes[ln][cl];
                    qt = ln+1;
                    qt2 = cl-1;
                    ndsc = 1;
                    while(jo == ms.posicoes[qt][qt2]){
                        ndsc++;
                        qt++;
                        qt2--;
                        if(ndsc==4){
                        return jo;
                        }
                    }
                }
            }
        }
    return 3;
}

int calculapontuacao(int qdiscos){
    return 10*qdiscos;
}

void somapartida1(ddsjogo1 *jg,int pontua){
    jg->npart++;
    jg->pont += pontua;
}

void somapartida2(ddsjogo2 *jg, int jvenc){
    switch(jvenc){
        case 0:jg->nemp++;
                break;
        case 1:jg->vitj1++;
                break;
        case 2:jg->vitj2++;
                break;
        default:break;
    }
}

FILE *arquivorecs(){
    FILE *arq;
    arq = fopen_s("recordes\\j4emlinha_recs","rb",stdout);
    if(arq == NULL){
        arq = fopen_s("recordes\\j4emlinha_recs","wb", stdout);
    }else{
        arq = fopen_s("recordes\\j4emlinha_recs","rb+", stdout);
    }
    return arq;
}

void gravarecordes(listarectotal *lr){
    FILE *arqrecs = arquivorecs();
    if(arqrecs != NULL){
            fwrite(&lr,sizeof(lr),1,arqrecs);
            fclose(arqrecs);
        /*int ctd,ctt = 0;
        for(ctd = 0;ctd <= lr->ultimo1;ctd++){
            fwrite(&lr->recs[ctt],sizeof(lr->recs[ctt]),1,arqrecs);
            ctt++;
        }
        for(ctd = 0;ctd <= lr->ultimo2;ctd++){
            fwrite(&lr->recs[ctt],sizeof(lr->recs[ctt]),1,arqrecs);
            ctt++;
        }*/
    }else{
        printf("O arquivo de recordes não pode ser salvo.");
    }
}

listarectotal recuperarecordes(){
    FILE *arq;
    arq = fopen_s("recordes\\j4emlinha_recs","rb", stdout);
    listarectotal rcds;
    if(arq != NULL){
        fread(&rcds,sizeof(rcds),1,arq);
    }else{
        rcds.rec1.ultimo = -1;
        rcds.rec2.ultimo = -1;
        return rcds;
    }
}

listarectotal posicionar1(listarectotal lr, ddsjogo1 dados){
    int ct,ct2;
    ddsjogo1 aux;
    for(ct=0;ct <= lr.rec1.ultimo;ct++){
        if(dados.pont > lr.rec1.recs[ct].pont){
            aux = lr.rec1.recs[ct];
            lr.rec1.recs[ct] = dados;
            dados = aux;
            for(ct2 = ct;ct2 <= lr.rec1.ultimo;ct2++){
                aux = lr.rec1.recs[ct];
                lr.rec1.recs[ct] = dados;
                dados = aux;
            }
            if(lr.rec1.ultimo < MAXRECD - 1){
                lr.rec1.recs[lr.rec1.ultimo] = dados;
                lr.rec1.ultimo++;
            }
        }
    }
    return lr;
}

listarectotal posicionar2(listarectotal lr, ddsjogo2 dados){
    int ct,ct2,p1,p2,p3,p4,r1,r2;
    ddsjogo2 aux;
    for(ct=0;ct<=lr.rec2.ultimo;ct++){
        p1 = lr.rec2.recs[ct].vitj1;
        p2 = lr.rec2.recs[ct].vitj2;
        if(p2 > p1){
            r1 = p1;
            p1 = p2;
            p2 = r1;
        }
        p3 = dados.vitj1;
        p4 = dados.vitj2;
        if(p4 > p3){
            r2 = p3;
            p3 = p4;
            p4 = r2;
        }
        r1 = p1-p2;
        r2 = p3-p4;
        if(r1 > r2){
            aux = lr.rec2.recs[ct];
            lr.rec2.recs[ct] = dados;
            dados = aux;
            for(ct2 = ct;ct2 <= lr.rec2.ultimo;ct2++){
                aux = lr.rec2.recs[ct];
                lr.rec2.recs[ct] = dados;
                dados = aux;
            }
            if(lr.rec2.ultimo < MAXRECD - 1){
                lr.rec2.recs[lr.rec1.ultimo] = dados;
                lr.rec2.ultimo++;
            }
        }
    }
    return lr;
}

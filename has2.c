/*
    07/03/2019
    Autor:  Mafalda Santos; Inês Soares; Sílvia Faria

    Progama main do HAS para uma casa com 2 quartos, 1 cozinha, 1 sala, 1 jardim, 1 pisinca e 1 wc
    Programa capaz de ler os dados dos sensores. 
    Fazendo a sua conversão de hexadecimal para decimal.
    Neste exemplo, é utilizada uma estrutura para respresentar os motes. Foram
    utlizados 7 motes. Sendo possível depois escalonar o programa para mais motes.
    Definição dos tipos de divisao:

    Divisao - ID MOTE - - POSICAO VETOR
    Cozinha - Mote 1  - 0
    Quarto 1 - Mote 2  - 1
    Quarto 2 - Mote 3  - 2
    Sala - Mote 4 - 3
    Jardim - Mote 5 -4
    Piscina - Mote 6  -5
    WC - Mote 7 - 6 
    
    Atuadores: 0-FECHA/DESLIGA; 1-ABRE/LIGA
                        Para a corrente-potencia: 
                            0-eletrodomésticos podem estar ligado
                            1-não se pode ligar eletrodomésticos
    Sensores: Luz, Corrente, Temperatura, Humidade
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <postgresql/libpq-fe.h>

#include "set_atuadores.h"
#include "set_sensores.h"
#include "motes.h"
#include "write_matrix.h"

#include "ddl.h"
#include "dml_config.h"
#include "dml_get_config.h"
#include "dml_select.h"
#include "historico.h"





/*id*/
#define COZINHA 1
#define QUARTO 2
#define SALA 4
#define JARDIM 5
#define PISCINA 6 
#define WC 7

/***************************************************/
/*          VALORES PARA AS REGRAS DA CASA         */
/***************************************************/

#define S_L_MAX 2000
#define S_L_MIN 500
#define S_H 60
#define S_T_MAX 25
#define S_T_MIN 15

#define Q_1_L_MAX 2000
#define Q_1_L_MIN 500
#define Q_1_H 60
#define Q_1_T_MAX 25
#define Q_1_T_MIN 15

#define Q_2_L_MAX 2000
#define Q_2_L_MIN 500
#define Q_2_H 60
#define Q_2_T_MAX 25
#define Q_2_T_MIN 15

#define WC_T_MAX 25
#define WC_T_MIN 15

#define J_L_MAX 200
#define J_L_MIN 100
#define J_H 60
#define J_HORA 18
#define J_MINUTO_MIN 21
#define J_MINUTO_MAX 30

#define P_L_MAX 200
#define P_L_MIN 100
#define P_T_MAX 25
#define P_T_MIN 15

#define C_H 60

#define POTENCIA 9660 
#define CORRENTE_MAX_C 2 /*POR DIVISAO 9660/(7*3*230)*/
#define CORRENTE_MAX_S 2
#define CORRENTE_MAX_Q2 2
#define CORRENTE_MAX_Q1 2
#define CORRENTE_MAX_P 2
#define CORRENTE_MAX_J 2
#define CORRENTE_MAX_WC 2
/***************************************************/

#define BUFFER 256
#define DIM 22 /*dimensão (23) de uma mensagem começa a contar em 0*/
#define BASE 16
#define BASE2 256 /*16²*/
#define TOTAL_MOTES 7
//#define DEBUG
#define NOME_CASA "SIM"
#define TOTAL_REGRAS 22
#define ALTERAR_BD 0

/*ids SENSORES*/
#define HC 1
#define CC 2

#define HQ1 3
#define TQ1 4
#define LQ1 5
#define CQ1 6

#define HQ2 7
#define TQ2 8
#define LQ2 9
#define CQ2 10

#define HS 11
#define TS 12
#define LS 13
#define CS 14

#define HJ 15
#define LJ 16
#define CJ 17

#define TP 18
#define LP 19
#define CP 20

#define TWC 21
#define CWC 22

#define TOTAL_SENSORES 22

/*IDS ATUADORES*/

#define DC 1
#define PC 2

#define PERQ1 3
#define DQ1 4
#define AQQ1 5
#define ARQ1 6
#define PQ1 7

#define PERQ2 8
#define DQ2 9
#define AQQ2 10
#define ARQ2 11
#define PQ2 12

#define PERS 13
#define DS 14
#define AQS 15
#define ARRS 16
#define PS 17

#define RJ 18
#define IJ 19
#define PJ 20

#define AQP 21
#define IP 22
#define PP 23

#define AQWC 24
#define ARRWC 25
#define PWC 26

#define TOTAL_ATUADORES 26

#define ID_CASA 1

 /*atualiza os motes sempre que lê alguma coisa do terminal*/
void  ler_terminal (void);

/*passagem de valores hexadecimais para decimais nas posições
 *específicas de acordo com o protocolo*/
void conversao_valores(void);

/*inicialmente atuadores desligados*/
void inicializacao(void);



/*Atualização dos atuadores*/
void atualiza_mote (void);


/*conectar e disconectar da BS*/
void disconnect(void);
int connect(void);
void cria_tabelas(void);
void erro(void);
void  insere_configuracoes(void);
void get_configuracoes(void);
void insere_historico(void);
void insere_historico_primeiro(void);




 Mote mote[TOTAL_MOTES];
/* mote= [Cozinha, Quarto1, Quarto2, Sala,Jardim, Piscina, WC]*/
 char string[BUFFER], mensagem[DIM][3];

 int id=0;
 int aux=100;

PGconn *dbconn;

int main(){

    PGresult *res;
    int ok;
   
	char *teste,q;
    char* conn = "host='db.fe.up.pt' user='sinf19a55' password='OEWFqJwe'";
	dbconn = PQconnectdb(conn);

    if (PQstatus(dbconn) == CONNECTION_BAD){
         PQfinish(dbconn);
         fprintf(stderr,"Não conseguiu ligar à BD\n");
         exit(1);
    }

    inicializacao();
    ok=connect();
   if(!ok)
        erro();
    
    cria_tabelas();

    if(ALTERAR_BD){
        res= PQexec( dbconn, " TRUNCATE TABLE sim.atuador, sim.atuacao, sim.Sensor_Leitura, sim.atuador_estado,\
        sim.casa, sim.constituicao_mote, sim.mote, sim.depende,sim.divisao, sim.regra, sim.sensor,\
        sim.sobre CASCADE; ");

        if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        {
            PQclear(res);
            disconnect();
            
        }
    PQclear(res);
    
    }

    

    res= PQexec( dbconn, " TRUNCATE TABLE sim.Sensor_Leitura, sim.atuador_estado,\
     sim.sobre CASCADE; ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
    {
        PQclear(res);
        disconnect();
        
    }
    PQclear(res);

    insere_configuracoes();

    get_configuracoes();
    insere_historico_primeiro();
    

   while(1){

       ler_terminal();
       atualiza_mote();
       print_matrix(&mote[COZINHA-1], &mote[QUARTO-1], &mote[QUARTO], &mote[SALA-1], &mote[WC-1], &mote[JARDIM-1], &mote[PISCINA-1]);
       insere_historico();
   }
}

void ler_terminal (void){

    if ( NULL!= (fgets(string,256,stdin) ) ) {
        conversao_valores();

#ifdef DEBUG
        printf("Valores convertidos em decimal: \n Mote ID: %d , Luz: %f, I: %f, T: %f, H: %f , P: %f\n",mote[id-1].mote_id,mote[id-1].luz, mote[id-1].corrente,mote[id-1].temperatura, mote[id-1].humidade, mote[id-1].potencia);
#endif
    }
}
void conversao_valores(void){
    int ok=0;
   int contagem=0;
   char *atual;

/*ler a mensagem completa (23 blocos)*/
   while (DIM!=contagem) {

            if(!contagem) 
                atual=strtok(string," ");
            else
            {
                atual=strtok(NULL," ");
            }
            strcpy(mensagem[contagem],atual);
            contagem++;
            
        }
        /*Hexadecimal= AAAA= 16*16*16*10 +
                             16*16*10+
                             16*10+
                             16
                           =16*16(16*10 +10 )+ (16*10 +10 )
                           onde (16*10+10) é dado pela strtol()
        */
       
        id= BASE2 * ( (int) strtol(mensagem[5],NULL,BASE) );
        id+=(int)strtol(mensagem[6],NULL,BASE);

        mote[id-1].mote_id=id;

        mote[id-1].luz= BASE2 * ( (float) strtol(mensagem[12],NULL,BASE) );
        mote[id-1].luz+= (float)strtol(mensagem[13],NULL,BASE);

        mote[id-1].corrente= BASE2 * ( (float) strtol(mensagem[14],NULL,BASE) );
        mote[id-1].corrente+= (float)strtol(mensagem[15],NULL,BASE);

        mote[id-1].temperatura= BASE2 * ( (float) strtol(mensagem[16],NULL,BASE) );
        mote[id-1].temperatura+= (float)strtol(mensagem[17],NULL,BASE);

        mote[id-1].humidade= BASE2 * ( (float) strtol(mensagem[18],NULL,BASE) );
        mote[id-1].humidade+= (float)strtol(mensagem[19],NULL,BASE);
        ok=conversao_valores_reais(&dbconn, &mote[id-1], id);
        if(!ok)
            erro();
          
}


void atualiza_mote (void){

    int i=0;
    int potencia,corrente[7],regras[7];

    for(i=0;i<TOTAL_MOTES;i++){

        switch (i){

            case (COZINHA-1):
            {
               set_cozinha(&mote[i],get_max(&dbconn,HC,15));

            }break;
            case (QUARTO-1):
            {
                set_quarto_sala(&mote[i],get_max(&dbconn,LQ1,4),getmin(&dbconn,LQ1,4),get_max(&dbconn,HQ1,6),get_max(&dbconn,TQ1,5),getmin(&dbconn,TQ1,5));

            }break;

            case QUARTO:
            {
                set_quarto_sala(&mote[i],get_max(&dbconn,LQ2,7),getmin(&dbconn,LQ2,7), get_max(&dbconn,HQ2,9), get_max(&dbconn,TQ2,8), getmin(&dbconn,TQ2,8));

            }break;
            case (SALA-1):
            {   
                set_quarto_sala(&mote[i],get_max(&dbconn,LS,1),getmin(&dbconn,LS,1),get_max(&dbconn,HS,3),get_max(&dbconn,TS,2),getmin(&dbconn,TS,2));
            }break;
            case (JARDIM-1):
            {
                set_jardim(&mote[i],get_max(&dbconn,LJ,11), getmin(&dbconn,LJ,11),get_max(&dbconn,HJ,12),get_h(&dbconn,HJ,12),getmax_min(&dbconn,HJ,12),getmin_min(&dbconn,HJ,12));

            }break;
            case (PISCINA-1):
            {
                set_piscina(&mote[i],&mote[JARDIM-1],get_max(&dbconn,LP,13),getmin(&dbconn,LP,13),get_max(&dbconn,TP,14),getmin(&dbconn,TP,14));

            } break;
            case (WC-1):
            {
                set_wc(&mote[i],get_max(&dbconn,TWC, 10), getmin(&dbconn,TWC, 10));
            }
            break;

            default:
            break;
        }

    }
    corrente[0]=CC;
    corrente[1]=CQ1;
    corrente[2]=CQ2;
    corrente[3]=CS;
    corrente[4]=CJ;
    corrente[5]=CP;
    corrente[6]=CWC;

    for(i=16;i<23;i++){
        regras[i-16]=i;
    }

    potencia=get_potencia(&dbconn,corrente,regras);
    verifica_pot(&mote[COZINHA-1], &mote[WC-1], &mote[PISCINA-1], &mote[JARDIM-1], &mote[SALA-1], &mote[QUARTO],&mote[QUARTO-1] ,potencia);



}
void inicializacao(void){
    int i=0;

    for(i=0;i<TOTAL_MOTES;i++){
        
        mote[i].mote_id=i+1;
        mote[i].casa_id=ID_CASA;
        mote[i].pot_excedida=0;
        mote[i].rega=0;
        mote[i].persiana=0;
        mote[i].iluminacao=0;
        mote[i].desumidificador=0;
        mote[i].aquece=0;
        mote[i].arrefece=0;

        mote[i].pot_excedida_ant=0;
        mote[i].rega_ant=0;
        mote[i].persiana_ant=0;
        mote[i].iluminacao_ant=0;
        mote[i].desumidificador_ant=0;
        mote[i].aquece_ant=0;
        mote[i].arrefece_ant=0;
    }
}


void disconnect(void){
	PQfinish(dbconn);

}

void cria_tabelas(void){
    
    int ok=0;


    ok=cria_casa(&dbconn);
        if(!ok)
           erro();
    ok=cria_mote(&dbconn);
        if(!ok)
           erro();

    ok=cria_divisao(&dbconn);
        if(!ok)
           erro();
     
   
    ok=cria_sensor(&dbconn);
        if(!ok)
           erro();

     
    ok=cria_constituicao_mote(&dbconn);
        if(!ok)
           erro();

    ok=cria_regra(&dbconn);
        if(!ok)
           erro();
     
    ok=cria_atuador(&dbconn);
        if(!ok)
           erro();

    ok=cria_atuador_estado(&dbconn);
        if(!ok)
           erro();    

    ok=cria_sobre(&dbconn);
        if(!ok)
           erro();   

    ok=cria_depende(&dbconn);
        if(!ok)
           erro();
     
    ok=cria_atuacao(&dbconn);
        if(!ok)
           erro();
    ok=cria_sensor_leitura(&dbconn);
    if(!ok)
        erro();
     
}

void insere_configuracoes(void){

    int ok=0;
    int i,j=1;
 
    /*INSERIR CASA NA DB*/
    ok= insere_casa(&dbconn,ID_CASA,NOME_CASA);

    if(!ok)
         erro();
  

    /*INSERIR MOTES NA DB*/

    ok=insere_mote( &dbconn,COZINHA, COZINHA , 2);
    if(!ok)
    erro();

    ok=insere_mote( &dbconn, QUARTO,QUARTO, 4);
    if(!ok)
    erro();

    ok=insere_mote( &dbconn, QUARTO+1,QUARTO+1, 4);
    if(!ok)
    erro();

    ok=insere_mote( &dbconn,SALA, SALA, 4);
    if(!ok)
    erro();

    ok=insere_mote( &dbconn,JARDIM, JARDIM, 2);
    if(!ok)
    erro();
    
    ok=insere_mote( &dbconn,PISCINA, PISCINA, 3);
    if(!ok)
    erro();

    ok=insere_mote( &dbconn,WC, WC, 2);
    if(!ok)
    erro();
            

    /*INSERIR DIVISOES NA DB*/
    ok=insere_divisao( &dbconn,ID_CASA,COZINHA,COZINHA, "cozinha");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA, QUARTO, QUARTO,"quarto1");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA,QUARTO+1,QUARTO+1, "quarto2");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA,SALA,SALA, "sala");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA,JARDIM,JARDIM, "jardim");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA,PISCINA, PISCINA, "piscina");
    if(!ok)
    erro();

    ok=insere_divisao( &dbconn,ID_CASA,WC, WC,"wc");
    if(!ok)
    erro();


    /*INSERIR SENSORES NA DB*/
	
    ok=insere_sensor( &dbconn,HC, "humidade_cozinha", "humidade");
    if(!ok)
    erro();
    ok=insere_sensor( &dbconn,CC, "corrente_cozinha", "corrente");
    if(!ok)
    erro();


    ok=insere_sensor(&dbconn,HQ1, "humidade_quarto1", "humidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,TQ1, "temperatura_quarto1", "temperatura");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,LQ1, "luminosidade_quarto1", "luminosidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CQ1, "corrente_quarto1", "corrente");
    if(!ok)
    erro();


    ok=insere_sensor(&dbconn,HQ2,"humidade_quarto2", "humidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,TQ2,"temperatura_quarto2", "temperatura");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,LQ2, "luminosidade_quarto2", "luminosidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CQ2, "corrente_quarto2", "corrente");
    if(!ok)
    erro();

    ok=insere_sensor(&dbconn,HS, "humidade_sala", "humidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,TS, "temperatura_sala", "temperatura");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,LS,"luminosidade_sala", "luminosidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CS,"corrente_sala", "corrente");
    if(!ok)
    erro();

    ok=insere_sensor(&dbconn,HJ, "humidade_jardim", "humidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,LJ, "luminosidade_jardim", "luminosidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CJ, "corrente_jardim", "corrente");
    if(!ok)
    erro();

    ok=insere_sensor(&dbconn,TP,"temperatura_piscina", "temperatura");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,LP, "luminosidade_piscina", "luminosidade");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CP, "corrente_piscina", "corrente");
    if(!ok)
    erro();

    ok=insere_sensor(&dbconn,TWC,"temperatura_wc", "temperatura");
    if(!ok)
    erro();
    ok=insere_sensor(&dbconn,CWC, "corrente_wc", "corrente");
    if(!ok)
    erro();
  

    /*INSERIR ATUADORES NA DB*/
  

    ok=insere_atuador(&dbconn,DC, "desumidificador_cozinha", "desumidificador");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PC, "potencia_cozinha", "potencia");
    if(!ok)
    erro();
    
    ok=insere_atuador(&dbconn,PERQ1, "persianas_quarto1", "persianas");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,DQ1, "desumidificador_quarto1", "desumidificador");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn, AQQ1,"aquecimento_quarto1", "aquecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,ARQ1, "arrefecimento_quarto1", "arrefecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PQ1, "potencia_quarto1", "potencia");
    if(!ok)
    erro();

    ok=insere_atuador(&dbconn,PERQ2, "persianas_quarto2", "persianas");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,DQ2,"desumidificador_quarto2", "desumidificador");if(!ok)
    erro();
    ok=insere_atuador(&dbconn,AQQ2, "aquecimento_quarto2", "aquecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,ARQ2, "arrefecimento_quarto2", "arrefecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PQ2, "potencia_quarto2", "potencia");
    if(!ok)
    erro();

    ok=insere_atuador(&dbconn,PERS, "persianas_sala", "persianas");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,DS, "desumidificador_sala", "desumidificador");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,AQS, "aquecimento_sala", "aquecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,ARRS, "arrefecimento_sala", "arrefecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PS, "potencia_sala", "potencia");
    if(!ok)
    erro();
    
    ok=insere_atuador(&dbconn,RJ, "rega_jardim", "rega");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,IJ, "iluminacao_jardim", "iluminacao");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PJ, "potencia_jardim", "potencia");
    if(!ok)
    erro();

    ok=insere_atuador(&dbconn,AQP, "aquecimento_piscina", "aquecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,IP, "iluminacao_piscina", "iluminacao");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PP, "potencia_piscina", "potencia");
    if(!ok)
    erro();
    
    ok=insere_atuador(&dbconn,AQWC, "aquecimento_wc", "aquecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,ARRWC, "arrefecimento_wc", "arrefecimento");
    if(!ok)
    erro();
    ok=insere_atuador(&dbconn,PWC, "potencia_wc", "potencia");
    if(!ok)
    erro();
      
	/*INSERE NUMERO DAS REGRAS*/
	for(j=1; j<TOTAL_REGRAS+1; j++){
		ok=insere_num_regras(&dbconn,j, j);
        	if(!ok) erro();
    }
 
/*INSERIR VALORES MAXIMOS E MINIMOS DAS REGRAS*/
	/*SALA*/
	ok=insere_regras(&dbconn, LS ,1, S_L_MAX, S_L_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn, TS ,2, S_T_MAX, S_T_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn, HS ,3, S_H, 0);
        if(!ok) erro();
	
	/*QUARTO1*/
	ok=insere_regras(&dbconn,LQ1,4, Q_1_L_MAX, Q_1_L_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn,TQ1, 5,Q_1_T_MAX, Q_1_T_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn, HQ1, 6,Q_1_H, 0);
        if(!ok) erro();

	/*QUARTO2*/
	ok=insere_regras(&dbconn,LQ2,7 ,Q_2_L_MAX, Q_2_L_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn,TQ2, 8,Q_2_T_MAX, Q_2_T_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn,HQ2 , 9, Q_2_H, 0);
        if(!ok) erro();

	/*WC*/
	ok=insere_regras(&dbconn,TWC,10, WC_T_MAX, WC_T_MIN);
        if(!ok) erro();

	/*JARDIM*/
	ok=insere_regras(&dbconn,LJ,11, J_L_MAX, J_L_MIN);
        if(!ok) erro();
	ok=insere_regra_jardim_hora(&dbconn,HJ,12, J_H, 0, J_HORA, J_MINUTO_MAX, J_MINUTO_MIN);
        if(!ok) erro();

	/*PISCINA*/
	ok=insere_regras(&dbconn,LP ,13, P_L_MAX, P_L_MIN);
        if(!ok) erro();
	ok=insere_regras(&dbconn, TP,14, P_T_MAX, P_T_MIN);
        if(!ok) erro();
	
	/*COZINHA*/
	ok=insere_regras(&dbconn,HC,15, C_H, 0);
        if(!ok) erro();

	/*POTENCIA*/
	ok=insere_regras(&dbconn,CC,16,CORRENTE_MAX_C, 0);
        if(!ok) erro();
	ok=insere_regras(&dbconn,CQ1,17,CORRENTE_MAX_Q1, 0);
        if(!ok) erro();
	ok=insere_regras(&dbconn,CQ2,18,CORRENTE_MAX_Q2, 0);
        if(!ok) erro();
    ok=insere_regras(&dbconn,CS,19,CORRENTE_MAX_S, 0);
        if(!ok) erro();
    ok=insere_regras(&dbconn,CJ,20,CORRENTE_MAX_J, 0);
        if(!ok) erro();
    ok=insere_regras(&dbconn,CP,21,CORRENTE_MAX_P, 0);
        if(!ok) erro();
    ok=insere_regras(&dbconn,CWC,22,CORRENTE_MAX_WC, 0);
        if(!ok) erro();

/*INSERIR CONSTITUICAO MOTE*/  
    for(i=1;i<TOTAL_SENSORES+1;i++){
        
        if(i<3)
            ok=insere_constituicao_mote(&dbconn,i,COZINHA);
        else if (i<7)
            ok=insere_constituicao_mote(&dbconn,i,QUARTO);
        else if (i<11)   
            ok=insere_constituicao_mote(&dbconn,i,QUARTO+1);
        else if (i<15)
            ok=insere_constituicao_mote(&dbconn,i,SALA);
        else if (i<18)
            ok=insere_constituicao_mote(&dbconn,i,JARDIM);
        else if (i<21)
           ok=insere_constituicao_mote(&dbconn,i,PISCINA);
        else 
            ok=insere_constituicao_mote(&dbconn,i,WC);
        
        if(!ok) erro();

    }
/*INSERIR ATUACAO  */
     for(i=1;i<TOTAL_ATUADORES+1;i++){

        if(i<3)
            ok=insere_atuacao(&dbconn,i,COZINHA);
        else if (i<8)
            ok=insere_atuacao(&dbconn,i,QUARTO);
        else if (i<13)   
            ok=insere_atuacao(&dbconn,i,QUARTO+1);
        else if (i<18)
            ok=insere_atuacao(&dbconn,i,SALA);
        else if (i<21)
            ok=insere_atuacao(&dbconn,i,JARDIM);
        else if (i<24)
           ok=insere_atuacao(&dbconn,i,PISCINA);
        else 
            ok=insere_atuacao(&dbconn,i,WC);
        
        if(!ok) erro();

    }
  

}
void insere_historico(void){
    //INSERIR HISTORICO

    int i,ok;

    
   
   time_t t;
    struct tm tm;
    t=time(NULL);
    tm=*localtime(&t);
    
    if(tm.tm_sec != aux){

	    aux=tm.tm_sec;

      
        //atuadores
        for(i=1;i<TOTAL_ATUADORES+1;i++){
            if(i<3)
                ok=insere_historico_atuador( &dbconn, &mote[COZINHA-1] , i);
            else if (i<8)
                ok=insere_historico_atuador( &dbconn,&mote[QUARTO-1] , i);
            else if (i<13)   
                ok=insere_historico_atuador( &dbconn, &mote[QUARTO] , i);
            else if (i<18)
                ok=insere_historico_atuador( &dbconn, &mote[SALA-1] , i);
            else if (i<21)
                ok=insere_historico_atuador( &dbconn, &mote[JARDIM-1] , i);
            else if (i<24)
            ok=insere_historico_atuador( &dbconn, &mote[PISCINA-1] , i);
            else 
                ok=insere_historico_atuador( &dbconn, &mote[WC-1] , i);
            
            if(!ok) erro();
        }
    }
   
}
void insere_historico_primeiro(void){
    //INSERIR HISTORICO

    
 
    int i,ok;


      
        //atuadores
        for(i=1;i<TOTAL_ATUADORES+1;i++){
            if(i<3)
                ok= insere_historico_atuador_primeiro( &dbconn, &mote[COZINHA-1] , i);
            else if (i<8)
                ok= insere_historico_atuador_primeiro( &dbconn,&mote[QUARTO-1] , i);
            else if (i<13)   
                ok= insere_historico_atuador_primeiro( &dbconn, &mote[QUARTO] , i);
            else if (i<18)
                ok= insere_historico_atuador_primeiro( &dbconn, &mote[SALA-1] , i);
            else if (i<21)
                ok= insere_historico_atuador_primeiro( &dbconn, &mote[JARDIM-1] , i);
            else if (i<24)
            ok= insere_historico_atuador_primeiro( &dbconn, &mote[PISCINA-1] , i);
            else 
                ok= insere_historico_atuador_primeiro( &dbconn, &mote[WC-1] , i);
           
            if(!ok) erro();
        }
    
   
}


void get_configuracoes(void){
    int i;

    for(i=0;i<TOTAL_MOTES;i++){

        get_id(&dbconn , &mote[i]);

    }

}

void erro(void){
        	
	
	fprintf(stderr,"%s\n", PQerrorMessage(dbconn));

    disconnect();
    exit(1);

}


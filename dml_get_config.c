#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "motes.h"


#define COZINHA 1
#define QUARTO 2
#define SALA 4
#define JARDIM 5
#define PISCINA 6 
#define WC 7

#define LUZ 0
#define CORRENTE 1
#define TEMPERATURA 2
#define HUMIDADE 3


#define H "humidade"
#define T "temperatura"
#define L "luminosidade"
#define C "corrente"

  
#define PER "persianas"
#define D "desumidificador"
#define AQ "aquecimento"
#define ARR "arrefecimento"
#define P "potencia"
#define R "rega"
#define I "iluminacao"

#define AQUECE 0
#define ARREFECE 1
#define PERSIANA 2
#define DESUMIDIFICADOR 3
#define  ILUMINACAO 4
#define REGA 5
#define POT_EXCEDIDA 6

#define SENSOR_TIPO 2
#define SENSOR_ID 0
#define MAX 500

int not_retrieve_2 (PGresult **res){

    if(PQresultStatus(*res)!= PGRES_TUPLES_OK){
            printf("not retrieve\n");
            PQclear(*res);
            return 1;
        }
    return 0;
    
}



int get_id(PGconn **conn,Mote *x){

    PGresult *res1,*res2;
    int linhas,i,sensor_id, sensores=0,atuadores=0,j=0;
    char teste[10],query[MAX]="SELECT (id_sensor) FROM\
                    sim.constituicao_mote WHERE\
                    id_mote=";

/*seleciona id_sensor*/
    sprintf(teste,"%d;",x->mote_id);
    strcat(query,teste);

 
    res1=PQexec(*conn,query); 

    if( not_retrieve_2 (&res1))
        return 0;

    sensores= PQntuples(res1);
  
/*coloca tudo a 0 inicialmente*/

    for(i=0;i<4;i++){
        x->sensores_ativos[i]=0;
        x->sensores_id[i]=0;
    }

    for(i=0;i<7;i++){
        x->atuadores_ativos[i]=0;
        x->atuadores_id[i]=0;
    }

/*seleciona dos sensores todos os com id_Sensor escolhido*/
    for(j=0;j<sensores;j++){

        sprintf(query,"SELECT tipo FROM\
                    sim.sensor WHERE\
                    id=");

        sprintf(teste,"%d;",atoi(PQgetvalue(res1,j,0)));
        strcat(query,teste);

        res2=PQexec(*conn,query); 

        if(not_retrieve_2 (&res2))
            return 0;  


        if ( !strcmp(PQgetvalue(res2,0,0), H) ){
           
            x->sensores_ativos[HUMIDADE]=1;
            x->sensores_id[HUMIDADE]=atoi(PQgetvalue(res1,j,0));
            
        }


        if ( !strcmp(PQgetvalue(res2,0,0),C) ){
            x->sensores_ativos[CORRENTE]=1;
            x->sensores_id[CORRENTE]=atoi(PQgetvalue(res1,j,0));
        }


        if ( !strcmp(PQgetvalue(res2,0,0),T) ){
            x->sensores_ativos[TEMPERATURA]=1;
            x->sensores_id[TEMPERATURA]=atoi(PQgetvalue(res1,j,0));
        }
     

        if ( !strcmp(PQgetvalue(res2,0,0),L) ){
            x->sensores_ativos[LUZ]=1;
            x->sensores_id[LUZ]=atoi(PQgetvalue(res1,j,0));
        }
  
  
        PQclear(res2);

    }



    PQclear(res1);
   
   sprintf(query,"SELECT (id_atuador) FROM\
                    sim.atuacao WHERE\
                    id_divisao=");

/*seleciona id_atuador para cada divisao,
procura a divisao com id=moted_id pq têm os mesmos id's*/

    x->divisao_id=x->mote_id;
    sprintf(teste,"%d;",x->mote_id);
    strcat(query,teste);

 
    res1=PQexec(*conn,query); 

    if( not_retrieve_2 (&res1))
        return 0;

    atuadores= PQntuples(res1);
  


/*seleciona dos atuadores todos os com id_atuador escolhido*/
    for(j=0;j<atuadores;j++){

        sprintf(query,"SELECT tipo FROM\
                    sim.atuador WHERE\
                    id=");

        sprintf(teste,"%d;",atoi(PQgetvalue(res1,j,0)));
        strcat(query,teste);

        res2=PQexec(*conn,query); 

        if(not_retrieve_2 (&res2))
            return 0;  



        if ( !strcmp(PQgetvalue(res2,0,0), PER) ){
           
            x->atuadores_ativos[PERSIANA]=1;
            x->atuadores_id[PERSIANA]=atoi(PQgetvalue(res1,j,0));
           
        }


        if ( !strcmp(PQgetvalue(res2,0,0),D) ){
            x->atuadores_ativos[DESUMIDIFICADOR]=1;
            x->atuadores_id[DESUMIDIFICADOR]=atoi(PQgetvalue(res1,j,0));
        }


        if ( !strcmp(PQgetvalue(res2,0,0),AQ) ){
            x->atuadores_ativos[AQUECE]=1;
            x->atuadores_id[AQUECE]=atoi(PQgetvalue(res1,j,0));
        }
     

        if ( !strcmp(PQgetvalue(res2,0,0),ARR) ){
            x->atuadores_ativos[ARREFECE]=1;
            x->atuadores_id[ARREFECE]=atoi(PQgetvalue(res1,j,0));
        }
       
        if ( !strcmp(PQgetvalue(res2,0,0),P) ){
            x->atuadores_ativos[POT_EXCEDIDA]=1;
            x->atuadores_id[POT_EXCEDIDA]=atoi(PQgetvalue(res1,j,0));
        }

        if ( !strcmp(PQgetvalue(res2,0,0),R) ){
            x->atuadores_ativos[REGA]=1;
            x->atuadores_id[REGA]=atoi(PQgetvalue(res1,j,0));
        }
        if ( !strcmp(PQgetvalue(res2,0,0),I) ){
            x->atuadores_ativos[ILUMINACAO]=1;
            x->atuadores_id[ILUMINACAO]=atoi(PQgetvalue(res1,j,0));
        }
              
  
        PQclear(res2);


    }



    PQclear(res1);


    return 1;
}

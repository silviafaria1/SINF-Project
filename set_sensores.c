
#include <stdio.h>
#include <postgresql/libpq-fe.h>
#include <time.h>
#include <string.h>
#include "motes.h"

#define TENSAO 230

#define COZINHA 1
#define QUARTO 2
#define SALA 4
#define JARDIM 5
#define PISCINA 6 
#define WC 7



#define MAX 500

#define LUZ 0
#define CORRENTE 1
#define TEMPERATURA 2
#define HUMIDADE 3



int insert_ok_4(PGresult **res){

    if(PQresultStatus(*res)!= PGRES_COMMAND_OK){
        PQclear(*res);
      
        return 0;
    }
    PQclear(*res);
    return 1;
}

int insere_historico_sensor( PGconn ***conn,Mote **x, int id){

    char query[MAX]="insert into sim.Sensor_Leitura(id_sensor, leitura, data) values (";
    PGresult *res;
    char str[10], data[25];
    time_t t;
    struct tm tm;
    float leitura=0;

    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);

    if(id == 1) leitura = (*x)->humidade;
    else if (id == 2) leitura = (*x)->corrente;
    else if (id == 3) leitura = (*x)->humidade;
    else if (id == 4) leitura = (*x)->temperatura;
    else if (id == 5) leitura = (*x)->luz;
    else if (id == 6) leitura = (*x)->corrente;
    else if (id == 7) leitura = (*x)->humidade;
    else if (id == 8) leitura = (*x)->temperatura;
    else if (id == 9) leitura = (*x)->luz;
    else if (id == 10) leitura = (*x)->corrente;
    else if (id == 11) leitura = (*x)->humidade;
    else if (id == 12) leitura = (*x)->temperatura;
    else if (id == 13) leitura = (*x)->luz;
    else if (id == 14) leitura = (*x)->corrente;
    else if (id == 15) leitura = (*x)->humidade;
    else if (id == 16) leitura = (*x)->luz;
    else if (id == 17) leitura = (*x)->corrente;
    else if (id == 18) leitura = (*x)->temperatura;
    else if (id == 19) leitura = (*x)->luz;
    else if (id == 20) leitura = (*x)->corrente;
    else if (id == 21) leitura = (*x)->temperatura;
    else  leitura = (*x)->corrente;

   
    sprintf(str,"%d,%d,",id, (int)leitura);    
    strcat(query, str); 
    strcat(query, data);
    strcat(query,");");
    
    res=PQexec(**conn,query);

    return (insert_ok_4(&res));

}

int conversao_valores_reais(PGconn **conn, Mote *x, int id)
{   
    int ok;
   

    if(x->sensores_ativos[LUZ]){
    
        x->luz=0.625*1000000*(x->luz/4096)*1.5/100000*1000;
        ok=insere_historico_sensor( &conn, &x , x->sensores_id[0]);
        if(!ok)
            return 0;
    }
    
    if(x->sensores_ativos[CORRENTE]){
        x->corrente=0.769*100000*((x->corrente/4096)*1.5/100000)*1000;
        x->potencia=x->corrente*TENSAO;
        ok=insere_historico_sensor( &conn, &x , x->sensores_id[1]);
        if(!ok)
            return 0;
        
    }

    if(x->sensores_ativos[TEMPERATURA]){
        x->temperatura=-39.6+0.01*x->temperatura;
        ok=insere_historico_sensor( &conn, &x , x->sensores_id[2]);
        if(!ok)
            return 0;
        
    }
        
    if(x->sensores_ativos[HUMIDADE]){
        x->humidade=-2.0468+0.0367* x->humidade-1.5955/1000000* (x->humidade)*(x->humidade);
        ok=insere_historico_sensor( &conn, &x , x->sensores_id[3]);
        if(!ok)
            return 0;
  
    }
    
    return 1;
        

}


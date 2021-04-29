#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include <time.h>

#define MAX 500

int not_retrieve(PGresult **res){

    if(PQresultStatus(*res)!= PGRES_TUPLES_OK){
            printf("not retrieve\n");
            PQclear(*res);
            return 1;
        }
    return 0;
    
}

int insert_ok(PGresult **res){

    if(PQresultStatus(*res)!= PGRES_COMMAND_OK){
        PQclear(*res);
      
        return 0;
    }

    PQclear(*res);
    return 1;
    

    

}

int insere_casa( PGconn **conn,int id, char *nome_casa){

    char teste[MAX]= "select exists (select id from sim.casa where id= ";
    char query[MAX]="insert into sim.casa (id, nome) values (";
    PGresult *res;
    char str[10];

    /*ver se o nome da casa ja existe na base de dados*/
    sprintf(str,"%d",id);
    strcat(teste, str);
    strcat(teste,");");
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);  
        strcat(query, str); 
        strcat(query,",'");     
        strcat(query, nome_casa);   
        strcat(query,"');");
        res=PQexec(*conn,query);

      return (insert_ok(&res));
    
    }

    return 1;

}



int insere_mote( PGconn **conn,int id, int n_mote, int n_sensores){
    
    char teste[MAX]= "select exists (select (id) from sim.mote where id=";
    char query[MAX]="INSERT INTO sim.Mote (id, numero, num_sensores) VALUES (";
    char str[10];
    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d",id);
    strcat(teste, str);
    strcat(teste,");");
    
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res); 
        sprintf(str,"%d,%d,%d);",id,n_mote,n_sensores);
        strcat(query, str );
        
        res=PQexec(*conn,query);
        return (insert_ok(&res));
 

    }

    return 1;
 
}

int insere_divisao( PGconn **conn,int id_casa, int id, int id_mote, char *divisao){

    char teste[MAX]= "select exists (select id from sim.divisao where id=";
    char query[MAX]="INSERT INTO sim.divisao (id, id_casa, id_mote, nome) VALUES (";
    char str[15];
    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d",id);
    strcat(teste, str);
    strcat(teste,");");
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);   

        sprintf(str,"%d,%d,%d,'",id,id_casa,id_mote);
        strcat(query, str ); 
        strcat(query, divisao);  
        strcat(query,"');");
        
        res=PQexec(*conn,query);
        return ( insert_ok(&res));

    }
    return 1;

   
}

int insere_sensor( PGconn **conn,int id, char *nome_sensor, char *tipo_sensor){

    char teste[MAX]= "select exists (select (id) from sim.sensor where id=";
    char query[MAX]="INSERT INTO sim.Sensor (id,nome, tipo) VALUES (";
    char str[10];
    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d",id);
    strcat(teste, str);
    strcat(teste,");");
  
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        
        sprintf(str,"%d",id);
        strcat(query, str);
        strcat(query,",'");
        strcat(query, nome_sensor); 
        strcat(query,"','");
        strcat(query,tipo_sensor);
        strcat(query,"');");
   
        res=PQexec(*conn,query);
        return ( insert_ok(&res));

    }
    return 1;
}

int insere_atuador( PGconn **conn,int id, char *nome_atuador, char *tipo_atuador){

    char teste[MAX]= "select exists (select (id) from sim.atuador where id=";
    char query[MAX]="INSERT INTO sim.atuador (id,nome, tipo) VALUES (";
    char str[10];

    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d);",id);
    strcat(teste, str);
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        
        sprintf(str,"%d",id);
        strcat(query, str);
        strcat(query,",'");
        strcat(query, nome_atuador); 
        strcat(query,"','");
        strcat(query,tipo_atuador);
        strcat(query,"');");
        res=PQexec(*conn,query);
      return ( insert_ok(&res));

    }
    return 1;
    

}

int insere_num_regras( PGconn **conn,int id, int n_regra){
   
    char teste[MAX]= "select exists (select (id) from sim.Regra where id=";
    char query[MAX]="INSERT INTO sim.Regra (id,numero) VALUES (";
    char str[10];
    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d);",id);
    strcat(teste, str);
      
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);   
        sprintf(str,"%d,%d);",id,n_regra);
        strcat(query, str);
        
        res=PQexec(*conn,query);
        return ( insert_ok(&res));

    }
    return 1;
   
}

int insere_regras( PGconn **conn, int id_sensor, int id_regra, int max, int min){


    char teste[MAX]= "select exists (select (id_sensor,id_regra) from sim.depende where id_sensor=";
    char query[MAX]="INSERT INTO sim.depende (id_sensor, id_regra, max, min) VALUES (";
    char str[25];
    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d and id_regra=%d);",id_sensor,id_regra);
    strcat(teste, str);
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        sprintf(str,"%d,%d,%d,%d);",id_sensor,id_regra, max,min);
        strcat(query, str);
        res=PQexec(*conn,query);
        return ( insert_ok(&res));

    }
    return 1;

}

int insere_regra_jardim_hora(PGconn **conn,int id_sensor, int id_regra, int max, int min, int hora, int min_max, int min_min){
    
    
    char teste[MAX]= "select exists (select (id_sensor,id_regra) from sim.depende where id_sensor=";
    char query[MAX]="INSERT INTO sim.depende (id_sensor, id_regra, max, min, hora, min_max, min_min ) VALUES (";
    char str[40];
  

    PGresult *res;

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d and id_regra=%d);",id_sensor, id_regra);
    strcat(teste, str);
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        
      
        sprintf(str,"%d,%d,%d,%d,%d,%d,%d",id_sensor,id_regra, max,min, hora, min_max, min_min);
        strcat(query, str); 
        strcat(query,");");

        res=PQexec(*conn,query);
      return ( insert_ok(&res));

    }
  
    return 1;
}

int insere_constituicao_mote(PGconn **conn,int id_sensor, int id_mote){
    char teste[MAX]= "select exists (select (id_sensor,id_mote) from sim.constituicao_mote where id_sensor=";
    char query[MAX]="INSERT INTO sim.constituicao_mote (id_sensor, id_mote, data ) VALUES (";
    char str[30], data[20];
    time_t t;
    struct tm tm;
    

    PGresult *res;

    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min);

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d and id_mote=%d);",id_sensor, id_mote);
    strcat(teste, str);
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        
      
        sprintf(str,"%d,%d,",id_sensor,id_mote);
        strcat(query, str);
        strcat(query,data); 
        strcat(query,");");

        res=PQexec(*conn,query);
        
      return ( insert_ok(&res));

    }
  
    return 1;
}
int insere_atuacao(PGconn **conn, int id_atuador,int id_divisao){

    char teste[MAX]= "select exists (select (id_divisao,id_atuador) from sim.atuacao where id_divisao=";
    char query[MAX]="INSERT INTO sim.atuacao(id_divisao, id_atuador, data ) VALUES (";
    char str[30], data[20];
    time_t t;
    struct tm tm;
    PGresult *res;


    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min);

    /*ver se os dados já foram inseridos uma vez na base de dados*/
    sprintf(str,"%d and id_atuador=%d);",id_divisao, id_atuador);
    strcat(teste, str);
    
    res=PQexec(*conn,teste); 

    if(not_retrieve(&res))
        return 0;    
    
    /*f=false*/
    if(!strcmp(PQgetvalue(res,0,0),"f") ) {

        PQclear(res);        
        
      
        sprintf(str,"%d,%d,",id_divisao, id_atuador);
        strcat(query, str);
        strcat(query,data); 
        strcat(query,");");

        res=PQexec(*conn,query);
      return ( insert_ok(&res));

    }
  
    return 1;

}

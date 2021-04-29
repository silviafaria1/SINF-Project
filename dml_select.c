#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>

#define MAX 500

int get_max(PGconn **conn,int id_sensor, int id_regra) {

    char str1[25];
    char query[MAX] = "SELECT max FROM sim.Depende WHERE id_sensor = ";
    PGresult *res;
    int max;

    sprintf(str1,"%d and id_regra=%d ;",id_sensor,id_regra);
    strcat(query, str1);

    res= PQexec(*conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        puts( PQresultErrorMessage(res));
        return 0;
    }
    
    max=atoi(PQgetvalue(res,0,0));
    PQclear(res);

    return max;
}

int getmin(PGconn **conn,int id_sensor, int id_regra) {

    char str1[25];
    char query [MAX]= "SELECT min FROM sim.Depende WHERE id_sensor = ";
    PGresult *res;
    int min;

    sprintf(str1,"%d and id_regra=%d ;",id_sensor,id_regra);
    strcat(query, str1);
    res = PQexec(*conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        puts( PQresultErrorMessage(res));
        return 0;
    }

    min=atoi(PQgetvalue(res,0,0));
    PQclear(res);

    return min;
  
}


int getmax_min(PGconn **conn,int id_sensor, int id_regra) {
    
    char str1[25];
    char query[MAX] = "SELECT min_max FROM sim.Depende WHERE id_sensor = ";
    PGresult *res;
    int min_max;
   
    sprintf(str1,"%d and id_regra=%d ;",id_sensor,id_regra);
    strcat(query, str1);
    res = PQexec(*conn, query);

    res = PQexec(*conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        puts( PQresultErrorMessage(res));
        return 0;
    }
    

    min_max=atoi(PQgetvalue(res,0,0));
    PQclear(res);
    return min_max;

}

int getmin_min(PGconn **conn,int id_sensor, int id_regra) {

    char str1[25];
    char query[MAX] = "SELECT min_min FROM sim.Depende WHERE id_sensor = ";
    PGresult *res;
    int min_min;

    sprintf(str1,"%d and id_regra=%d ;",id_sensor,id_regra);
    strcat(query, str1);
    res = PQexec(*conn, query);

    res = PQexec(*conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        puts( PQresultErrorMessage(res));
        return 0;
    }
    
    min_min=atoi(PQgetvalue(res,0,0));
    PQclear(res);
    return min_min;
}

int get_h(PGconn **conn,int id_sensor, int id_regra) {

    char str1[25];
    char query [MAX]= "SELECT hora FROM sim.Depende WHERE id_sensor = ";
    PGresult *res;
    int get_h;

    sprintf(str1,"%d and id_regra=%d ;",id_sensor,id_regra);
    strcat(query, str1);
    res = PQexec(*conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        puts( PQresultErrorMessage(res));
        return 0;
    }
    

    get_h=atoi(PQgetvalue(res,0,0));
    PQclear(res);
    return get_h;
}

int get_potencia(PGconn **conn,int *id_sensor, int *id_regra) {

    char str1[25];
    char query [MAX];
    PGresult *res;
    int p=0,i;


    for(i=0;i<7;i++){   

        sprintf(query,"SELECT max FROM sim.Depende WHERE id_sensor = ");
        sprintf(str1,"%d and id_regra=%d ;",id_sensor[i],id_regra[i]);
        strcat(query, str1);
        res = PQexec(*conn, query);

        if (PQresultStatus(res) != PGRES_TUPLES_OK){
            puts( PQresultErrorMessage(res));
            return 0;
        }
        

        p = (atoi(PQgetvalue(res,0,0)) )*(3*230) + p;
        PQclear(res);

        
    }

    return p;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>





int cria_atuador_estado(PGconn **conn){

  
    PGresult *res;

    res= PQexec( *conn, " CREATE TABLE IF NOT EXISTS sim.Atuador_Estado (\
    id SERIAL PRIMARY KEY, \
    data TIMESTAMP,\
    estado BOOLEAN,\
    id_atuador INTEGER NOT NULL,\
    FOREIGN KEY ( id_atuador) REFERENCES sim.Atuador(id) ON UPDATE CASCADE ON DELETE CASCADE); ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    

    
    return 1;

}
int cria_casa(PGconn **conn){
  

    PGresult *res;
    res= PQexec( *conn, " CREATE TABLE IF NOT EXISTS sim.Casa(\
    id INTEGER PRIMARY KEY,\
    nome VARCHAR(128)\
    );\
    ");



    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);

return 1;

}
int cria_divisao(PGconn **conn){


    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Divisao(\
    id INTEGER  PRIMARY KEY,\
    nome VARCHAR(128),\
    id_casa INTEGER  NOT NULL,\
    id_mote INTEGER  NOT NULL UNIQUE,\
    FOREIGN KEY ( id_casa) REFERENCES sim.Casa(id) ON UPDATE CASCADE ON DELETE CASCADE,\
    FOREIGN KEY ( id_mote) REFERENCES sim.Mote(id) ON UPDATE CASCADE ON DELETE CASCADE\
    );");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);


return 1;

}
int cria_mote(PGconn **conn){

    PGresult *res;
    res= PQexec( *conn, " CREATE TABLE IF NOT EXISTS sim.Mote(\
    id INTEGER  PRIMARY KEY,\
    numero INTEGER,\
    num_sensores INTEGER DEFAULT 4 \
    );   ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);   
    return 1;

}
int cria_sensor_leitura(PGconn **conn){

    PGresult *res;

    res= PQexec( *conn, " CREATE TABLE IF NOT EXISTS sim.Sensor_Leitura(\
    id SERIAL PRIMARY KEY, \
    data TIMESTAMP,\
    leitura VARCHAR(128),\
    id_sensor INTEGER NOT NULL,\
    FOREIGN KEY ( id_sensor) REFERENCES sim.Sensor(id) ON UPDATE CASCADE ON DELETE CASCADE); ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    

    
    return 1;    
}

int cria_constituicao_mote(PGconn **conn){
    

    PGresult *res;

    res= PQexec( *conn, " CREATE TABLE IF NOT EXISTS sim.Constituicao_Mote(\
    id_mote INTEGER NOT NULL,\
    id_sensor INTEGER NOT NULL ,\
    data TIMESTAMP,\
    PRIMARY KEY ( id_mote, id_sensor),\
    FOREIGN KEY ( id_mote) REFERENCES sim.Mote(id) ON UPDATE CASCADE ON DELETE CASCADE,\
    FOREIGN KEY ( id_sensor) REFERENCES sim.Sensor(id) ON UPDATE CASCADE ON DELETE CASCADE ); ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_sensor(PGconn **conn){
        
    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Sensor(\
    id INTEGER   PRIMARY KEY,\
    nome VARCHAR(128),\
    tipo VARCHAR(128));");


    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_regra(PGconn **conn){
        
    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Regra(\
    id INTEGER  PRIMARY KEY,\
    numero INTEGER);");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_sobre(PGconn **conn){
        
    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Sobre(\
    id_atuador INTEGER NOT NULL ,\
    id_regra INTEGER NOT NULL, \
    data TIMESTAMP,\
    PRIMARY KEY ( id_atuador,  id_regra, data),\
    FOREIGN KEY ( id_atuador) REFERENCES sim.Atuador(id) ON UPDATE CASCADE ON DELETE CASCADE,\
    FOREIGN KEY ( id_regra) REFERENCES sim.Regra(id) ON UPDATE CASCADE ON DELETE CASCADE\
    );");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_atuador(PGconn **conn){

    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Atuador(\
    id INTEGER PRIMARY KEY,\
    nome VARCHAR(128),\
    tipo VARCHAR(128));");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_depende(PGconn **conn){
    
    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Depende(\
    id_sensor INTEGER NOT NULL,\
    id_regra INTEGER NOT NULL, \
    max INTEGER,\
    min INTEGER,\
    hora INTEGER,\
    min_max INTEGER,\
    min_min INTEGER,\
    PRIMARY KEY ( id_sensor, id_regra),\
    FOREIGN KEY ( id_sensor) REFERENCES sim.Sensor(id) ON UPDATE CASCADE ON DELETE CASCADE,\
    FOREIGN KEY ( id_regra) REFERENCES sim.Regra(id) ON UPDATE CASCADE ON DELETE CASCADE); ");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}

int cria_atuacao(PGconn **conn){
    


    PGresult *res;
    res= PQexec( *conn, "CREATE TABLE IF NOT EXISTS sim.Atuacao(\
    id_atuador INTEGER NOT NULL,\
    id_divisao INTEGER NOT NULL, \
    data TIMESTAMP,\
    PRIMARY KEY ( id_divisao, id_atuador, data),\
    FOREIGN KEY ( id_atuador) REFERENCES sim.Atuador(id) ON UPDATE CASCADE ON DELETE CASCADE,\
    FOREIGN KEY ( id_divisao) REFERENCES sim.Divisao(id) ON UPDATE CASCADE ON DELETE CASCADE);");

    if(PQresultStatus(res)!= PGRES_COMMAND_OK)
        return 0;

    PQclear(res);
    return 1;

}




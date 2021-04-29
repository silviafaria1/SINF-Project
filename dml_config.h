/*
    4/05/2019
    Autor:  Mafalda Santos; Inês Soares; Sílvia Faria
    POPULAR BASE DE DADOS
*/

#ifndef DML_CONFIG_H_
#define DML_CONFIG_H_

#include <postgresql/libpq-fe.h>

int not_retrieve(PGresult **res);
int insert_ok(PGresult **res);
int insere_casa(PGconn **conn, int id, char *nome_casa);
int insere_mote(PGconn **conn,int id, int n_mote, int n_sensores);
int insere_divisao(PGconn **conn, int id_casa,int id, int id_mote, char *divisao);
int insere_sensor(PGconn **conn, int id, char *nome_sensor, char *tipo_sensor);
int insere_atuador(PGconn **conn, int id, char *nome_atuador, char *tipo_atuador);
int insere_regras(PGconn **conn, int id_sensor, int id_regra, int max, int min);
int insere_num_regras(PGconn **conn,int id, int n_regra);
int insere_regra_jardim_hora(PGconn **conn, int id_sensor, int id_regra, int max, int min, int hora, int min_max, int min_min);
int insere_constituicao_mote(PGconn **conn,int id_sensor, int id_mote);
int insere_atuacao(PGconn **conn,int id_atuador, int id_divisao);
#endif

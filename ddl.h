/*
    12/03/2019
    Autor:  Mafalda Santos; Inês Soares; Sílvia Faria
    Programa capaz de indicar a DDL, minutos e segundos atuais.
*/

#ifndef DDL_H_
#define DDL_H_

#include <postgresql/libpq-fe.h>


int cria_atuador_estado( PGconn **conn);
int cria_casa( PGconn **conn);
int cria_divisao( PGconn **conn);
int cria_mote( PGconn **conn);
int cria_constituicao_mote( PGconn **conn);
int cria_sensor( PGconn **conn);
int cria_regra( PGconn **conn);
int cria_atuador( PGconn **conn);
int cria_depende( PGconn **conn);
int cria_atuacao( PGconn **conn);
int cria_sobre (PGconn **conn);
int cria_sensor_leitura(PGconn **conn);



#endif


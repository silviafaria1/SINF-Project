#ifndef HISTORICO_H_
#define HISTORICO_H_

#include <postgresql/libpq-fe.h>
#include "motes.h"

int insert_ok_3(PGresult **res);
int insere_historico_atuador( PGconn **conn,Mote *x,int id);
int insere_sobre(PGconn ***conn,int id_regra, int id_atuador);
int insere_historico_atuador_primeiro( PGconn **conn,Mote *x, int id);


#endif

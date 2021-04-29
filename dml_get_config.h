/*
    4/05/2019
    Autor:  Mafalda Santos; Inês Soares; Sílvia Faria
   GET configurações e regras
*/


#ifndef DML_GET_CONFIG_H_
#define DML_GET_CONFIG_H_

#include <postgresql/libpq-fe.h>
#include "motes.h"


int not_retrieve_2(PGresult **res);
int get_id(PGconn **conn,Mote *x);


#endif

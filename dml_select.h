#ifndef DML_SELECT_H_
#define DML_SELECT_H_

#include <postgresql/libpq-fe.h>

int get_max(PGconn **conn,int id_sensor, int id_regra);
int getmin(PGconn **conn,int id_sensor, int id_regra);
int getmax_min(PGconn **conn,int id_sensor, int id_regra);
int getmin_min(PGconn **conn,int id_sensor, int id_regra);
int get_h(PGconn **conn,int id_sensor, int id_regra);
int get_potencia(PGconn **conn,int *id_sensor, int *id_regra);
#endif

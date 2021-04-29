#ifndef SET_SENSORES_H_
#define SET_SENSORES_H_
#include "motes.h"
#include <postgresql/libpq-fe.h>


/*indica o tipo de divisao
    Cozinha - Mote 1 -1
    Quarto 1 - Mote 2 -2
    Quarto 2 - Mote 3 - 2
    Sala - Mote 4 - 3
    Jardim - Mote 5 -4
    Piscina - Mote 6 -5 
    WC - Mote 7 -6

*/

/*passagem dos valores decimais para os valores reais usando as
fórmulas do TelosB*/
int conversao_valores_reais(PGconn **conn, Mote *x, int id);
int insere_historico_sensor( PGconn ***conn,Mote **x,int id);
int insert_ok_4(PGresult **res);




#endif /*SET_SESORES_H*/

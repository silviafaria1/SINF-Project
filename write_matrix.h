#ifndef WRITE_MATRIX_H_
#define WRITE_MATRIX_H_

#include "motes.h"
#include "set_atuadores.h"

/*imprime a matrix com o estado atual dos atuadores em cada divisão*/
void print_matrix(Mote *cozinha, Mote *quarto1, Mote *quarto2, Mote *sala, Mote *wc, Mote *jardim, Mote *piscina);

#endif

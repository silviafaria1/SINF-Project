#ifndef SET_ATUADORES_H_
#define SET_ATUADORES_H_

#include "motes.h"

/*Atualização dos atuadores em função do tipo da divisao*/

void set_anterior(Mote **x, int acerta[7]);
void set_quarto_sala(Mote *x, float l_max, float l_min, float h, float t_max, float t_min);
void set_jardim(Mote *x, float l_max, float l_min, float h, int hora, int minutos_max, int minutos_min);
void set_piscina(Mote *piscina, Mote *jardim, float l_max, float l_min, float t_max, float t_min);
void set_cozinha(Mote *x, float h);
void set_wc(Mote *x, float t_max, float t_min);
void verifica_pot(Mote *COZINHA, Mote *WC, Mote *PISCINA, Mote *JARDIM, Mote *SALA, Mote *QUARTO,Mote *QUARTO2, float p_max);
#endif /*SET_ATUADORES_H*/
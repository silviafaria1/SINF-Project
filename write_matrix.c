#include <stdio.h>
#include "set_atuadores.h"
#include "motes.h"

void print_matrix(Mote *cozinha, Mote *quarto1, Mote *quarto2, Mote *sala, Mote *wc, Mote *jardim, Mote *piscina){
    int coz_hum_green=0, coz_hum_red=0, coz_pot_green=0, coz_pot_red=0;
    int q1_aquece_green=0, q1_aquece_red=0, q1_arrefece_green=0, q1_arrefece_red=0, q1_hum_green=0, q1_hum_red=0, q1_per_green=0, q1_per_red=0, q1_pot_green=0, q1_pot_red=0;
    int q2_aquece_green=0, q2_aquece_red=0, q2_arrefece_green=0, q2_arrefece_red=0, q2_hum_green=0, q2_hum_red=0, q2_per_green=0, q2_per_red=0, q2_pot_green=0, q2_pot_red=0;
    int sala_aquece_green=0, sala_aquece_red=0, sala_arrefece_green=0, sala_arrefece_red=0, sala_hum_green=0, sala_hum_red=0, sala_per_green=0, sala_per_red=0, sala_pot_green=0, sala_pot_red=0;
    int wc_aquece_green=0, wc_aquece_red=0, wc_arrefece_green=0, wc_arrefece_red=0, wc_pot_green=0, wc_pot_red=0;
    int jardim_luz_green=0, jardim_luz_red=0, jardim_pot_green=0, jardim_pot_red=0, jardim_rega_green=0, jardim_rega_red=0;
    int piscina_aquece_green=0, piscina_aquece_red=0, piscina_luz_green=0, piscina_luz_red=0, piscina_pot_green=0, piscina_pot_red=0;
    int s_coz_hum=0, s_q1_hum=0, s_q2_hum=0, s_sala_hum=0;
    int s_coz_pot=0, s_q1_pot=0, s_q2_pot=0, s_wc_pot=0, s_jardim_pot=0, s_piscina_pot=0, s_sala_pot=0;
    int s_q1_temp=0, s_q2_temp=0, s_sala_temp=0, s_wc_temp=0, s_piscina_temp=0;
    int s_q1_luz=0, s_q2_luz=0, s_sala_luz=0, s_jardim_luz=0, s_piscina_luz=0;
    
    
    if(cozinha->desumidificador){   //ligar desumidificador->VERDE
        coz_hum_red=0;
        coz_hum_green=255;
    }
    else{   //desligar desumidificador->VERMELHO
        coz_hum_red=255;
        coz_hum_green=0;
    }
    if((cozinha->pot_excedida)){   //pode ligar eletrodomesticos->VERDE
        coz_pot_red=0;
        coz_pot_green=150;
    }
    else{  //nao pode ligar eletrodomesticos->VERMELHO
        coz_pot_red=150;
        coz_pot_green=0;
    }
    if(quarto1->persiana){   //abre persiana->VERDE
        q1_per_red=0;
        q1_per_green=255;
    }
    else{  //fecha persiana->VERMELHO
        q1_per_red=255;
        q1_per_green=0;
    }
    if(quarto1->desumidificador){   //ligar desumidificador->VERDE
        q1_hum_red=0;
        q1_hum_green=150;
    }
    else{   //desligar desumidificador->VERMELHO
        q1_hum_red=150;
        q1_hum_green=0;
    }
    if(quarto1->aquece){   //ligar aquecedor->VERDE
        q1_aquece_red=0;
        q1_aquece_green=255;
    }
    else{  //desligar aquecedor->VERMELHO
        q1_aquece_red=255;
        q1_aquece_green=0;
    }
    if(quarto1->arrefece){   //ligar ar condicionado->VERDE
        q1_arrefece_red=0;
        q1_arrefece_green=150;
    }
    else{  //desligar ar condicionado->VERMELHO
        q1_arrefece_red=150;
        q1_arrefece_green=0;
    }
    
    if((quarto1->pot_excedida)){   //pode ligar eletrodomesticos->VERDE
        q1_pot_red=0;
        q1_pot_green=255;
    }
    else{  //nao pode ligar eletrodomesticos->VERMELHO
        q1_pot_red=255;
        q1_pot_green=0;
    }
    if(quarto2->persiana){   //abre persiana->VERDE
        q2_per_red=0;
        q2_per_green=255;
    }
    else{  //fecha persiana->VERMELHO
        q2_per_red=255;
        q2_per_green=0;
    }
    if(quarto2->desumidificador){   //ligar desumidificador->VERDE
        q2_hum_red=0;
        q2_hum_green=150;
    }
    else{   //desligar desumidificador->VERMELHO
        q2_hum_red=150;
        q2_hum_green=0;
    }
    if(quarto2->aquece){   //ligar aquecedor->VERDE
        q2_aquece_red=0;
        q2_aquece_green=255;
    }
    else{  //desligar aquecedor->VERMELHO
        q2_aquece_red=255;
        q2_aquece_green=0;
    }
    if(quarto2->arrefece){   //ligar ar condicionado->VERDE
        q2_arrefece_red=0;
        q2_arrefece_green=150;
    }
    else{  //desligar ar condicionado->VERMELHO
        q2_arrefece_red=150;
        q2_arrefece_green=0;
    }
    
    if((quarto2->pot_excedida)){   //pode ligar eletrodomesticos->VERDE
        q2_pot_red=0;
        q2_pot_green=255;
    }
    else{  //nao pode ligar eletrodomesticos->VERMELHO
        q2_pot_red=255;
        q2_pot_green=0;
    }
    if(sala->persiana){   //abre persiana->VERDE
        sala_per_red=0;
        sala_per_green=255;
    }
    else{  //fecha persiana->VERMELHO
        sala_per_red=255;
        sala_per_green=0;
    }
    if(sala->desumidificador){   //ligar desumidificador->VERDE
        sala_hum_red=0;
        sala_hum_green=150;
    }
    else{   //desligar desumidificador->VERMELHO
        sala_hum_red=150;
        sala_hum_green=0;
    }
    if(sala->aquece){   //ligar aquecedor->VERDE
        sala_aquece_red=0;
        sala_aquece_green=255;
    }
    else{  //desligar aquecedor->VERMELHO
        sala_aquece_red=255;
        sala_aquece_green=0;
    }
    if(sala->arrefece){   //ligar ar condicionado->VERDE
        sala_arrefece_red=0;
        sala_arrefece_green=150;
    }
    else{  //desligar ar condicionado->VERMELHO
        sala_arrefece_red=150;
        sala_arrefece_green=0;
    }
    
    if((sala->pot_excedida)){   //pode ligar eletrodomesticos->VERDE
        sala_pot_red=0;
        sala_pot_green=255;
    }
    else{  //nao pode ligar eletrodomesticos->VERMELHO
        sala_pot_red=255;
        sala_pot_green=0;
    }
    if(wc->aquece){   //ligar aquecedor->VERDE
        wc_aquece_red=0;
        wc_aquece_green=255;
    }
    else{  //desligar aquecedor->VERMELHO
        wc_aquece_red=255;
        wc_aquece_green=0;
    }
    if(wc->arrefece){   //ligar ar condicionado->VERDE
        wc_arrefece_red=0;
        wc_arrefece_green=150;
    }
    else{  //desligar ar condicionado->VERMELHO
        wc_arrefece_red=150;
        wc_arrefece_green=0;
    }
    
    if((wc->pot_excedida)){   //pode ligar eletrodomesticos->VERDE
        wc_pot_red=0;
        wc_pot_green=255;
    }
    else{  //nao pode ligar eletrodomesticos->VERMELHO
        wc_pot_red=255;
        wc_pot_green=0;
    }
    if(jardim->rega){   //ligar a rega->VERDE
        jardim_rega_red=0;
        jardim_rega_green=255;
    }
    else{   //desligar rega->VERMELHO
        jardim_rega_red=255;
        jardim_rega_green=0;
    }
    if(jardim->iluminacao){   //ligar a luz->VERDE
        jardim_luz_red=0;
        jardim_luz_green=150;
    }
    else{   //desligar luz->VERMELHO
        jardim_luz_red=150;
        jardim_luz_green=0;
    }
    if((jardim->pot_excedida)){   //pode ligar aparelhos que consomem potencia->VERDE
        jardim_pot_red=0;
        jardim_pot_green=255;
    }
    else{  //nao pode ligar aparelhos que consomem potencia->VERMELHO
        jardim_pot_red=255;
        jardim_pot_green=0;
    }
    if(piscina->aquece){   //ligar aquecedor da agua->VERDE
        piscina_aquece_red=0;
        piscina_aquece_green=255;
    }
    else{  //desligar aquecedor da agua->VERMELHO
        piscina_aquece_red=255;
        piscina_aquece_green=0;
    }
        if(piscina->iluminacao){   //ligar a luz->VERDE
        piscina_luz_red=0;
        piscina_luz_green=150;
    }
    else{   //desligar luz->VERMELHO
        piscina_luz_red=150;
        piscina_luz_green=0;
    }
    if((piscina->pot_excedida)){   //pode ligar aparelhos aparelhos que consomem potencia->VERDE
        piscina_pot_red=0;
        piscina_pot_green=255;
    }
    else{  //nao pode ligar aparelhos que consomem potencia->VERMELHO
        piscina_pot_red=255;
        piscina_pot_green=0;
    }
    s_coz_hum= (int)(cozinha->humidade *2.55);
    s_q1_hum=(int)(quarto1->humidade *2.55);
    s_q2_hum=(int)(quarto2->humidade *2.55);
    s_sala_hum=(int)(sala->humidade *2.55);
    s_coz_pot=(int)(cozinha->corrente *5.1);
    s_q1_pot=(int)(quarto1->corrente * 5.1);
    s_q2_pot=(int)(quarto2->corrente *5.1);
    s_sala_pot=(int)(sala->corrente *5.1);
    s_wc_pot=(int)(wc->corrente *5.1);
    s_jardim_pot=(int)(jardim->corrente *5.1);
    s_piscina_pot=(int)(piscina->corrente *5.1);
    s_q1_temp=(int)(quarto1->temperatura *6.375);
    s_q2_temp=(int)(quarto2->temperatura *6.375);
    s_sala_temp=(int)(sala->temperatura *6.375);
    s_wc_temp=(int)(wc->temperatura *6.375);
    s_piscina_temp=(int)(piscina->temperatura *6.375);
    s_q1_luz=(int)(quarto1->luz / 14);
    s_q2_luz=(int)(quarto2->luz / 14);
    s_sala_luz=(int)(sala->luz / 14);
    s_jardim_luz=(int)(jardim->luz / 14);
    s_piscina_luz=(int)(piscina->luz / 14);
   
    printf("[[0,204,204],[0,204,204],[0,204,204],[0,204,204],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[%d,%d,0],[0,204,204],[236,127,3],[%d,%d,0],[%d,%d,0],[%d,%d,0],[236,127,3],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[%d,%d,0],[0,204,204],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[%d,%d,0],[%d,%d,0],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[%d,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[%d,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[%d,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[%d,%d,0],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[%d,%d,0],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[%d,%d,0],[%d,%d,0],[%d,%d,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,0,%d],[%d,0,0],[0,204,204],[236,127,3],[%d,0,0],[%d,%d,0],[236,127,3],[236,127,3],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[0,%d,0],[0,204,204],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[236,127,3],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[255,255,255],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[%d,%d,0],[0,0,%d],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[%d,0,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[0,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[132,132,132],[132,132,132],[132,132,132],[132,132,132],[255,255,255],[255,255,255],[240,186,123],[0,0,%d],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[%d,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[%d,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,0,%d],[%d,0,0],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[%d,0,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[%d,%d,0],[0,%d,0],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[0,%d,0],[240,186,123],[44,128,47],[44,128,47],[19,38,206],[19,38,206],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,204,204],[0,204,204],[0,204,204],[0,204,204],[255,255,255],[255,255,255],[240,186,123],[240,186,123],[240,186,123],[44,128,47],[44,128,47],[%d,%d,0],[0,%d,0],[44,128,47],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]\n", q1_per_red, q1_per_green, q1_arrefece_red, q1_arrefece_green, wc_aquece_red, wc_aquece_green, wc_arrefece_red, wc_arrefece_green, wc_pot_red, wc_pot_green, q1_hum_red, q1_hum_green, q1_pot_red, q1_pot_green, q1_aquece_red, q1_aquece_green, coz_hum_red, coz_hum_green, coz_pot_red, coz_pot_green, piscina_aquece_red, piscina_aquece_green, sala_per_red, sala_per_green, piscina_luz_red, piscina_luz_green, sala_hum_red, sala_hum_green, piscina_pot_red, piscina_pot_green,  sala_aquece_red, sala_aquece_green, q2_per_red, q2_per_green, q2_arrefece_red, q2_arrefece_green, sala_arrefece_red, sala_arrefece_green, q2_hum_red, q2_hum_green, q2_pot_red, q2_pot_green, sala_pot_red, sala_pot_green, q2_aquece_red, q2_aquece_green, jardim_rega_red, jardim_rega_green, jardim_luz_red, jardim_luz_green, jardim_pot_red, jardim_pot_green, s_q1_hum, s_q1_temp, s_wc_temp, s_wc_pot, s_wc_pot, s_q1_pot, s_q1_pot, s_q1_luz, s_coz_pot, s_coz_pot, s_coz_hum, s_piscina_temp, s_piscina_luz, s_sala_hum, s_piscina_pot, s_piscina_pot, s_sala_pot, s_sala_pot, s_q2_hum, s_q2_temp, s_sala_temp, s_q2_pot, s_q2_pot, s_q2_luz, s_sala_luz, s_jardim_pot, s_jardim_pot, s_jardim_luz);
   }

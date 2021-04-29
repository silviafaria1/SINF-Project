#include <stdio.h>
#include <time.h>

#include "motes.h"
#include "hora.h"


#define TAMB 25
#define P 0
#define  AQ 1
#define REGA 2
#define PER 3
#define ILU 4
#define DES 5
#define ARR 6

void set_anterior(Mote **x, int acerta[7]){



    if(acerta[0])
          (*x)->pot_excedida_ant=(*x)->pot_excedida;
    if(acerta[1])
         (*x)->aquece_ant=(*x)->aquece;
    if(acerta[2])
           (*x)->rega_ant=(*x)->rega;
    if(acerta[3])
          (*x)->persiana_ant=(*x)->persiana;
    if(acerta[4])
         (*x)->iluminacao_ant= (*x)->iluminacao;
    if(acerta[5])
        (*x)->desumidificador_ant=(*x)->desumidificador;
    if(acerta[6])
         (*x)->arrefece_ant=(*x)->arrefece;
}
void set_quarto_sala(Mote *x, float l_max, float l_min, float h, float t_max, float t_min){
    int v[7]={0};

    v[PER]=v[DES]=v[REGA]=v[ARR]=1;


    set_anterior(&x,v);
 

    if (x->luz<=l_min)
    {
        x->persiana=0; //FECHADA
    }
    else if ( (x->luz<l_max) && (x->luz > l_min))
    {
        x->persiana=1; //ABERTA
    }
    else
    {
        x->persiana=1;
    }
    

    if(x->humidade > h){
        x->desumidificador=1;
    }
    else
        x->desumidificador=0;

    if ( x->temperatura < t_min){
        x->aquece=1;
        x->arrefece=0;
    }
    else if ( x->temperatura > t_max)
    {
        x->aquece=0;
        x->arrefece=1;
    }
    else
    {
        x->aquece=0;
        x->arrefece=0;
    }




}

void set_wc(Mote *x, float t_max, float t_min){
    int v[7]={0};

    v[AQ]=v[ARR]=1;

    set_anterior(&x,v);


    if(x->temperatura < t_min){
        x->aquece=1;
        x->arrefece=0;
    }
    else if(x->temperatura > t_max){
        x->aquece=0;
        x->arrefece=1;
    }
    else
    {
        x->aquece=0;
        x->arrefece=0;
    }

    
}

void set_jardim(Mote *x, float l_max, float l_min, float h, int hora, int minutos_max, int minutos_min){
    int v[7]={0};

    v[ILU]=v[REGA]=1;
    set_anterior(&x,v);


    if (x->luz> l_max)
    {
        x->iluminacao=0;
    }
    else 
    {
        x->iluminacao=1;
    }

    if( ( x->humidade < h ) &&  ((get_hour()==hora) && (get_min()>=minutos_min) && (get_min()<=minutos_max))){
        x->rega=1;
    }
    else 
        x->rega=0;
    


}

void set_piscina(Mote *piscina, Mote *jardim, float l_max, float l_min, float t_max, float t_min){
    int v[7]={0};

    v[ILU]=v[AQ]=1;
    set_anterior(&piscina,v);


    if(piscina->luz > l_max)
        piscina->iluminacao=0;
    else
        piscina->iluminacao=1;

    if(jardim->temperatura > TAMB){

        if (piscina->temperatura > t_max){
            piscina->aquece=0;
        }
        else if (piscina->temperatura < t_min){
            piscina->aquece=1;
        }
        else 
            piscina->aquece=0;
    }
    else
        piscina->aquece=0;
    

    
}

void set_cozinha(Mote *x, float h){
    int v[7]={0};

    v[DES]=1;

    set_anterior(&x,v);
   

    if(x->humidade > h){
        x->desumidificador=1;
    }
    else
        x->desumidificador=0;

}

void verifica_pot(Mote *COZINHA, Mote *WC, Mote *PISCINA, Mote *JARDIM, Mote *SALA, Mote *QUARTO,Mote *QUARTO2, float p_max){
    int v[7]={0};
    float p;
    p=COZINHA->potencia+WC->potencia+PISCINA->potencia+JARDIM->potencia+QUARTO->potencia+SALA->potencia+QUARTO2->potencia;
    
    v[P]=1;
    set_anterior(&COZINHA,v);
    set_anterior(&WC,v);
    set_anterior(&PISCINA,v);
    set_anterior(&JARDIM,v);
    set_anterior(&QUARTO,v);
    set_anterior(&QUARTO2,v);
    set_anterior(&SALA,v);



    if(p>p_max) {
        COZINHA->pot_excedida=1;
        WC->pot_excedida=1;
        PISCINA->pot_excedida=1;
        JARDIM->pot_excedida=1;
        QUARTO->pot_excedida=1;
        SALA->pot_excedida=1;
        QUARTO2->pot_excedida=1;
    }
    else {
        COZINHA->pot_excedida=0;
        WC->pot_excedida=0;
        PISCINA->pot_excedida=0;
        JARDIM->pot_excedida=0;
        QUARTO->pot_excedida=0;
        SALA->pot_excedida=0;
        QUARTO2->pot_excedida=0;
    }    

}

#ifndef MOTES_H_
#define MOTES_H_

typedef struct Motes{
/*estruturar representa os motes*/

    int mote_id, divisao_id, casa_id;

/*sensores_id = sensores_ativos = [luz,corrente,temperatura,humdidade]
atuadores_id= atuadores_ativos= [aquece,arrefece,persinana, desumidificador, 
                                 iluminacao, rega, pot_excedida]*/

    int sensores_id[4],atuadores_id[7],sensores_ativos[4],atuadores_ativos[7];

   
    float luz, corrente, temperatura, humidade,potencia; /*sensores*/
    int aquece, arrefece, persiana, desumidificador, iluminacao, rega, pot_excedida;
    int aquece_ant, arrefece_ant, persiana_ant, desumidificador_ant, iluminacao_ant, rega_ant, pot_excedida_ant;

}Mote;

#endif




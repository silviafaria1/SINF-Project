/*
    12/03/2019
    Autor:  Mafalda Santos; Inês Soares; Sílvia Faria
    Programa capaz de indicar a hora, minutos e segundos atuais.
*/

#ifndef HORA_H_
#define HORA_H_



/*retorna um apontador para uma estrutura com o tempo atual*/
 struct tm  * tempo(void);

/*retorna o minuto atual*/
int get_min(void);
/*retorna o segundo atual*/
int get_sec(void);
/*retorna a hora atual*/
int get_hour(void);



#endif
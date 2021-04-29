
#include <time.h>



/*retorna um apontador para uma estrutura com o tempo atual*/
 struct tm  * tempo(void){
    
    time_t curtime;
    struct tm  *loc_time;


    curtime=time(NULL);
    loc_time=localtime(&curtime);

    return loc_time;
 }

/*retorna o minuto atual*/
int get_time(void){

    struct tm  *loc_time;

    loc_time=(tempo());

    return loc_time->tm_min;
}
/*retorna o segundo atual*/
int get_sec(void){

    struct tm  *loc_time;

    loc_time=(tempo());

    return loc_time->tm_sec;
}
/*retorna a hora atual*/
int get_hour(void){

    struct tm  *loc_time;

    loc_time=(tempo());

    return loc_time->tm_hour;
}
/*retorna o minuto atual*/
int get_min(void){

    struct tm  *loc_time;

    loc_time=(tempo());

    return loc_time->tm_min;
}


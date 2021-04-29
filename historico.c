#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "motes.h"
#include <time.h>

#define MAX 500




int insert_ok_3(PGresult **res){

    if(PQresultStatus(*res)!= PGRES_COMMAND_OK){
        PQclear(*res);
      
        return 0;
    }
    PQclear(*res);
    return 1;
}

int insere_sobre(PGconn ***conn,int id_regra, int id_atuador){

    char query[MAX]="insert into sim.Sobre (id_regra, id_atuador, data) values (";
    PGresult *res;
    char str[10], data[25];
    time_t t;
    struct tm tm;

    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min, tm.tm_sec);

        
    sprintf(str,"%d,%d,",id_regra,id_atuador);   
    strcat(query, str);
    strcat(query, data); 
    strcat(query,");");
    res=PQexec(*(*conn),query);

      return (insert_ok_3(&res));
     
}


int insere_historico_atuador( PGconn **conn,Mote *x, int id){

    char query[MAX]="insert into sim.atuador_estado(id_atuador, estado, data) values (";
    PGresult *res;
    char str[10], data[25];
    time_t t;
    struct tm tm;
    int estado=0, ok=0,i;


    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);

    sprintf(str,"%d,",id);
    strcat(query, str);
    
 
    
    if(id == 1){ 

        estado = x->desumidificador;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
        


            
            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;

            ok=insere_sobre( &(conn),15,1);
            if(!ok)
                return 0;
      
    }
   else if (id == 2){
        estado = x->pot_excedida;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 


            
            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
   
            ok=insere_sobre( &(conn),16,2);
            if(!ok)
                return 0;
        
        
    }
    else if (id == 3){
        estado = x->persiana;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
                 

            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),4,3);

            if(!ok)
                return 0;           
        }
    
    else if (id == 4){
        estado = x->desumidificador;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;

            ok=insere_sobre( &(conn),6,4);

            if(!ok)
                return 0;           
        
    }
    else if (id == 5){
        estado = x->aquece;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;

            ok=insere_sobre( &(conn),5,5);

            if(!ok)
             return 0;            
        
    }
    else if (id == 6){
        estado = x->arrefece;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


            res=PQexec(*conn,query);

            if(!insert_ok_3(&res))
                 return 0;
            ok=insere_sobre( &(conn),5,6);

            if(!ok)
                    return 0;       
        
    }
    else if (id == 7){
        estado = x->pot_excedida;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

        
        res=PQexec(*conn,query);
        if(!insert_ok_3(&res))
             return 0;
        ok=insere_sobre( &(conn),17,7);
        if(!ok)
              return 0;
        
    }
    else if (id == 8){
        estado = x->persiana;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

    
           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),18,8);
            if(!ok)
                return 0;
          
        
    }
    else if (id == 9){
        estado = x->desumidificador;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),9,9);

            if(!ok)
                return 0;         
        
    }
    else if (id == 10){
        estado = x->aquece;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

          
            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),8,10);
            if(!ok)
                return 0;
            
        
    }
    else if (id == 11){
        estado = x->arrefece;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         
            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),8,11);
            if(!ok)
                return 0;
           
        
    }
    else if (id == 12){
        estado = x->pot_excedida;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         
 

            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
           ok=insere_sobre( &(conn),18,12);
           if(!ok)
            return 0;
           
        
    }
    else if (id == 13){
        estado = x->persiana;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


        res=PQexec(*conn,query);
        if(!insert_ok_3(&res))
                return 0;
         ok=insere_sobre( &(conn),1,13);
         if(!ok)
            return 0;
         
        
    }
    else if (id == 14){
        estado = x->desumidificador;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


          res=PQexec(*conn,query);
         if(!insert_ok_3(&res))
                return 0;
           ok=insere_sobre( &(conn),3,14);
           if(!ok)
            return 0;
          
        
    }
   else if (id == 15){
        estado = x->aquece;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


           
         res=PQexec(*conn,query);
         if(!insert_ok_3(&res))
                return 0;
          ok=insere_sobre( &(conn),2,15);
          if(!ok)
            return 0;
        
        
    }
    else if (id == 16){
        estado = x->arrefece;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

          res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
           ok=insere_sobre( &(conn),2,16);
           if(!ok)
            return 0;
      
        
    }
    else if (id == 17){
        estado = x->pot_excedida;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

          res=PQexec(*conn,query);
         if(!insert_ok_3(&res))
                return 0;
           ok=insere_sobre( &(conn),19,17);
           if(!ok)
            return 0;
        
        
    }
    else if (id == 18){
        estado = x->rega;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         
  

        res=PQexec(*conn,query);
        if(!insert_ok_3(&res))
                return 0;
         ok=insere_sobre( &(conn),12,18);
         if(!ok)
            return 0;
        
        
    }
    else if (id == 19){
        estado = x->iluminacao;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

         res=PQexec(*conn,query);
          if(!insert_ok_3(&res))
                return 0;
          ok=insere_sobre( &(conn),11,19);
          if(!ok)
            return 0;
           
        
    }
    else if (id == 20){
        estado = x->pot_excedida;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         


          res=PQexec(*conn,query);
        if(!insert_ok_3(&res))
                return 0;
           ok=insere_sobre( &(conn),20,20);
           if(!ok)
            return 0;
     
        
    }
    else if (id == 21){
        estado = x->aquece;

        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),14,21);
            if(!ok)
                return 0;
       
        
    }
    else if (id == 22){
        estado = x->iluminacao;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

            res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
                return 0;
            ok=insere_sobre( &(conn),13,22);
            if(!ok)
                return 0;
       
        
    }
    else if (id == 23){
        estado = x->pot_excedida;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
            return 0;
            ok=insere_sobre( &(conn),21,23);
            if(!ok)
                return 0;
         
        
    }
    else if (id == 24){
        estado = x->aquece;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 

           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
            return 0;
            ok=insere_sobre( &(conn),10,24);
            if(!ok)
                return 0;
        
        
    }
    else if (id == 25){
        estado = x->arrefece;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         

           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
            return 0;
            ok=insere_sobre( &(conn),10,25);
            if(!ok)
                return 0;
 
        
    }
    else{
        estado = x->pot_excedida;
        if(estado)
            {
                strcat(query,"true,");
                
            }
            else
            {
                strcat(query,"false,");
            }
            

        strcat(query, data);    
        strcat(query,");"); 
         
           res=PQexec(*conn,query);
            if(!insert_ok_3(&res))
            return 0;
            ok=insere_sobre( &(conn),22,26);
            if(!ok)
                return 0;
          
        
    }
    return 1;

 


}
int insere_historico_atuador_primeiro( PGconn **conn,Mote *x, int id){

    char query[MAX]="insert into sim.atuador_estado(id_atuador, estado, data) values (";
    PGresult *res;
    char str[10], data[25];
    time_t t;
    struct tm tm;
    int estado=0, ok=0,i;


    t=time(NULL);
    tm=*localtime(&t);
    sprintf(data,"'%d-%d-%d %d:%d:%d'",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);

    sprintf(str,"%d,false,",id);
    strcat(query, str);
    strcat(query, data);    
    strcat(query,");"); 
    res=PQexec(*conn,query);
    

    if(!insert_ok_3(&res))
        return 0;
   
    return 1;

    
}

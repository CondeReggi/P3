/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include "../include/asignacion.h"
#include "../include/pila.h"
#include "../include/utils.h"
#include <cstddef>
#include <stdio.h>


//Proponen los hospitales
Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{

    printf ("M vale:%d\n",n); 

    Pila /* Gordon */ freeHospital = crear_pila();
    Asignacion result = crear_asignacion(); //Creo result para posteriormente llenarlo con matches
    nat current; 
    nat current_student;
    int* next = new int[m]; 
    nat* matches = new nat[n];
    nat** ranking = new nat*[n];

    for(nat i = 0; i < n; i++){ 
      ranking[i] = new nat[n];
      for(nat j = 0; j < m; j++){ 
        ranking[i][ePrefs[i][j]] = j;
      }
    }

    for (nat i = 1; i <= m; i++) { //Pongo de 1 a M no de 0 a M-1
      apilar(i, freeHospital);
      next[i - 1] = 0;
    }
    for(nat i = 0; i < n; i++){
      matches[i] = 0;
    }

    while(!es_vacia_pila(freeHospital)){
      current = cima(freeHospital);
      printf ("Current vale:%d\n", current); 
      current_student = hPrefs[current - 1][next[current - 1]];

      printf ("current_student vale:%d\n", current_student);
      next[current - 1] = next[current - 1] + 1;
      //printf ("current:%d\n",current); 
      //printf ("current_student:%d\n",current_student);
        
      if(matches[current_student] == 0){
        matches[current_student] = current - 1;
        desapilar(freeHospital);
        printf ("entre if - "); 
      }else if(ranking[current_student][current - 1] < ranking[current_student][matches[current_student]]){ //Aca el ranking tiene mayor prioruidad el estudiante de matches[current_student]
        desapilar(freeHospital);

        //Capaz no es asi

        apilar(matches[current_student], freeHospital);
        matches[current_student] = current - 1;
      
        printf ("entre else if - "); 
      }else{
        printf ("entre else - "); 
      }
    }

    for(nat i = 0; i < n; i++){ //Recorro y voy asignando, se supone en maches esta todo
      par *nuevo = new par;
      nuevo->eid = i;
      nuevo->hid = matches[i];
      insertar_par(*nuevo, result);
      delete(nuevo);
    }

    destruir_pila(freeHospital); //Elimino la cola

    for(nat i = 0; i < n; i++){
      delete[] ranking[i]; //Elimino todos antes
    }

    delete[] ranking; //Elimino el array de ranking
    delete[] matches; //Elimino el array de matches
    delete[] next; //Elimino el array de next
    
    return result; // se debe retornar algo de tipo asignacion
}

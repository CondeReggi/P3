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


//Proponen los hospitales
Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{
    Pila /* Gordon */ freeHospital = crear_pila();
    Asignacion result = crear_asignacion(); //Creo result para posteriormente llenarlo con matches
    nat current; nat current_student;
    nat* next; nat* matches;
    nat** ranking;

    for(nat i = 0; i < n; i++){ 
      for(nat j = 0; j < n; j++){ 
        ranking[i][ePrefs[i][j]] = j;
      }
    }

    for (nat i = 1; i <= m; i++) {
      apilar(i, freeHospital);
      next[i] = 1;
    }
    for(nat i = 0; i < n; i++){
      matches[i] = -1;
    }

    while(!es_vacia_pila(freeHospital)){
      current = cima(freeHospital);
      current_student = hPrefs[current][next[current]];
      next[current]++;

      if(matches[current_student] == -1){
        matches[current_student] = current;
        desapilar(freeHospital);

      }else if(ranking[current][current_student] < ranking[current][matches[current_student]]){
        desapilar(freeHospital);
        apilar(matches[current_student], freeHospital);
        matches[current_student] = current;
      }
    }

    for(int i = 0; i < n; i++){ //Recorro y voy asignando, se supone en maches esta todo
      par nuevo;
      nuevo.eid = i;
      nuevo.hid = matches[i];
      insertar_par(nuevo, result);
    }

    destruir_pila(freeHospital); //Elimino la cola
    delete(matches); //Elimino el array de matches
    return result; // se debe retornar algo de tipo asignacion
}



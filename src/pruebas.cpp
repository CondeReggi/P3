/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include "../include/asignacion.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/utils.h"
#include <cstddef>


//Proponen los hospitales
Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{
    Cola freeMen = crear_cola();

    //Cambios

    Pila /* Gordon */ freeHospital = crear_pila();
    nat current;
    nat current_student;

    nat** ranking;
    nat* next;
    nat* matches;

    Asignacion result = crear_asignacion(); //Creo result para posteriormente llenarlo con matches
    
    //si la ePref[i][j] es la j esima preferencia del i esimo estudiante
    //entonces ranking[i][j] devuelve que numero de preferencia tiene el estudiante sobre el hospital

    for(nat i = 0; i < n; i++){ 
      for(nat j = 0; j < n; j++){ 
        ranking[i][ePrefs[i][j]] = j;
      }
    }

    for (nat i = 0; i < m; i++) {
      apilar(i, freeHospital);
      next[i] = 1;
    }

    for(nat i = 0; i < n; i++){
      matches[i] = 0;
    }

    while(!es_vacia_pila(freeHospital)){
      current = cima(freeHospital);
      current_student = hPrefs[current][next[current]];

      if(matches[current_student] == 0){
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

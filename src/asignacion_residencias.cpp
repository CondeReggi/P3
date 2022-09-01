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
    nat current; 
    nat current_student;
    nat* next = new nat[m]; 
    nat* matches = new nat[n];
    nat** ranking = new nat*[n];

    for(nat i = 0; i < n; i++){ 
      for(nat j = 0; j < n; j++){ 
        ranking[i][ePrefs[i][j]] = j;
      }
    }

    for (nat i = 1; i <= m; i++) { //Pongo de 1 a M no de 0 a M-1
      apilar(i, freeHospital);
      next[i] = 1;
    }
    for(nat i = 0; i < n; i++){
      matches[i] = 0;
    }

    while(!es_vacia_pila(freeHospital)){
      current = cima(freeHospital);
      current_student = hPrefs[current][next[current]];
      next[current]++;

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
      par *nuevo = new par;
      nuevo->eid = i;
      nuevo->hid = matches[i] - 1;
      insertar_par(*nuevo, result);
      delete(nuevo);
    }

    destruir_pila(freeHospital); //Elimino la cola

    delete(ranking); //Elimino el array de ranking
    delete(matches); //Elimino el array de matches
    delete(next); //Elimino el array de next
    
    return result; // se debe retornar algo de tipo asignacion
}



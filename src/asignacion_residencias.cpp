/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include "../include/asignacion.h"
#include "../include/cola.h"
#include "../include/utils.h"
#include <cstddef>


//Proponen los hospitales
Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{
    Cola freeMen = crear_cola();
    nat current;
    nat current_hospital = 0;

    nat* matches; //Array de matches para index (numero hospital) tal match (numero hombre)

    Asignacion result = crear_asignacion(); //Creo result para posteriormente llenarlo con matches

    for(nat i = 0; i < m; i++){ 
      matches[i - 1] = 0; //Inicializo en 0 todos los matches para los hospitales
    }

    for(nat i = 0; i < n; i++){ 
      encolar(i, freeMen); //Pongo en la cola para que todos los hospitales esten libres en un principio
    }

    while(!es_vacia_cola(freeMen) && current_hospital <= n){ //Mientras hospitales dispoibles y hombres en el rango de cantidad de hombres
      current = frente(freeMen);

      if(matches[current_hospital] == 0){ //Si no esta asignada la mujer para el hombre dale que es tarde
			  matches[current_hospital] = current;
			  desencolar(freeMen);

		  }else if(hPrefs[current_hospital][current] < hPrefs[current_hospital][matches[current_hospital]]){ //Fijo prioridad del hospital
        nat ex_man = matches[current_hospital]; //Agarro a la persona y la encolo
        desencolar(freeMen);
        matches[current_hospital] = current;
        encolar((nat)ex_man , freeMen);
      }

      current_hospital++;
    }   

    for(int i = 0; i < n; i++){ //Recorro y voy asignando, se supone en maches esta todo
      par nuevo;
      nuevo.eid = i;
      nuevo.hid = matches[i];
      insertar_par(nuevo, result);
    }

    destruir_cola(freeMen); //Elimino la cola
    delete(matches); //Elimino el array de matches
    
    return result; // se debe retornar algo de tipo asignacion
}

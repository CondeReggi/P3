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

Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{
    Cola freeMen = crear_cola();
    nat current_man;
    nat current_hospital;
    nat* matches;

    Asignacion result = crear_asignacion();

    for(nat i = 1; i <= n; i++){ //Hay que llenar la pila con todos los hombres
      encolar(i, freeMen);
    }

    while(!es_vacia_cola(freeMen)){ //Mientras hombres dispoibles
      current_man = frente(freeMen);
      current_hospital = 1;

      if(matches[current_hospital] == 0){ //Si no esta asignada la mujer para el hombre dale que es tarde
			  matches[current_hospital] = current_man;
			  desencolar(freeMen);
		  }else if(ePrefs[current_hospital][current_man] < ePrefs[current_hospital][matches[current_hospital]]){ //Ek ranking este se supone que ya lo tengo es hPref y/o ePref
        nat ex_man = matches[current_hospital];
        desencolar(freeMen);
        matches[current_hospital] = current_man;
        encolar((nat)ex_man , freeMen);
      }
    }   

    for(int i = 0; i < n; i++){ //Recorro y voy asignando, se supone en maches esta todo
      // par nuevo = crear_par(i, matches[i]);
      par nuevo;
      nuevo.eid = i;
      nuevo.hid = matches[i];
      insertar_par(nuevo, result);
    }
    
    return result; // se debe retornar algo de tipo asignacion
}

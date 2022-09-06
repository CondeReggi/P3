#include "../include/asignacion_residencias.h"
#include "../include/asignacion.h"
#include "../include/pila.h"
#include "../include/utils.h"
#include <cstddef>
#include <stdio.h>

// Proponen los hospitales
Asignacion asignarResidencias(nat m, nat *C, nat n, nat **hPrefs, nat **ePrefs)
{
  Pila /* Gordon */ freeHospital = crear_pila();
  Asignacion result = crear_asignacion(); // Creo result para posteriormente llenarlo con matches
  nat current;
  nat current_student;
  int *next = new int[m];
  int *matches = new int[n];
  int **ranking = new int *[n];

  for (nat i = 0; i < n; i++)
  {
    ranking[i] = new int[n];
    for (nat j = 0; j < m; j++)
    {
      ranking[i][ePrefs[i][j]] = j;
    }
  }

  for (nat i = 0; i < m; i++)
  { 
    apilar(i, freeHospital);
    next[i] = 0;
  }
  for (nat i = 0; i < n; i++)
  {
    matches[i] = -1;
  }

  current = cima(freeHospital);
  while (!es_vacia_pila(freeHospital) && next[current] < (int)n)
  {
    current = cima(freeHospital);
    if(C[current] == 0){
      desapilar(freeHospital);
      continue;
    }

    current_student = hPrefs[current][next[current]];
    next[current] = next[current] + 1;
    if (matches[current_student] == -1)
    {
      matches[current_student] = current;
      C[current] = C[current] - 1;
    }
    else if (ranking[current_student][current] < ranking[current_student][matches[current_student]])
    { // Aca el ranking tiene mayor prioruidad el estudiante de matches[current_student]
      apilar(matches[current_student], freeHospital);
      C[matches[current_student]] = C[matches[current_student]] + 1;
      matches[current_student] = current;
      C[current] = C[current] - 1;
    }
  }

  for (int i = 0; i < (int)n; i++)
  { // Recorro y voy asignando, se supone en maches esta todo
    par *nuevo = new par;
    nuevo->eid = i;
    nuevo->hid = matches[i];
    insertar_par(*nuevo, result);
    delete (nuevo);
  }

  destruir_pila(freeHospital); // Elimino la cola

  for (nat i = 0; i < n; i++)
  {
    delete[] ranking[i]; // Elimino todos antes
  }

  delete[] ranking; // Elimino el array de ranking
  delete[] matches; // Elimino el array de matches
  delete[] next;    // Elimino el array de next

  return result; // se debe retornar algo de tipo asignacion
}
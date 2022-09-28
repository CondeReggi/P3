/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>
#include <cmath>

#include "../include/cronologia_consistente.h"
#include "../include/grafo.h"
#include "../include/lista.h"
#include "../include/lista_datos.h"
#include "../include/utils.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  int* array = new int[9999999];
  int* muere_o_nace = new int[9999999];
  for(int i = 0; i < (int)(2 * n + 1) ; i++){
    array[i] = -1;
  }

  Grafo g = crear_grafo(2 * n + 1, true);
  for(nat i = 1; i <= n ; i++){
    agregar_vertice(i, g);
    muere_o_nace[i] = 0;
    agregar_vertice(i + n, g);
    muere_o_nace[i + n] = 1;
    agregar_arista(i, i + n, g);
  }

  // imprimir_lista_datos(tipo1);
  // printf("\ny lista 2\n");
  // imprimir_lista_datos(tipo2);

  while(!es_vacia_lista_datos(tipo1)){
    agregar_arista(id1(primer_dato(tipo1)) + n, id2(primer_dato(tipo1)), g); // (1, muere) -> (2, nace).
    tipo1 = resto_datos(tipo1);
  }

  while(!es_vacia_lista_datos(tipo2)){
    agregar_arista(id1(primer_dato(tipo2)), id2(primer_dato(tipo2)) + n, g); // (2, nace) -> (1, muere)
    agregar_arista(id2(primer_dato(tipo2)), id1(primer_dato(tipo2)) + n, g); // (1, muere) -> (2, nace)
    tipo2 = resto_datos(tipo2);
  }

  nat* array_de_grados = new nat[99999];
  Lista vertices_para_llenar_in_grado = vertices(g);
  comienzo(vertices_para_llenar_in_grado);
  while (existe_actual(vertices_para_llenar_in_grado)) {
    nat elem = actual(vertices_para_llenar_in_grado);
    array_de_grados[elem] = in_grado(elem, g);
    siguiente(vertices_para_llenar_in_grado);
  }
  destruir_lista(vertices_para_llenar_in_grado);

  Cronologia cr = new evento[2 * n];
  int index = 0;
  Lista vertices_de_g = vertices(g);
  comienzo(vertices_de_g);
  while(existe_actual(vertices_de_g)){
    nat elem = actual(vertices_de_g);
    if(array_de_grados[elem] == 0){
      evento nuevo;
      if(muere_o_nace[elem] == 1){
        nuevo.tipo = muere;
        nuevo.id = elem - n;
      }else{
        nuevo.tipo = nace;
        nuevo.id = elem;
      }
      cr[index] = nuevo;

      Lista adyacentes_a_elem = copia_lista(adyacentes(elem, g));
      comienzo(adyacentes_a_elem);

      while (existe_actual(adyacentes_a_elem)){
        array_de_grados[actual(adyacentes_a_elem)] = array_de_grados[actual(adyacentes_a_elem)] - 1;
        siguiente(adyacentes_a_elem);
      }
      destruir_lista(adyacentes_a_elem);
      remover(elem, vertices_de_g);
      comienzo(vertices_de_g);
      index = index + 1;
    }else{
      siguiente(vertices_de_g);
    }
  }

  if(es_vacia_lista(vertices_de_g)){
    destruir_grafo(g);
    delete[] array;
    delete[] array_de_grados;
    delete[] muere_o_nace;
    destruir_lista(vertices_de_g);
    return cr;
  }else{
    destruir_grafo(g);
    delete[] array;
    delete[] array_de_grados;
    delete[] muere_o_nace;
    destruir_lista(vertices_de_g);
    delete[] cr;
    return NULL;
  }
}

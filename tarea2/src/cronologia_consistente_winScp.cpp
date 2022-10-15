/*
  MÃ³dulo de implementaciÃ³n de `cronologia_consistente'.

  Laboratorio de ProgramaciÃ³n 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>

#include "../include/cronologia_consistente.h"
#include "../include/grafo.h"
#include "../include/lista.h"
#include "../include/lista_datos.h"
#include "../include/utils.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  nat cantidad = 0;
  Grafo g = crear_grafo(2 * n + 1, true);
  for (nat i = 1; i <= n; i++)
  { // O(n)
    agregar_vertice(i, g);
    agregar_vertice(i + n, g);
    agregar_arista(i, i + n, g);
  }

  while (!es_vacia_lista_datos(tipo1))
  {                                                                          // O(cant tipo1)
    agregar_arista(id1(primer_dato(tipo1)) + n, id2(primer_dato(tipo1)), g); // (1, muere) -> (2, nace).
    tipo1 = resto_datos(tipo1);
  }

  while (!es_vacia_lista_datos(tipo2))
  {                                                                          // O(cant tipo2)
    agregar_arista(id1(primer_dato(tipo2)), id2(primer_dato(tipo2)) + n, g); // (2, nace) -> (1, muere)
    agregar_arista(id2(primer_dato(tipo2)), id1(primer_dato(tipo2)) + n, g); // (1, muere) -> (2, nace)
    tipo2 = resto_datos(tipo2);
  }

  nat *array_de_grados = new nat[cantidad_vertices(g) + 1];
  Lista vertices_para_llenar_in_grado = vertices(g);
  Lista con_cero_adyacencias = crear_lista();

  comienzo(vertices_para_llenar_in_grado);
  while (existe_actual(vertices_para_llenar_in_grado))
  { // O(n)
    nat elem = actual(vertices_para_llenar_in_grado);
    array_de_grados[elem] = in_grado(elem, g);

    if(array_de_grados[elem] == 0){
      insertar_al_inicio(elem, con_cero_adyacencias);
      cantidad++;
    }

    siguiente(vertices_para_llenar_in_grado);
  }
  destruir_lista(vertices_para_llenar_in_grado);

  Cronologia cr = new evento[2 * n];
  nat index = 0;

  while (!es_vacia_lista(con_cero_adyacencias)){
    nat elem = primero(con_cero_adyacencias);

    evento nuevo;
    if (elem > n)
    {
      nuevo.tipo = muere;
      nuevo.id = elem - n;
    }
    else
    {
      nuevo.tipo = nace;
      nuevo.id = elem;
    }
    cr[index++] = nuevo;

    Lista adyacentes_a_elem = adyacentes(elem, g);
    comienzo(adyacentes_a_elem);

    while (existe_actual(adyacentes_a_elem)){
      array_de_grados[actual(adyacentes_a_elem)] = array_de_grados[actual(adyacentes_a_elem)] - 1;
      if (array_de_grados[actual(adyacentes_a_elem)] == 0){
        insertar_al_final(actual(adyacentes_a_elem), con_cero_adyacencias);
        cantidad++;
      }
      siguiente(adyacentes_a_elem);
    }
    remover_al_inicio(con_cero_adyacencias);
  }
  destruir_lista(con_cero_adyacencias);
  delete[] array_de_grados;
  destruir_grafo(g);

  if (cantidad >= 2*n){
    return cr;
  }    
  
  delete[] cr;
  return NULL;
}

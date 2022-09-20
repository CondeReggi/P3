/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
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
  int* array = new int[2 * n + 1];
  // Crear grafo
  Grafo g = crear_grafo(2 * n - 1, true);

  ListaDatos auxiliar1 = tipo1;
  ListaDatos auxiliar2 = tipo2;

  // Agrego los no incidentes sabemos que hay todo. faltan los solapados que esos pueden ir de uno a otro
  while (!es_vacia_lista_datos(auxiliar1))
  {
    if (!existe_vertice(id1(primer_dato(auxiliar1)), g)){
      array[id1(primer_dato(auxiliar1))] = 0;
      agregar_vertice(id1(primer_dato(auxiliar1)), g);
    }
    if (!existe_vertice(id2(primer_dato(auxiliar1)), g)){
      array[id2(primer_dato(auxiliar1))] = 0;
      agregar_vertice(id2(primer_dato(auxiliar1)), g);
    }

    // Como son incidentes entonces: agregamos una arista (id1,id2) de tipo1
    agregar_arista(id1(primer_dato(auxiliar1)), id2(primer_dato(auxiliar1)), g);
    array[id2(primer_dato(auxiliar1))]++;
    auxiliar1 = resto_datos(auxiliar1);
  }

  while (!es_vacia_lista_datos(auxiliar2))
  {
    if (!existe_vertice(id1(primer_dato(auxiliar2)), g)){
      array[id1(primer_dato(auxiliar2))] = 0;
      agregar_vertice(id1(primer_dato(auxiliar2)), g);
    }
    if (!existe_vertice(id2(primer_dato(auxiliar2)), g)){
      array[id2(primer_dato(auxiliar2))] = 0;
      agregar_vertice(id2(primer_dato(auxiliar2)), g);
    }

    // Como son adyacentes entonces: agregamos una arista (id1,id2) y (id2,id1) de tipo2
    agregar_arista(id1(primer_dato(auxiliar2)), id2(primer_dato(auxiliar2)), g);
    agregar_arista(id2(primer_dato(auxiliar2)), id1(primer_dato(auxiliar2)), g);
    array[id2(primer_dato(auxiliar2))]++;
    array[id1(primer_dato(auxiliar2))]++;
    auxiliar2 = resto_datos(auxiliar2);
  }

  destruir_lista_datos(auxiliar1);
  destruir_lista_datos(auxiliar2);

  // Con esto finalizamos la creacion del grafo
  // Buscar orden Topologico
  Cronologia cr = new evento[2 * n];
  Lista vertices_de_g = vertices(g);
  int index = 0;
  bool existeAlMenosUnNoIncidente = false;
  for (int i = 1; i <= cantidad_vertices(g); i++){
    if (in_grado(i, g) == 0){
      // Aca ya se que todos tienen 0 aristas incidentes
      evento nuevo;
      nuevo.id = i;
      nuevo.tipo = /* ¿como se si se muere o nace? */;
      cr[index] = nuevo;
      index = index + 1;

      Lista adyacentes_a_v = adyacentes(i, g);

      // Actualizo las adyacencias de los nodos que estan conectados
      while (!es_vacia_lista(adyacentes_a_v)){
        g->celda[primero(adyacentes_a_v)].ingrado--;
        g->celda[primero(adyacentes_a_v)].outgrado--;
        remover_al_inicio(adyacentes_a_v);
      }

      destruir_lista(adyacentes_a_v);
    }else{
      existeAlMenosUnNoIncidente = true;
    }
  }

  if (existeAlMenosUnNoIncidente){
    return NULL;
  }else{
    destruir_grafo(g);
    delete[] cr;
    delete[] array;
    return cr;
  }

  //Otra alternativa
  int cantidad_sin_incidentes;
  Lista L; /* Empty list that will contain the sorted elements */
  Lista S; /* S ← Set of all nodes with no incoming edges */

  for (int i = 1; i <= cantidad_vertices(g); i++){
    if(in_grado(i, g) == 0){
      insertar_al_inicio(i, S);
    }
  }

  while(!es_vacia_lista(S)){
    nat first = primero(S);
    remover_al_inicio(S);
    insertar_al_final(first, L);

    
    Lista adyacentes_a_v = adyacentes(first, g);
    while (!es_vacia_lista(adyacentes_a_v)){
      //Remove arista (a1, b1) del grafo


      array[primero(adyacentes_a_v)]--;
      remover_al_inicio(adyacentes_a_v);
    }
  }


}

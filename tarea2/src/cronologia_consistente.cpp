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
  // Crear grafo
  Grafo g = crear_grafo(2 * n - 1, true);

  ListaDatos auxiliar1 = tipo1;
  ListaDatos auxiliar2 = tipo2;

  // Agrego los no incidentes sabemos que hay todo. faltan los solapados que esos pueden ir de uno a otro
  while (!es_vacia_lista_datos(auxiliar1))
  {
    if (!existe_vertice(id1(primer_dato(auxiliar1)), g)) agregar_vertice(id1(primer_dato(auxiliar1)), g);
    if (!existe_vertice(id2(primer_dato(auxiliar1)), g)) agregar_vertice(id2(primer_dato(auxiliar1)), g);

    // Como son incidentes entonces: agregamos una arista (id1,id2) de tipo1
    agregar_arista(id1(primer_dato(auxiliar1)), id2(primer_dato(auxiliar1)), g);
    auxiliar1 = resto_datos(auxiliar1);
  }

  while (!es_vacia_lista_datos(auxiliar2))
  {
    if (!existe_vertice(id1(primer_dato(auxiliar2)), g)) agregar_vertice(id1(primer_dato(auxiliar2)), g);
    if (!existe_vertice(id2(primer_dato(auxiliar2)), g)) agregar_vertice(id2(primer_dato(auxiliar2)), g);

    // Como son adyacentes entonces: agregamos una arista (id1,id2) y (id2,id1) de tipo2
    agregar_arista(id1(primer_dato(auxiliar2)), id2(primer_dato(auxiliar2)), g);
    agregar_arista(id2(primer_dato(auxiliar2)), id1(primer_dato(auxiliar2)), g);
    auxiliar2 = resto_datos(auxiliar2);
  }

  destruir_lista_datos(auxiliar1); 
  destruir_lista_datos(auxiliar2);

  // Con esto finalizamos la creacion del grafo
  // Buscar orden Topologico
  bool existe_ciclo = false;
  Lista lista_vertices = vertices(g);

  Lista cronologia = crear_lista();
  Grafo auxiliar = g;
  Lista vertices_auxiliar = vertices(auxiliar);

  for(nat i = 1; i <= n; i++){
    if(auxiliar->celdas[i].ingrado == 0){
      insertar_al_final(i, cronologia);
      remover(i, vertices_auxiliar);
    }
  }

  while(!es_vacia_lista(vertices_auxiliar)){
    insertar_al_final(vertices_auxiliar->elem, cronologia);
    Lista aBorrar = vertices_auxiliar;
    vertices_auxiliar = vertices_auxiliar->sig;
    delete aBorrar;
  }

  if(!es_vacia_lista(vertices_auxiliar)){
    return cr
  }

  nat cant_vertices = cantidad_vertices(g);



  //ordenTopologico(primerVertice, g, lista_vertices, visitado);



  bool existe_cr_consistente = false;

  


  Cronologia cr = new evento[2 * n];

  if (existe_cr_consistente)
  { // si existe, retornarla en cr
    return cr;
  }
  else
  { // si no existe, liberar la memoria asociada a cr y retornar NULL
    destruir_grafo(g);
    delete[] cr;
    return NULL;
  }
}

// void ordenTopologico(Vertice v, Grafo g, Lista &lista, int* &visitado){
//   visitado[v] = true;
//   for(int i = 0; i < v->adyacentes; i++){
//     if(visitado[adyacentes[v][i]] == false){
//       ordenTopologico(adyacentes[v][i], g , lista, visitado);
//     }else{
//       break;
//     }
//   }
// }

// Crear una pila
// Crear un array de visitados
// inicializar todas los vertices del Grafo visitados[v] = false
//  for(int i = 0; i < g->CantidadVertices; i++){
//    if(visitado[i] == false){
//      odenarTopologico(i, visitado, pila);
//    }
//  }

// void odenarTopologico(int v, boolean *visitado, Pila pila, Grafo *g){
//   visitado[v] == true;
//   int i;
//   const adyacentes_a_v = g->vertices[v]->adyacentes;
//   while(adyacentes_a_v->next != nullptr){
//     i = adyacentes_a_v->next;
//     if(!visitado[i]){
//       odenarTopologico(i, visitado, pila, g);
//     }
//   }
// }
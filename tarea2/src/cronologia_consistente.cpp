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
  int* array = new int[2 * n + 1];
  

  for(int i = 0; i < (int)(2 * n + 1) ; i++){
    array[i] = -1;
  }

  printf("Cargue array\n");

  // Crear grafo
  Grafo g = crear_grafo(2 * n - 1, true);

  imprimir_lista_datos(tipo1);
  imprimir_lista_datos(tipo2);

  while(!es_vacia_lista_datos(tipo1)){
    agregar_vertice(id1(primer_dato(tipo1)), g); // (1, nace) => 1 
    agregar_vertice(id1(primer_dato(tipo1)) + n, g); // (1, muere) => 2

    agregar_arista(id1(primer_dato(tipo1)), id1(primer_dato(tipo1)) + n, g); // (1, nace) -> (1, muere)

    agregar_vertice(id2(primer_dato(tipo1)), g); // (2, nace) => 3
    agregar_vertice(id2(primer_dato(tipo1)) + n, g); // (2, muere) => 4

    agregar_arista(id2(primer_dato(tipo1)), id2(primer_dato(tipo1)) + n, g); // (2, nace) -> (2, muere)
    agregar_arista(id1(primer_dato(tipo1)) + n, id2(primer_dato(tipo1)), g); // (1, muere) -> (2, nace).
    tipo1 = resto_datos(tipo1);
  }

  while(!es_vacia_lista_datos(tipo2)){
    agregar_vertice(id1(primer_dato(tipo2)), g); // (1, nace) => 1 
    agregar_vertice(id1(primer_dato(tipo2)) + n, g); // (1, muere) => 2

    agregar_vertice(id2(primer_dato(tipo2)), g); // (2, nace) => 3
    agregar_vertice(id2(primer_dato(tipo2)) + n, g); // (2, muere) => 4

    agregar_arista(id2(primer_dato(tipo2)), id1(primer_dato(tipo2)) + n, g); // (2, nace) -> (2, muere)
    agregar_arista(id1(primer_dato(tipo2)) + n, id2(primer_dato(tipo2)), g); // (1, muere) -> (2, nace)
    tipo2 = resto_datos(tipo2);
  }

  // Agrego los no incidentes sabemos que hay todo. faltan los solapados que esos pueden ir de uno a otro
  // while (!es_vacia_lista_datos(auxiliar1))
  // {
  //   if (!existe_vertice(id1(primer_dato(auxiliar1)), g)){
  //     array[id1(primer_dato(auxiliar1))] = nace;
  //     agregar_vertice(id1(primer_dato(auxiliar1)), g);
  //   }
  //   if (!existe_vertice(id2(primer_dato(auxiliar1)), g)){
  //     array[id2(primer_dato(auxiliar1))] = muere;
  //     agregar_vertice(id2(primer_dato(auxiliar1)), g);
  //   }
  //   // Como son incidentes entonces: agregamos una arista (id1,id2) de tipo1
  //   agregar_arista(id1(primer_dato(auxiliar1)), id2(primer_dato(auxiliar1)), g);
  //   printf("Agregue nodos: %d y %d, y la arista desde d1 a d2\n",id1(primer_dato(auxiliar1)) ,id2(primer_dato(auxiliar1)) );
  //   auxiliar1 = resto_datos(auxiliar1);
  // }
  // printf("Llene con lista1\n");
  // while (!es_vacia_lista_datos(auxiliar2)) //Esto esta mal armado creo
  // {
  //   if (!existe_vertice(id1(primer_dato(auxiliar2)), g)){
  //     if(array[id1(primer_dato(auxiliar2))] != -1){
  //       array[id1(primer_dato(auxiliar2))] = nace;
  //     }
  //     agregar_vertice(id1(primer_dato(auxiliar2)), g);
  //   }
  //   if (!existe_vertice(id2(primer_dato(auxiliar2)), g)){
  //     if(array[id2(primer_dato(auxiliar2))] != -1){
  //       array[id2(primer_dato(auxiliar2))] = nace;
  //     }
  //     agregar_vertice(id2(primer_dato(auxiliar2)), g);
  //   }
  //   // Como son adyacentes entonces: agregamos una arista (id1,id2) y (id2,id1) de tipo2
  //   agregar_arista(id1(primer_dato(auxiliar2)), id2(primer_dato(auxiliar2)), g);
  //   agregar_arista(id2(primer_dato(auxiliar2)), id1(primer_dato(auxiliar2)), g);
  //   printf("Agregue nodos: %d y %d, y la arista desde d1 a d2 y d2 a d1\n",id1(primer_dato(auxiliar2)) ,id2(primer_dato(auxiliar2)) );
  //   auxiliar2 = resto_datos(auxiliar2);
  // }

  nat* array_de_grados = new nat[cantidad_vertices(g)];
  for(nat i = 1; i <= cantidad_vertices(g); i++){
    array_de_grados[i - 1] = in_grado(i, g);
    printf("Para el nodo %d tiene in grado: %d\n", i, in_grado(i, g));
  }

  // Con esto finalizamos la creacion del grafo
  // Buscar orden Topologico
  // Lista vertices_de_g = vertices(g);
  // int index = 0;
  // bool existeAlMenosUnNoIncidente = false;
  // for (nat i = 1; i <= cantidad_vertices(g); i++){
  //   if (array_de_grados[i - 1] == 0 || i == 1){
  //     // Aca ya se que todos tienen 0 aristas incidentes
  //     evento nuevo;
  //     nuevo.id = i;
  //     nuevo.tipo = tipo_evento(array[i]); /* ¿como se si se muere o nace? */; //Estructura auxiliar de murio, nace? por indice'
  //     cr[index] = nuevo;
  //     printf("En index %d inserte id: %d tipo %d\n", index, i, tipo_evento(array[i]));
  //     index = index + 1;
  //     // No es necesario porque solo hay que dar un orden topologico, en caso de que haya se muestrea y listo sino, existeAlmenosUnNoIncicidente = true y no hay orden topologico
  //     Lista indicentes_a_v = copia_lista(incidentes(i, g));
  //     // Actualizo las adyacencias de los nodos que estan conectados NO ES NECESARIO DESTUIR LAS ARISTAS
  //     while (!es_vacia_lista(indicentes_a_v)){
  //       printf("Para el nodo: %d tenia tantos: %d\n", primero(indicentes_a_v), array_de_grados[primero(indicentes_a_v) - 1]);
  //       if(array_de_grados[primero(indicentes_a_v) - 1] != 0){
  //         array_de_grados[primero(indicentes_a_v) - 1] = array_de_grados[primero(indicentes_a_v) - 1] - 1;
  //       }
  //       remover_al_inicio(indicentes_a_v);
  //     }
  //     destruir_lista(indicentes_a_v);
  //   }else{
  //     printf("Consegui un no inicidente con mas de grado de incidentes en el indice %d\n", i);
  //     existeAlMenosUnNoIncidente = true;
  //   }
  // }
  
  Cronologia cr = new evento[2 * n];
  int index = 0;
  Lista vertices_de_g = vertices(g);
  comienzo(vertices_de_g);
  while(existe_actual(vertices_de_g)){
    nat elem = actual(vertices_de_g);
    printf("Recorriendo elemento : %d que tiene flechas para afuera tantas: %d\n", elem, out_grado(elem, g));
    if(array_de_grados[elem - 1] == 0){
      printf("El elemnto con 0 elementos es : %d\n", elem);
      evento nuevo;
      nuevo.id = floor(elem / 2);

      if(elem % 2 == 0){
        nuevo.tipo = muere;
      }else{
        nuevo.tipo = nace;
      }
      //nuevo.tipo = tipo_evento(array[elem]);
      cr[index] = nuevo;

      Lista adyacentes_a_elem = copia_lista(adyacentes(elem, g));
      comienzo(adyacentes_a_elem);

      while (existe_actual(adyacentes_a_elem)){
        printf("El elemento actual que se supone es incidente es: %d y actualmente tiene %d ingrado\n", actual(adyacentes_a_elem), array_de_grados[actual(adyacentes_a_elem) - 1]);
        array_de_grados[actual(adyacentes_a_elem) - 1] = array_de_grados[actual(adyacentes_a_elem) - 1] - 1;
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
    printf("Voy a devolver cr\n");
    destruir_grafo(g);
    delete[] array;
    delete[] array_de_grados;
    destruir_lista(vertices_de_g);
    return cr;
  }else{
    printf("Voy a devolver null\n");
    destruir_grafo(g);
    delete[] array;
    delete[] array_de_grados;
    destruir_lista(vertices_de_g);
    delete[] cr;
    return NULL;
  }
  // printf("Valor: %d", existeAlMenosUnNoIncidente);

  // if (existeAlMenosUnNoIncidente){
  //   printf("Voy a devolver null\n");
  //   destruir_grafo(g);
  //   delete[] cr;
  //   delete[] array;
  //   return NULL;
  // }else{
  //   printf("Voy a devolver cr\n");
  //   destruir_grafo(g);
  //   delete[] array;
  //   return cr;
  // }

  //Otra alternativa
  // int cantidad_sin_incidentes;
  // Lista L; /* Empty list that will contain the sorted elements */
  // Lista S; /* S ← Set of all nodes with no incoming edges */

  // for (int i = 1; i <= cantidad_vertices(g); i++){
  //   if(in_grado(i, g) == 0){
  //     insertar_al_inicio(i, S);
  //   }
  // }

  // while(!es_vacia_lista(S)){
  //   nat first = primero(S);
  //   remover_al_inicio(S);
  //   insertar_al_final(first, L);

    
  //   Lista adyacentes_a_v = adyacentes(first, g);
  //   while (!es_vacia_lista(adyacentes_a_v)){
  //     //Remove arista (a1, b1) del grafo


  //     array[primero(adyacentes_a_v)]--;
  //     remover_al_inicio(adyacentes_a_v);
  //   }
  // }
}

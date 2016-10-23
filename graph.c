//
// Created by lfmundim on 20/10/16.
//

#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

void allocGraph(graphT *graph, mapT map){
    int i;
    graph->dimension = map.size_x*map.size_y;
    graph->matrix = (int**)calloc((size_t)graph->dimension, sizeof(int*));
    for(i=0; i<graph->dimension; i++)
        graph->matrix[i] = (int*)calloc((size_t)graph->dimension, sizeof(int));
}

void makeGraph(mapT map, graphT *graph, personT *person, bool scan){
    int i, j, source, dest, aux[2];
    //preenche com 1s
    if(scan==false) { //portas == paredes OK
        for (i = map.size_x - 1; i >= 0; i--) {
            for (j = 0; j < map.size_y; j++) {
                if(map.matrix[i][j].key[0]=='V'){
                    person->coord_x=i;
                    person->coord_y=j;
                }
                //direita
                if (i + 1 < map.size_x) {
                    if (map.matrix[i + 1][j].key[0] != '#') { //parede
                        //wormhole
                        if(map.matrix[i+1][j].wormhole==true){
                            aux[0] = (int)map.matrix[i+1][j].key[0]-48;
                            aux[1] = (int)map.matrix[i+1][j].key[1]-48;
                            source = map.matrix[i][j].number;
                            dest = map.matrix[aux[0]][aux[1]].number;
                            graph->matrix[source][dest] = 1;
                        }
                            //normal
                        else if (map.matrix[i + 1][j].key[0] < 58 || map.matrix[i + 1][j].key[0] == 'E' ||
                            map.matrix[i + 1][j].key[0] > 96) {//inclui numeros, ponto, saída e chaves
                            source = map.matrix[i][j].number;
                            dest = map.matrix[i + 1][j].number;
                            graph->matrix[source][dest] = 1;
                        }
                    }
                }
                //esquerda
                if (i - 1 >= 0) {
                    if (map.matrix[i - 1][j].key[0] != '#') { //parede
                        //wormhole
                        if(map.matrix[i-1][j].wormhole==true){
                            aux[0] = (int)map.matrix[i-1][j].key[0]-48;
                            aux[1] = (int)map.matrix[i-1][j].key[1]-48;
                            source = map.matrix[i][j].number;
                            dest = map.matrix[aux[0]][aux[1]].number;
                            graph->matrix[source][dest] = 1;
                        }
                        //normal
                        else if (map.matrix[i - 1][j].key[0] < 58 || map.matrix[i - 1][j].key[0] == 'E' ||
                            map.matrix[i - 1][j].key[0] > 96) {//inclui numeros, ponto e saída
                            source = map.matrix[i][j].number;
                            dest = map.matrix[i - 1][j].number;
                            graph->matrix[source][dest] = 1;
                        }
                    }
                }
                //acima
                if (j - 1 >= 0) {
                    if (map.matrix[i][j - 1].key[0] != '#') { //parede
                        //wormhole
                        if(map.matrix[i][j-1].wormhole==true){
                            aux[0] = (int)map.matrix[i][j-1].key[0]-48;
                            aux[1] = (int)map.matrix[i][j-1].key[1]-48;
                            source = map.matrix[i][j].number;
                            dest = map.matrix[aux[0]][aux[1]].number;
                            graph->matrix[source][dest] = 1;
                        }
                            //normal
                        else if (map.matrix[i][j - 1].key[0] < 58 || map.matrix[i][j - 1].key[0] == 'E' ||
                            map.matrix[i][j - 1].key[0] > 96) {//inclui numeros, ponto e saída
                            source = map.matrix[i][j].number;
                            dest = map.matrix[i][j - 1].number;
                            graph->matrix[source][dest] = 1;
                        }
                    }
                }
                //abaixo
                if (j + 1 < map.size_y) {
                    if (map.matrix[i][j + 1].key[0] != '#') { //parede
                        //wormhole
                        if(map.matrix[i][j+1].wormhole==true){
                            aux[0] = (int)map.matrix[i][j+1].key[0]-48;
                            aux[1] = (int)map.matrix[i][j+1].key[1]-48;
                            source = map.matrix[i][j].number;
                            dest = map.matrix[aux[0]][aux[1]].number;
                            graph->matrix[source][dest] = 1;
                        }
                        //normal
                        else if (map.matrix[i][j + 1].key[0] < 58 || map.matrix[i][j + 1].key[0] == 'E' ||
                            map.matrix[i][j + 1].key[0] > 96) {//inclui numeros, ponto e saída
                            source = map.matrix[i][j].number;
                            dest = map.matrix[i][j + 1].number;
                            graph->matrix[source][dest] = 1;
                        }
                    }
                }
            }
        }
    }
}
//
// Created by lfmundim on 20/10/16.
//

#ifndef TP2_2_GRAPH_H
#define TP2_2_GRAPH_H

#include "map.h"
#include "vinicius.h"

typedef struct graphT{
    int **matrix;
    int dimension;
}graphT;

void openDoor(int keycell, graphT *graph, mapT map);

void closeDoor(int keycell, graphT *graph, mapT map);

void materializeWormhole(bool included[], graphT *graph, mapT map, personT person);

void dematerializeWormhole(int vertex, graphT *graph, mapT map, personT person);

void allocGraph(graphT *graph, mapT map);

void freeGraph(graphT *graph);

void printGraph(graphT *graph);

void makeGraph(mapT map, graphT *graph, personT *person); //scan true se for ignorar portas

int walking(int *keylocation, graphT *graph, mapT map, personT *vinicius);

#endif //TP2_2_GRAPH_H

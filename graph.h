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

void allocGraph(graphT *graph, mapT map);

void makeGraph(mapT map, graphT *graph, personT *person, bool scan); //scan true se for ignorar portas

int dijkstra(graphT graph, mapT map);

void dijkstraScan(graphT graph, mapT map, int *keys);

#endif //TP2_2_GRAPH_H

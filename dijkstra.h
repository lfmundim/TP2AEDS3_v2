//
// Created by lfmundim on 22/10/16.
//

#ifndef TP2_2_DIJKSTRA_H
#define TP2_2_DIJKSTRA_H

#include <stdbool.h>
#include "map.h"
#include "graph.h"
#include "vinicius.h"

int minDistance(int dist[], bool included[], int vertex_num);

int dijkstra(graphT *graph, int source, int vertex_num, int dest, mapT map, personT person);

//int dijkstraScan(int **graph, int source, int vertex_num, int dest, char *keys, mapT map);


#endif //TP2_2_DIJKSTRA_H

//
// Created by lfmundim on 22/10/16.
//

#ifndef TP2_2_DIJKSTRA_H
#define TP2_2_DIJKSTRA_H

#include <stdbool.h>

int minDistance(int dist[], bool included[], int vertex_num);

int dijkstra(int **graph, int source, int vertex_num, int dest);

#endif //TP2_2_DIJKSTRA_H

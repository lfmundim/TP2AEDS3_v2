//
// Created by lfmundim on 22/10/16.
//

#include <stdio.h>
#include "dijkstra.h"
#include <limits.h>
#include "vinicius.h"

int minDistance(int dist[], bool included[], int vertex_num){
    int min = INT_MAX, min_index=0, i;

    for(i=0; i<vertex_num; i++){
        if(included[i] == false && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

int dijkstra(int **graph, int source, int vertex_num, int dest){
    int dist[vertex_num], i, j, v;
    bool included[vertex_num];

    for(i=0; i<vertex_num; i++){
        dist[i] = 100000;
        included[i] = false;
    }

    dist[source] = 0; //distância de um vértice para ele mesmo

    for(i=0; i<vertex_num-1; i++){
        v = minDistance(dist, included, vertex_num);
        included[v] = true;

        for(j=0; j<vertex_num; j++){
            if(!included[j] && graph[v][j] && dist[v] != INT_MAX && dist[v]+graph[v][j] < dist[j]){
                dist[j] = dist[v]+graph[v][j];
            }
        }
    }

    return dist[dest];
}

//int dijkstraScan(int **graph, int source, int vertex_num, int dest, char *keys, mapT map){
//    int dist[vertex_num], i, j, v, count, count2, aux=0;
//    bool included[vertex_num];
//
//    for(i=0; i<vertex_num; i++){
//        dist[i] = INT_MAX;
//        included[i] = false;
//    }
//
//    dist[source] = 0; //distância de um vértice para ele mesmo
//
//    for(i=0; i<vertex_num-1; i++){
//        v = minDistance(dist, included, vertex_num);
//        included[v] = true;
//
//        for(j=0; j<vertex_num; j++){
//            if(!included[j] && graph[v][j] && dist[v] != INT_MAX && dist[v]+graph[v][j] < dist[j]){
//                dist[j] = dist[v]+graph[v][j];
//            }
//        }
//    }
//
//    return dist[dest];
//}

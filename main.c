#include <stdio.h>
#include "vinicius.h"
#include "map.h"
#include "graph.h"
#include "dijkstra.h"
#include <limits.h>

int main(){
    mapT map;
    graphT graph;
    personT vinicius;
    int keys, shortest=INT_MAX, keylocation[4];

    scanf("%d %d %d", &map.size_x, &map.size_y, &keys);
    vinicius.key_n = keys;

    makePerson(&vinicius, keys);

    makeMap(&map); //OK
    fillMap(&map, &vinicius); //OK
    printf("GRID:\n");
    for(int i=map.size_x-1; i>=0; i--){
        for(int j=0; j<map.size_y; j++){
            printf("[%c]", map.matrix[i][j].key[0]);
        }
        printf("\n");
    }
    //TODO tratar input2, tratar wormholes(sumir, cadeias de wormholes), modificar outro dijkstra pra só calcular o necessário
    allocGraph(&graph, map);
    makeGraph(map, &graph, &vinicius);//TODO ignorando portas
    findKeys(map, keylocation);
    for(int i=0; i<4; i++)
        printf("%d ", keylocation[i]);
    printf("\n");
//    shortest = dijkstra(graph.matrix, 12, graph.dimension, 0);
    shortest = walking(keylocation, &graph, map, &vinicius);
    printf("SHORTEST: %d\n", shortest);


    //caminha

    return 0;
}
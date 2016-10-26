#include <stdio.h>
#include "vinicius.h"
#include "map.h"
#include "graph.h"
#include "dijkstra.h"
#include <limits.h>
#include <stdlib.h>

int main(){
    mapT map;
    graphT graph;
    personT vinicius;
    int keys, shortest, keylocation[4];

    scanf("%d %d %d", &map.size_x, &map.size_y, &keys);
    vinicius.key_n = keys;

    makePerson(&vinicius, keys);

    makeMap(&map); //OK
    fillMap(&map, &vinicius); //OK
//    printf("GRID:\n");
//    for(int i=map.size_x-1; i>=0; i--){
//        for(int j=0; j<map.size_y; j++){
//            printf("[%c]", map.matrix[i][j].key[0]);
//        }
//        printf("\n");
//    }
    //TODO tratar wormholes(sumir, cadeias de wormholes), modificar outro dijkstra pra só calcular o necessário
    allocGraph(&graph, map);
    makeGraph(map, &graph, &vinicius);
    findKeys(map, keylocation);
//    for(int i=0; i<4; i++)
//        printf("%d ", keylocation[i]);
//    printf("\n");
    shortest = walking(keylocation, &graph, map, &vinicius);
//    printf("SHORTEST: %d\n", shortest);

    if(shortest==100000)
        printf("-1\n");
    else
        printf("%d\n", shortest);



    return 0;
}
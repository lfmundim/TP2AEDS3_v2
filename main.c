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

    makeMap(&map);
    fillMap(&map, &vinicius);
    allocGraph(&graph, map);
    makeGraph(map, &graph, &vinicius);
    findKeys(map, keylocation);
    shortest = walking(keylocation, &graph, map, &vinicius);

    if(shortest==100000)
        printf("-1\n");
    else
        printf("%d\n", shortest);
    freePerson(&vinicius);
    freeGraph(&graph);
    freeMap(&map);


    return 0;
}

#include <stdio.h>
#include "vinicius.h"
#include "map.h"
#include "graph.h"

int main(){
    mapT map;
    graphT graph;
    personT vinicius;
    int keys, i, j;

    scanf("%d %d %d", &map.size_x, &map.size_y, &keys);

    makePerson(&vinicius, keys);

    makeMap(&map); //OK
    fillMap(&map); //OK
    //TODO makegraph para varredura, fazer caminhadas, tratar portas, fazer dijkstrascan, modificar outro dijkstra pra só calcular o necessário
    allocGraph(&graph, map);
    makeGraph(map, &graph, &vinicius, true);//TODO ignorando portas
//    dijkstraScan(graph, map, &neededKeys); //TODO shortest path, guarda chaves
    makeGraph(map, &graph, &vinicius, false);//considerando portas -- OK
    //caminha

    return 0;
}
//
// Created by lfmundim on 20/10/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"
#include "dijkstra.h"

void openDoor(int keycell, graphT *graph, mapT map){
    int i, j, number;
    char aux;

    for(i=map.size_x-1; i>=0; i--){
        for(j=0; j<map.size_y; j++){
            if(map.matrix[i][j].number==keycell) {
                aux = map.matrix[i][j].key[0]-32; //"transforma" minúsculo em maiúsculo (para porta)
            }
        }
    }

    for(i=0; i<map.size_x; i++){
        for(j=0; j<map.size_y; j++) {
            if(map.matrix[i][j].key[0]==aux){
                number = map.matrix[i][j].number;
                if(number-1>=0)
                    graph->matrix[number-1][number]=1;
                if(number+1<graph->dimension)
                    graph->matrix[number+1][number]=1;
                if(number-map.size_y>=0)
                    graph->matrix[number-map.size_y][number]=1;
                if(number+map.size_y<graph->dimension)
                    graph->matrix[number+map.size_y][number]=1;
            }
        }
    }

}

void closeDoor(int keycell, graphT *graph, mapT map){
    int i, j, number;
    char aux=-1;

    for(i=0; i<map.size_x; i++){
        for(j=0; j<map.size_y; j++){
            if(map.matrix[i][j].number==keycell) {
                aux = map.matrix[i][j].key[0];
                aux -= 32;
            }
        }
    }

    for(i=0; i<map.size_x; i++){
        for(j=0; j<map.size_y; j++) {
            if(map.matrix[i][j].key[0]==aux){
                number = map.matrix[i][j].number;
                if(number-1>=0)
                    graph->matrix[number-1][number]=0;
                if(number+1<graph->dimension)
                    graph->matrix[number+1][number]=0;
                if(number-map.size_y>=0)
                    graph->matrix[number-map.size_y][number]=0;
                if(number+map.size_y<graph->dimension)
                    graph->matrix[number+map.size_y][number]=0;
            }
        }
    }

}

void materializeWormhole(bool included[], graphT *graph, mapT map, personT person){
    int i, j, k;

    for(i=0; i<graph->dimension; i++){
        for(j=0; j<map.size_x; j++){
            for(k=0; k<map.size_y; k++){
                if(included[i]==true && map.matrix[j][k].number==i && map.matrix[j][k].key[0]>47 && map.matrix[j][k].key[0]<58){
                    map.matrix[j][k].wormhole=true;
                }
            }
        }
    }
    makeGraph(map, graph, &person);
}

void dematerializeWormhole(int vertex, graphT *graph, mapT map, personT person){
    int i, j, k;

    for(i=0; i<graph->dimension; i++){
        for(j=0; j<map.size_x; j++){
            for(k=0; k<map.size_y; k++){
                if(map.matrix[j][k].number==vertex && map.matrix[j][k].wormhole==true){
                    map.matrix[j][k].wormhole=false;
//                    printf("OI\n");
                    goto out;
                }
            }
        }
    }
    out:
    makeGraph(map, graph, &person);
}

void allocGraph(graphT *graph, mapT map){
    int i;
    graph->dimension = map.size_x*map.size_y;
    graph->matrix = (int**)calloc((size_t)graph->dimension, sizeof(int*));
    for(i=0; i<graph->dimension; i++)
        graph->matrix[i] = (int*)calloc((size_t)graph->dimension, sizeof(int));
}

void freeGraph(graphT *graph){
    int i;
    for(i=0; i<graph->dimension; i++)
        free(graph->matrix[i]);
    free(graph->matrix);
}

void printGraph(graphT *graph){
    int i, j;

    for(i=0; i<graph->dimension; i++){
        for(j=0; j<graph->dimension; j++){
            printf("[%d]", graph->matrix[i][j]);
        }
        printf("\n");
    }

}

void makeGraph(mapT map, graphT *graph, personT *person){
    int i, j, source, dest, aux[2];
    //preenche com 1s
    for (i = map.size_x - 1; i >= 0; i--) {
        for (j = 0; j < map.size_y; j++) {
            if(map.matrix[i][j].key[0]=='V'){
                person->coord_x=i;
                person->coord_y=j;
            }
            //direita
            if (i + 1 < map.size_x) {
                if (map.matrix[i + 1][j].key[0] != '#' &&
                    map.matrix[i + 1][j].key[0] != 'D' &&
                    map.matrix[i + 1][j].key[0] != 'C' &&
                    map.matrix[i + 1][j].key[0] != 'H' &&
                    map.matrix[i + 1][j].key[0] != 'S' ) { //parede
                    //wormhole
                    if(map.matrix[i+1][j].wormhole==true){
                        aux[0] = (int)map.matrix[i+1][j].key[0]-48;
                        aux[1] = (int)map.matrix[i+1][j].key[1]-48;
                        while(map.matrix[aux[0]][aux[1]].wormhole==true){
                            aux[0] = (int)map.matrix[aux[0]][aux[1]].key[0]-48;
                            aux[1] = (int)map.matrix[aux[0]][aux[1]].key[1]-48;
                        }
                        source = map.matrix[i][j].number;
                        dest = map.matrix[aux[0]][aux[1]].number;
                        graph->matrix[source][dest] = 1;
                    }
                        //normal
                    else if (map.matrix[i + 1][j].key[0] < 58 || map.matrix[i + 1][j].key[0] == 'E' ||
                        map.matrix[i + 1][j].key[0] > 96 ||map.matrix[i + 1][j].key[0] =='V') {//inclui numeros, ponto, saída e chaves
                        source = map.matrix[i][j].number;
                        dest = map.matrix[i + 1][j].number;
                        graph->matrix[source][dest] = 1;
                    }
                }
            }
            //esquerda
            if (i - 1 >= 0) {
                if (map.matrix[i - 1][j].key[0] != '#' &&
                    map.matrix[i - 1][j].key[0] != 'D' &&
                    map.matrix[i - 1][j].key[0] != 'C' &&
                    map.matrix[i - 1][j].key[0] != 'H' &&
                    map.matrix[i - 1][j].key[0] != 'S') { //parede
                    //wormhole
                    if(map.matrix[i-1][j].wormhole==true){
                        aux[0] = (int)map.matrix[i-1][j].key[0]-48;
                        aux[1] = (int)map.matrix[i-1][j].key[1]-48;
                        while(map.matrix[aux[0]][aux[1]].wormhole==true){
                            aux[0] = (int)map.matrix[aux[0]][aux[1]].key[0]-48;
                            aux[1] = (int)map.matrix[aux[0]][aux[1]].key[1]-48;
                        }
                        source = map.matrix[i][j].number;
                        dest = map.matrix[aux[0]][aux[1]].number;
                        graph->matrix[source][dest] = 1;
                    }
                    //normal
                    else if (map.matrix[i - 1][j].key[0] < 58 || map.matrix[i - 1][j].key[0] == 'E' ||
                        map.matrix[i - 1][j].key[0] > 96 || map.matrix[i - 1][j].key[0] == 'V') {//inclui numeros, ponto e saída
                        source = map.matrix[i][j].number;
                        dest = map.matrix[i - 1][j].number;
                        graph->matrix[source][dest] = 1;
                    }
                }
            }
            //acima
            if (j - 1 >= 0) {
                if (map.matrix[i][j - 1].key[0] != '#' &&
                    map.matrix[i][j - 1].key[0] != 'D' &&
                    map.matrix[i][j - 1].key[0] != 'C' &&
                    map.matrix[i][j - 1].key[0] != 'S' &&
                    map.matrix[i][j - 1].key[0] != 'H' ) { //parede
                    //wormhole
                    if(map.matrix[i][j-1].wormhole==true){
                        aux[0] = (int)map.matrix[i][j-1].key[0]-48;
                        aux[1] = (int)map.matrix[i][j-1].key[1]-48;
                        while(map.matrix[aux[0]][aux[1]].wormhole==true){
                            aux[0] = (int)map.matrix[aux[0]][aux[1]].key[0]-48;
                            aux[1] = (int)map.matrix[aux[0]][aux[1]].key[1]-48;
                        }
                        source = map.matrix[i][j].number;
                        dest = map.matrix[aux[0]][aux[1]].number;
                        graph->matrix[source][dest] = 1;
                    }
                        //normal
                    else if (map.matrix[i][j - 1].key[0] < 58 || map.matrix[i][j - 1].key[0] == 'E' ||
                        map.matrix[i][j - 1].key[0] > 96 || map.matrix[i][j - 1].key[0] == 'V') {//inclui numeros, ponto e saída
                        source = map.matrix[i][j].number;
                        dest = map.matrix[i][j - 1].number;
                        graph->matrix[source][dest] = 1;
                    }
                }
            }
            //abaixo
            if (j + 1 < map.size_y) {
                if (map.matrix[i][j + 1].key[0] != '#' &&
                    map.matrix[i][j + 1].key[0] != 'D' &&
                    map.matrix[i][j + 1].key[0] != 'C' &&
                    map.matrix[i][j + 1].key[0] != 'S' &&
                    map.matrix[i][j + 1].key[0] != 'H'){ //parede
                    //wormhole
                    if(map.matrix[i][j+1].wormhole==true){
                        aux[0] = (int)map.matrix[i][j+1].key[0]-48;
                        aux[1] = (int)map.matrix[i][j+1].key[1]-48;
                        while(map.matrix[aux[0]][aux[1]].wormhole==true){
                            aux[0] = (int)map.matrix[aux[0]][aux[1]].key[0]-48;
                            aux[1] = (int)map.matrix[aux[0]][aux[1]].key[1]-48;
                        }
                        source = map.matrix[i][j].number;
                        dest = map.matrix[aux[0]][aux[1]].number;
                        graph->matrix[source][dest] = 1;
                    }
                    //normal
                    else if (map.matrix[i][j + 1].key[0] < 58 || map.matrix[i][j + 1].key[0] == 'E' ||
                        map.matrix[i][j + 1].key[0] > 96 || map.matrix[i][j + 1].key[0] == 'V') {//inclui numeros, ponto e saída
                        source = map.matrix[i][j].number;
                        dest = map.matrix[i][j + 1].number;
                        graph->matrix[source][dest] = 1;
                    }
                }
            }
        }
    }
}

int walking(int *keylocation, graphT *graph, mapT map, personT *vinicius){
    int aux, i, j, k, shortest;

    shortest = dijkstra(graph, map.matrix[vinicius->coord_x][vinicius->coord_y].number, graph->dimension, map.matrix[map.exit_x][map.exit_y].number);

    if(vinicius->key_n>=1) {
        for (i = 0; i < 4; i++) { //1 key
            if(keylocation[i]>graph->dimension) {
                break;
            }
            aux = dijkstra(graph, map.matrix[vinicius->coord_x][vinicius->coord_y].number, graph->dimension, keylocation[i]);
            if(aux<100000) {
                openDoor(keylocation[i], graph, map);
                aux += dijkstra(graph, keylocation[i], graph->dimension,
                                map.matrix[map.exit_x][map.exit_y].number);
            }
            if (aux < shortest) {
                shortest = aux;
            }
            closeDoor(keylocation[i], graph, map);
        }
    }

    if(vinicius->key_n >=2){
        for(i=0; i<4; i++){ //2 key
            for(j=0; j<4; j++){
                if(keylocation[i]>graph->dimension || keylocation[j]>graph->dimension) {
                    break;
                }
                aux = dijkstra(graph, map.matrix[vinicius->coord_x][vinicius->coord_y].number, graph->dimension, keylocation[i]);
                openDoor(keylocation[i], graph, map);
                aux += dijkstra(graph, keylocation[i], graph->dimension, keylocation[j]);
                openDoor(keylocation[j], graph, map);
                aux += dijkstra(graph, keylocation[j], graph->dimension, map.matrix[map.exit_x][map.exit_y].number);
                if(aux<shortest) {
                    shortest = aux;
                }
                closeDoor(keylocation[i], graph, map);
                closeDoor(keylocation[j], graph, map);
            }
        }
    }


    if(vinicius->key_n==3) {
        for (i = 0; i < 4; i++) { //3 key
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 2; k++) {
                    if (keylocation[i] > graph->dimension || keylocation[j] > graph->dimension ||
                        keylocation[k] > graph->dimension) {
                        break;
                    }
                    aux = dijkstra(graph, map.matrix[vinicius->coord_x][vinicius->coord_y].number, graph->dimension,
                                   keylocation[i]);
                    openDoor(keylocation[i], graph, map);
                    aux += dijkstra(graph, keylocation[i], graph->dimension, keylocation[j]);
                    openDoor(keylocation[j], graph, map);
                    aux += dijkstra(graph, keylocation[j], graph->dimension, keylocation[k]);
                    openDoor(keylocation[k], graph, map);
                    aux += dijkstra(graph, keylocation[k], graph->dimension, map.matrix[map.exit_x][map.exit_y].number);
                    if (aux < shortest) {
                        shortest = aux;
                    }
                    closeDoor(keylocation[i], graph, map);
                    closeDoor(keylocation[j], graph, map);
                    closeDoor(keylocation[k], graph, map);
                }
            }
        }
    }
    return shortest;
}
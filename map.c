//
// Created by lfmundim on 20/10/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "vinicius.h"

void makeMap(mapT *map){
    int i, j, k=0;

    map->matrix = (cellT**)calloc((size_t)map->size_x,sizeof(cellT*));
    for(i=0; i<map->size_x; i++)
        map->matrix[i] = (cellT*)calloc((size_t)map->size_y,sizeof(cellT));

    for(i=0; i<map->size_x; i++){
        for(j=0; j<map->size_y; j++){
            map->matrix[i][j].key[0] = '#';
            map->matrix[i][j].wormhole = false;
            map->matrix[i][j].number = k;
            k++;
        }
    }
}

void freeMap(mapT *map){
    int i;
    for(i=0; i<map->size_x; i++)
        free(map->matrix[i]);
    free(map->matrix);

}

void fillMap(mapT *map, personT *person){
    int i, j;

    for(i=map->size_x-1; i>=0; i--){
        for(j=0; j<map->size_y; j++){
            scanf(" %c", &map->matrix[i][j].key[0]);
            if(map->matrix[i][j].key[0]>47 && map->matrix[i][j].key[0]<58) {
                scanf(" %c", &map->matrix[i][j].key[1]);
                map->matrix[i][j].wormhole = true;
            }
            else if(map->matrix[i][j].key[0]=='V'){
                person->coord_x = i;
                person->coord_y = j;
            }
            else if(map->matrix[i][j].key[0]=='E'){
                map->exit_x = i;
                map->exit_y = j;
            }
        }
    }

}

void findKeys(mapT map, int *keylocation){
    int i, j, k=0;
    for(i=0; i<map.size_x; i++){
        for(j=0; j<map.size_y; j++){
            if(map.matrix[i][j].key[0]=='c')
                keylocation[k++]=map.matrix[i][j].number;
            if(map.matrix[i][j].key[0]=='d')
                keylocation[k++]=map.matrix[i][j].number;
            if(map.matrix[i][j].key[0]=='h')
                keylocation[k++]=map.matrix[i][j].number;
            if(map.matrix[i][j].key[0]=='s')
                keylocation[k++]=map.matrix[i][j].number;
        }
    }
}
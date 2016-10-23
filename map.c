//
// Created by lfmundim on 20/10/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

void makeMap(mapT *map){
//    int dimensions = map->size_x*map->size_y;
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

void fillMap(mapT *map){
    int i, j;

    for(i=map->size_x-1; i>=0; i--){
        for(j=0; j<map->size_y; j++){
            scanf(" %c", &map->matrix[i][j].key[0]);
            if(map->matrix[i][j].key[0]>47 && map->matrix[i][j].key[0]<58) {
                scanf(" %c", &map->matrix[i][j].key[1]);
                map->matrix[i][j].wormhole = true;
            }
        }
    }

}
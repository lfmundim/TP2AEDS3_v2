//
// Created by lfmundim on 20/10/16.
//

#ifndef TP2_2_MAP_H
#define TP2_2_MAP_H

#include <stdbool.h>
#include "vinicius.h"

typedef struct cellT{
    char key[2];
    bool wormhole;
    int number;
}cellT;

typedef struct mapT{
    int size_x, size_y;
    cellT **matrix;
    int exit_x, exit_y;
}mapT;

void makeMap(mapT *map);

void fillMap(mapT *map, personT *person);

void findKeys(mapT map, int *keylocation);

#endif //TP2_2_MAP_H

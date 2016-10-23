//
// Created by lfmundim on 17/10/16.
//

#include <stdlib.h>
#include "vinicius.h"
#include "map.h"
#include "dijkstra.h"

void makePerson(personT *person, int key_n){
    person->keys = (char*)calloc((size_t)key_n,sizeof(char));
}

void freePerson(personT *person) {
    free(person->keys);
}


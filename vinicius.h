//
// Created by lfmundim on 17/10/16.
//

#ifndef TP2_VINICIUS_H
#define TP2_VINICIUS_H

typedef struct personT{
    char *keys;
    int coord_x, coord_y;
    int key_n;
}personT;

void makePerson(personT *person, int key_n);

void freePerson(personT *person);

//void walking(int *keylocation, graphT *graph, mapT map, personT *vinicius, int *shortest);

#endif //TP2_VINICIUS_H

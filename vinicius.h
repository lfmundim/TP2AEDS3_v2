//
// Created by lfmundim on 17/10/16.
//

#ifndef TP2_VINICIUS_H
#define TP2_VINICIUS_H

typedef struct personT{
    char *keys;
    int coord_x, coord_y;
    int time;
}personT;

void makePerson(personT *person, int key_n);

void freePerson(personT *person);

#endif //TP2_VINICIUS_H

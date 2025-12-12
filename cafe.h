#ifndef CAFE_H
#define CAFE_H

typedef struct Item {
    int id;
    char name[50];
    float price;
    struct Item* next;
} Item;

extern Item* head;

void init();
void show();
void add();
void find();
void del();
void save();

#endif
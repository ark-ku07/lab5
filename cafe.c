#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cafe.h"

Item* head = NULL;
int id_count = 1;

void init() {
    FILE* f = fopen("db.txt", "r");
    if (!f) return;
    
    Item* last = NULL;
    while (1) {
        Item* new = (Item*)malloc(sizeof(Item));
        if (!new) break;
        
        int res = fscanf(f, "%d %s %f", &new->id, new->name, &new->price);
        if (res != 3) { free(new); break; }
        
        new->next = NULL;
        
        if (!head) head = new;
        else last->next = new;
        last = new;
        
        if (new->id >= id_count) id_count = new->id + 1;
    }
    fclose(f);
}

void show() {
    Item* p = head;
    if (!p) { printf("Pusto\n"); return; }
    
    while (p) {
        printf("%d. %s - %.2f\n", p->id, p->name, p->price);
        p = p->next;
    }
}

void add() {
    Item* new = (Item*)malloc(sizeof(Item));
    new->id = id_count++;
    
    printf("Nazvanie: "); scanf("%s", new->name);
    printf("Tsena: "); scanf("%f", &new->price);
    
    new->next = NULL;
    
    if (!head) head = new;
    else {
        Item* p = head;
        while (p->next) p = p->next;
        p->next = new;
    }
    save();
}

Item* find_id(int id) {
    Item* p = head;
    while (p && p->id != id) p = p->next;
    return p;
}

void find() {
    int t; scanf("%d", &t);
    
    if (t == 1) {
        int id; scanf("%d", &id);
        Item* f = find_id(id);
        printf(f ? "Naideno: %s\n" : "Net\n", f->name);
    } else {
        float price; scanf("%f", &price);
        Item* p = head;
        while (p) {
            if (p->price <= price) printf("%d. %s\n", p->id, p->name);
            p = p->next;
        }
    }
}

void del() {
    int id; scanf("%d", &id);
    
    if (!head) { printf("Net\n"); return; }
    
    if (head->id == id) {
        Item* t = head;
        head = head->next;
        free(t);
        save();
        return;
    }
    
    Item* p = head;
    while (p->next && p->next->id != id) p = p->next;
    
    if (!p->next) { printf("Net\n"); return; }
    
    Item* t = p->next;
    p->next = t->next;
    free(t);
    save();
}

void save() {
    FILE* f = fopen("db.txt", "w");
    Item* p = head;
    while (p) {
        fprintf(f, "%d %s %.2f\n", p->id, p->name, p->price);
        p = p->next;
    }
    fclose(f);
}
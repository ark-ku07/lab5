#ifndef CAFE_H
#define CAFE_H
#define FILE_NAME "menu.txt"

typedef struct Item {
    int id;
    char name[50];
    float price;
    char category[30];
    struct Item* next;
} Item;

typedef struct Menu {
    Item* head;
    int next_id;
} Menu;

void init_menu(Menu* menu);
void show(Menu* menu);
void add(Menu* menu);
void edit(Menu* menu);
void find_by_price(Menu* menu);
void find_by_category(Menu* menu);
void del(Menu* menu);
void save(Menu* menu);
void load(Menu* menu);

#endif

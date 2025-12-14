#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cafe.h"

void init_menu(Menu* menu) {
    menu->head = NULL;
    menu->next_id = 1;
}

void show(Menu* menu) {
    if (menu->head == NULL) {
        printf("Pusto.\n");
        return;
    }
    
    printf("\nMenu:\n");
    Item* current = menu->head;
    while (current != NULL) {
        printf("%d. %s - %.2f rub. [%s]\n",
               current->id, current->name, current->price, current->category);
        current = current->next;
    }
}

void add(Menu* menu) {
    Item* new_item = (Item*)malloc(sizeof(Item));
    if (new_item == NULL) {
        printf("Oshibka pamyati.\n");
        return;
    }
    
    new_item->id = menu->next_id++;
    
    printf("Nazvanie: ");
    scanf("%s", new_item->name);
    printf("Cena: ");
    scanf("%f", &new_item->price);
    printf("Kategoriya: ");
    scanf("%s", new_item->category);
    
    new_item->next = menu->head;
    menu->head = new_item;
    
    printf("Dobavleno.\n");
}

void edit(Menu* menu) {
    int id;
    printf("ID dlya redaktirovaniya: ");
    scanf("%d", &id);
    
    Item* current = menu->head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Novoe nazvanie: ");
            scanf("%s", current->name);
            printf("Novaya cena: ");
            scanf("%f", &current->price);
            printf("Novaya kategoriya: ");
            scanf("%s", current->category);
            printf("Izmeneno.\n");
            return;
        }
        current = current->next;
    }
    printf("Ne najdeno.\n");
}

void find_by_price(Menu* menu) {
    float price;
    printf("Cena dlya poiska: ");
    scanf("%f", &price);
    
    Item* current = menu->head;
    while (current != NULL) {
        if (current->price == price) {
            printf("Najdeno: %s (id: %d, kategoriya: %s)\n",
                   current->name, current->id, current->category);
            return;
        }
        current = current->next;
    }
    printf("Ne najdeno.\n");
}

void find_by_category(Menu* menu) {
    char category[30];
    printf("Kategoriya dlya poiska: ");
    scanf("%s", category);
    
    Item* current = menu->head;
    int found = 0;
    
    printf("\nRezultaty poiska (kategoriya = %s):\n", category);
    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            printf("ID: %d | %s | %.2f rub\n",
                   current->id, current->name, current->price);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Ne najdeno.\n");
    }
}

void del(Menu* menu) {
    int id;
    printf("ID dlya udaleniya: ");
    scanf("%d", &id);
    
    Item* current = menu->head;
    Item* prev = NULL;
    
    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                menu->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Udaleno.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Ne najdeno.\n");
}

void save(Menu* menu) {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Oshibka sohraneniya.\n");
        return;
    }
    
    Item* current = menu->head;
    while (current != NULL) {
        fprintf(file, "%d %s %.2f %s\n",
                current->id, current->name, current->price, current->category);
        current = current->next;
    }
    
    fclose(file);
    printf("Sohraneno v %s.\n", FILE_NAME);
}

void load(Menu* menu) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Fayla %s net.\n", FILE_NAME);
        return;
    }
    
    while (menu->head != NULL) {
        Item* temp = menu->head;
        menu->head = menu->head->next;
        free(temp);
    }
    
    int id;
    char name[50], category[30];
    float price;
    menu->next_id = 1;
    
    while (fscanf(file, "%d %s %f %s", &id, name, &price, category) == 4) {
        Item* new_item = (Item*)malloc(sizeof(Item));
        new_item->id = id;
        strcpy(new_item->name, name);
        new_item->price = price;
        strcpy(new_item->category, category);
        new_item->next = menu->head;
        menu->head = new_item;
        
        if (id >= menu->next_id) {
            menu->next_id = id + 1;
        }
    }
    
    fclose(file);
    printf("Zagruzheno iz %s.\n", FILE_NAME);
}

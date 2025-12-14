#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cafe.h"

int get_int(const char* prompt) {
    char buf[20];
    int val;
    while (1) {
        printf("%s", prompt);
        scanf("%s", buf);
        if (sscanf(buf, "%d", &val) == 1) return val;
        printf("Vvedite chislo!\n");
    }
}

float get_float(const char* prompt) {
    char buf[20];
    float val;
    while (1) {
        printf("%s", prompt);
        scanf("%s", buf);
        if (sscanf(buf, "%f", &val) == 1 && val > 0) return val;
        printf("Nekorrektnaya cena!\n");
    }
}

void init_menu(Menu* m) {
    m->head = NULL;
    m->next_id = 1;
    
    FILE* f = fopen("db.txt", "r");
    if (f == NULL) return;
    
    Item* last = NULL;
    int id; char name[50], cat[30]; float price;
    
    while (fscanf(f, "%d %s %f %s", &id, name, &price, cat) == 4) {
        Item* temp = (Item*)malloc(sizeof(Item));
        if (temp == NULL) break;
        
        temp->id = id;
        strcpy(temp->name, name);
        temp->price = price;
        strcpy(temp->category, cat);
        temp->next = NULL;
        
        if (m->head == NULL) {
            m->head = temp;
        } else {
            last->next = temp;
        }
        last = temp;
        
        if (temp->id >= m->next_id) {
            m->next_id = temp->id + 1;
        }
    }
    
    fclose(f);
}

void show(Menu* m) {
    Item* temp = m->head;
    
    if (temp == NULL) {
        printf("Pusto\n");
        return;
    }
    
    while (temp != NULL) {
        printf("%d %s %.2f [%s]\n", temp->id, temp->name, temp->price, temp->category);
        temp = temp->next;
    }
}

void add(Menu* m) {
    Item* new_item = (Item*)malloc(sizeof(Item));
    if (new_item == NULL) {
        printf("Oshibka pamyati\n");
        return;
    }
    
    new_item->id = m->next_id;
    m->next_id++;
    
    printf("Vvedite nazvanie: ");
    scanf("%s", new_item->name);
    new_item->price = get_float("Vvedite tsenu: ");
    printf("Vvedite kategoriyu: ");
    scanf("%s", new_item->category);
    
    new_item->next = NULL;
    
    if (m->head == NULL) {
        m->head = new_item;
    } else {
        Item* temp = m->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_item;
    }
    
    printf("Dobavleno.\n");
    save(m);
}

Item* findbyid(Menu* m, int id) {
    Item* temp = m->head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void edit(Menu* m) {
    int id = get_int("ID dlya redaktirovaniya: ");
    Item* item = findbyid(m, id);
    if (item == NULL) {
        printf("Ne naideno\n");
        return;
    }
    
    printf("Novoe nazvanie: ");
    scanf("%s", item->name);
    item->price = get_float("Novaya tsena: ");
    printf("Novaya kategoriya: ");
    scanf("%s", item->category);
    printf("Izmeneno.\n");
    save(m);
}

void find(Menu* m) {
    int choice = get_int("1 - po ID, 2 - po tsene, 3 - po kategorii: ");
    
    if (choice == 1) {
        int id = get_int("Vvedite ID: ");
        Item* result = findbyid(m, id);
        if (result == NULL) {
            printf("Ne naideno\n");
        } else {
            printf("Naideno: %s %.2f [%s]\n", result->name, result->price, result->category);
        }
    } else if (choice == 2) {
        float max_price = get_float("Maksimalnaya tsena: ");
        
        Item* temp = m->head;
        int found = 0;
        while (temp != NULL) {
            if (temp->price <= max_price) {
                printf("%d %s %.2f [%s]\n", temp->id, temp->name, temp->price, temp->category);
                found = 1;
            }
            temp = temp->next;
        }
        if (found == 0) {
            printf("Net tovarov\n");
        }
    } else if (choice == 3) {
        char category[30];
        printf("Vvedite kategoriyu: ");
        scanf("%s", category);
        
        Item* temp = m->head;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->category, category) == 0) {
                printf("%d %s %.2f\n", temp->id, temp->name, temp->price);
                found = 1;
            }
            temp = temp->next;
        }
        if (found == 0) {
            printf("Net tovarov\n");
        }
    } else {
        printf("Nepravilniy vibor\n");
    }
}

void del(Menu* m) {
    int id = get_int("Vvedite ID dlya udaleniya: ");
    
    if (m->head == NULL) {
        printf("Spisok pust\n");
        return;
    }
    
    if (m->head->id == id) {
        Item* temp = m->head;
        m->head = m->head->next;
        free(temp);
        printf("Udaleno\n");
        save(m);
        return;
    }
    
    Item* current = m->head;
    while (current->next != NULL) {
        if (current->next->id == id) {
            Item* temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("Udaleno\n");
            save(m);
            return;
        }
        current = current->next;
    }
    
    printf("Element ne naiden\n");
}

void save(Menu* m) {
    FILE* f = fopen("db.txt", "w");
    if (f == NULL) {
        printf("Oshibka sohraneniya\n");
        return;
    }
    
    Item* temp = m->head;
    while (temp != NULL) {
        fprintf(f, "%d %s %.2f %s\n", temp->id, temp->name, temp->price, temp->category);
        temp = temp->next;
    }
    
    fclose(f);
}

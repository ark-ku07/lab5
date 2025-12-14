#include <stdio.h>
#include <stdlib.h>
#include "cafe.h"

int main() {
    Menu cafe_menu;
    init_menu(&cafe_menu);
    
    int choice;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Pokazat vse\n");
        printf("2. Dobavit noviy\n");
        printf("3. Redaktirovat\n");
        printf("4. Naiti\n");
        printf("5. Udalit\n");
        printf("0. Vihod\n");
        printf("Vash vibor: ");
        
        char input[20];
        scanf("%s", input);
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Vvedite chislo!\n");
            continue;
        }
        
        if (choice == 0) {
            save(&cafe_menu);
            break;
        } else if (choice == 1) {
            show(&cafe_menu);
        } else if (choice == 2) {
            add(&cafe_menu);
        } else if (choice == 3) {
            edit(&cafe_menu);
        } else if (choice == 4) {
            find(&cafe_menu);
        } else if (choice == 5) {
            del(&cafe_menu);
        } else {
            printf("Nepravilniy vibor\n");
        }
    }
    
    while (cafe_menu.head != NULL) {
        Item* temp = cafe_menu.head;
        cafe_menu.head = cafe_menu.head->next;
        free(temp);
    }
    
    return 0;
}

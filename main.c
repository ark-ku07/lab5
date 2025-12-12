#include <stdio.h>
#include <stdlib.h> 
#include "cafe.h"

int main() {
    int choice;
    init();
    
    while (1) {
        printf("\n1.Pokazat 2.Dobavit 3.Poisk 4.Udalit 0.Vyhod\nVybor: ");
        scanf("%d", &choice);
        
        if (choice == 0) { save(); printf("Vyhod\n"); break; }
        if (choice == 1) show();
        else if (choice == 2) add();
        else if (choice == 3) find();
        else if (choice == 4) del();
        else printf("Neverno\n");
    }
    
    while (head) {
        Item* tmp = head;
        head = head->next;
        free(tmp);
    }
    
    return 0;
}

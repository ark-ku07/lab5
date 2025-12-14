#include <stdio.h>
#include "cafe.h"

int main() {
    Menu cafe_menu;
    init_menu(&cafe_menu);
    
    int choice;
    
    do {
        printf("\n1. Pokazat menu\n");
        printf("2. Dobavit bludo\n");
        printf("3. Redaktirovat bludo\n");
        printf("4. Najti po cene\n");
        printf("5. Najti po kategorii\n");
        printf("6. Udalit bludo\n");
        printf("7. Sohranit v fayl\n");
        printf("8. Zagruzit iz fayla\n");
        printf("0. Vihod\n");
        printf("Vash vibor: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: show(&cafe_menu); break;
            case 2: add(&cafe_menu); break;
            case 3: edit(&cafe_menu); break;
            case 4: find_by_price(&cafe_menu); break;
            case 5: find_by_category(&cafe_menu); break;
            case 6: del(&cafe_menu); break;
            case 7: save(&cafe_menu); break;
            case 8: load(&cafe_menu); break;
            case 0: save(&cafe_menu); printf("Do svidaniya!\n"); break;
            default: printf("Nekorrektniy vibor.\n");
        }
    } while (choice != 0);
    
    return 0;
}

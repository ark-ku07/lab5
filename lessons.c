#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Ошибка\n");
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Ошибка\n");
        return 1;
    }
    
    int n, m;
    if (fscanf(f, "%d%d", &n, &m) != 2  n <= 0  m <= 0) {
        printf("Ошибка\n");
        fclose(f);
        return 1;
    }
    
    int **a = (int**)malloc(n * sizeof(int*));
    if (a == NULL) {
        printf("Ошибка\n");
        fclose(f);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(m * sizeof(int));
        if (a[i] == NULL) {
            printf("Ошибка\n");
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            fclose(f);
            return 1;
        }
        for (int j = 0; j < m; j++) {
            if (fscanf(f, "%d", &a[i][j]) != 1) {
                printf("Ошибка\n");
                for (int k = 0; k <= i; k++) free(a[k]);
                free(a);
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);

    if (n <= 2) {
        printf("Ошибка\n");
        for (int i = 0; i < n; i++) free(a[i]);
        free(a);
        return 1;
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < m; j++)
            if (a[i][j] < 0) sum += a[i][j];

    int max_j = 0;
    for (int j = 1; j < m; j++)
        if (a[2][j] > a[2][max_j]) max_j = j;

    a[2][max_j] = sum;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
        free(a[i]);
    }
    free(a);
    
    return 0;
}

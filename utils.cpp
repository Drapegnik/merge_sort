//
// Created by Ivan Pazhitnykh on 25.09.16.
//


#include <cstdio>

void print(int *data, int length, bool isEndl) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", data[i]);
        if (i != length - 1)
            printf(" ");
    }

    printf("]");
    if (isEndl)
        printf("\n");
}

void print_line(int before, int length, int after) {
    for (int i = 0; i < before; i++)
        printf("\n");
    for (int i = 0; i < length; i++)
        printf("-");
    for (int i = 0; i < after; i++)
        printf("\n");
}

void print_master() {
    printf("$\033[1;31m master\033[0m:");
}
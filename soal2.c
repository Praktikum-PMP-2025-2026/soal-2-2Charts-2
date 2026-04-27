#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Meteorite {
    char* name;
    int mass;
    int purity;
} Meteorite;

typedef struct Array_Meteorite {
    Meteorite* data;
    size_t len;
    size_t cap;
} Array_Meteorite;

Array_Meteorite am_reserve(Array_Meteorite arr, size_t len) {
    if(arr.cap - arr.len < len) {
        if(arr.cap <= 0) 
            arr.cap = 8;

        while(arr.cap - arr.len < len) arr.cap *= 2;

        arr.data = realloc(arr.data, sizeof(*arr.data) * arr.cap);
    }
    return arr;
}

Array_Meteorite am_append(Array_Meteorite arr, Meteorite met) {
    arr = am_reserve(arr, 1);

    arr.data[arr.len++] = met;
    return arr;
}

Array_Meteorite am_bubble_sort(Array_Meteorite arr) {
    for(size_t i = 0; i < arr.len; ++i) {
        for(size_t j = 0; j < arr.len - i - 1; ++j) {
            // highest to lowest
            if(arr.data[j].purity < arr.data[j + 1].purity) {
                Meteorite temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
            else if(arr.data[j].purity == arr.data[j + 1].purity &&
                    arr.data[j].mass > arr.data[j + 1].mass) {
                Meteorite temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
            else if(arr.data[j].purity == arr.data[j + 1].purity && 
                    arr.data[j].mass == arr.data[j + 1].mass && 
                    strcmp(arr.data[j].name, arr.data[j+1].name) > 0) {
                Meteorite temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
        }
    }

    return arr;
}

int main(void) {
    Array_Meteorite am = {0};
    int N = 0;
    scanf("%d", &N);

    am = am_reserve(am, N);

    for(size_t i = 0; i < N; ++i) {
        Meteorite met = {0};
        met.name = malloc(5120);
        scanf("%s %d %d", met.name, &met.mass, &met.purity);
        am = am_append(am, met);
    }

    am = am_bubble_sort(am);
    for(size_t i = 0, j = 0; j < 3 && i < am.len; ++i, ++j) {
        printf("%s %d %d\n", am.data[i].name, am.data[i].mass, am.data[i].purity);
    }

    return 0;
}

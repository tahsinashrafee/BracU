#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int checkP2(int x);
int *dTob(int n,int l);
int bTod(int a[],int l);

int main() {
    int pgs = 4; 
    int ms = 32; 
    int nof = ms / pgs; 
    int offset_bit = 0;
    while ((1 << offset_bit) < pgs) {
        offset_bit++;
    }
    int pg_num_bit = 0;
    while ((1 << pg_num_bit) < nof) {
        pg_num_bit++;
    }
    int la[] = {8, 4, 3, 2, 15, 18, 25}; 
    int pmt[] = {3, 6, 8, 12, 2};

    int logical_address_count = sizeof(la) / sizeof(la[0]);

    printf("Output:\n");

    printf("Page size: %d\n", pgs);
    printf("Memory size: %d\n", ms);
    printf("Number of frames required: %d\n", nof);
    printf("Page number bits: %d\n", pg_num_bit);
    printf("Offset bits: %d\n", offset_bit);
    printf("Number of address spaces: %zu\n", sizeof(pmt) / sizeof(pmt[0]));

    printf("Page Table_____\n");
    for (int i = 0; i < (sizeof(pmt) / sizeof(pmt[0])); i++) {
        printf("%d -> %d\n", i, pmt[i]);
    }

    for (int i = 0; i < logical_address_count; i++) {
        int logical_address = la[i];

        int page_number = logical_address >> offset_bit; 
        int offset = logical_address & ((1 << offset_bit) - 1); 

        if (page_number >= (sizeof(pmt) / sizeof(pmt[0]))) {
            printf("%d has an invalid page number\n", page_number);
            continue;
        }
        int frame_number = pmt[page_number];
        int physical_address = (frame_number * pgs) + offset;

        if (physical_address >= ms) {
            printf("%d is an invalid physical address\n", physical_address);
            continue;
        }
        
        
        printf("Corresponding physical address of logical address %d: %d\n", logical_address, physical_address);
    }

    return 0;
}

int checkP2(int x) {
    return (x && !(x & (x - 1)));
}

int *dTob(int n, int l) {
    static int arr[32]; // 
    for (int i = l - 1; i >= 0; i--) {
        arr[i] = n % 2;
        n /= 2;
    }
    return arr;
}

int bTod(int a[], int l) {
    int value = 0;
    for (int i = 0; i < l; i++) {
        value = (value << 1) + a[i];
    }
    return value;
}


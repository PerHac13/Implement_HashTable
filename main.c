#include "./src/hash_table.h"
#include "./src/prime.h"
#include<stdio.h>

int main() {
    hash_table* ht = ht_new_table();
    ht_del_table(ht);
    printf("Working\n");
}
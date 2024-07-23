#include "./src/hash_table.h"

int main() {
    hash_table* ht = ht_new_table();
    ht_del_table(ht);
}
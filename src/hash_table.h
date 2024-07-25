// Include guards to your hash_table.h file to prevent multiple inclusions
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} ht_entry;

typedef struct {
    ht_entry** entries;
    unsigned int entry_count;
    unsigned int size;
} hash_table;

hash_table* ht_new_table();
void ht_del_table(hash_table* ht);

// api functions
void ht_insert(hash_table* ht, const char* key, const char* value);
char* ht_search(hash_table* ht, const char* key);
void ht_delete(hash_table* ht, const char* key);

#endif
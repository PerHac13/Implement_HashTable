
#include<stdlib.h>
#include<stdio.h>

#include "hash_table.h"

// creating the entry for the hash table
static ht_entry* ht_new_entry(const char* key, const char* value) {
    ht_entry* entry = malloc(sizeof(ht_entry));
    entry->key = strdup(key);
    entry->value = strdup(value);

    return entry;
}

//creating the hash table
hash_table* ht_new_table(){
    hash_table* ht = malloc(sizeof(hash_table));
    ht->size = 43;
    ht->entry_count = 0;
    ht->entries = calloc((size_t)ht->size, sizeof(ht_entry*));

    return ht;
}

// deleting the entry
static void ht_del_entry(ht_entry* entry) {
    free(entry->key);
    free(entry->value);
    free(entry);
}

// deleting the hash table
void ht_del_table(hash_table* ht) {
    for(int i = 0; i < ht->size; i++) {
        ht_entry* entry = ht->entries[i];
        if(entry != NULL) {
            ht_del_entry(entry);
        }
    }
    free(ht->entries);
    free(ht);
}


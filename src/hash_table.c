
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

// hash function
static int ht_hash(const char* key, const int prime, const int num_buckets) {
    long hash = 0;
    const int len_s = strlen(key);
    for(int i = 0; i < len_s; i++) {
        hash += (long)pow(prime, len_s - (i+1)) * key[i];
        hash = hash % num_buckets;
    }
    return (int)hash;
}

// double hashing function to avoid collisions
static int ht_get_hash(const char* key, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(key, 151, num_buckets);
    const int hash_b = ht_hash(key, 163, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}


// inserting the key and value function
void ht_insert(hash_table* ht, const char* key, const char* value) {
    ht_entry* entry = ht_new_entry(key, value);
    int index = ht_get_hash(entry->key, ht->size, 0);
    ht_entry* existing_entry = ht->entries[index];
    int i = 1;
    while(existing_entry != NULL) {
        if(existing_entry != &Ht_Del_entry) {
            if(strcmp(existing_entry->key, key) == 0) {
                ht_del_entry(existing_entry);
                ht->entries[index] = entry;
                return;
            }
        }
        index = ht_get_hash(entry->key, ht->size, i);
        existing_entry = ht->entries[index];
        i++;
    }
    ht->entries[index] = entry;
    ht->entry_count++;
}

// creating a dummy entry to delete the key to avoid breaking of collision chain

static ht_entry Ht_Del_entry = {NULL, NULL};

// searching the key function
char* ht_search(hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_entry* entry = ht->entries[index];
    int i = 1;
    while(entry != NULL) {
        if(entry != &Ht_Del_entry) {
        if(strcmp(entry->key, key) == 0) {
            return entry->value;}
        }
        index = ht_get_hash(key, ht->size, i);
        entry = ht->entries[index];
        i++;
    }
    return NULL;
}

// deleting the key function
void ht_delete(hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_entry* entry = ht->entries[index];
    int i = 1;
    while(entry != NULL){
        if(entry != &Ht_Del_entry) {
            if(strcmp(entry->key, key) == 0) {
                ht_del_entry(entry);
                ht->entries[index] = &Ht_Del_entry;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        entry = ht->entries[index];
        i++;
    }
    ht->entry_count--;
}


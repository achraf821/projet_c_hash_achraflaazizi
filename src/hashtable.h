#define _GNU_SOURCE

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

// Table simple : clé = hex hash (string), valeur = mot (string)


typedef struct hashtable_t hashtable_t;


hashtable_t *ht_create(size_t buckets);
void ht_destroy(hashtable_t *ht);
int ht_insert(hashtable_t *ht, const char *hash_hex, const char *word);
const char *ht_lookup(hashtable_t *ht, const char *hash_hex);


#endif
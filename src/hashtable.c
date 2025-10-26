#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>


typedef struct node { char *key; char *val; struct node *next; } node;
struct hashtable_t { node **buckets; size_t nb; };


static unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}


hashtable_t *ht_create(size_t buckets) {
    hashtable_t *ht = malloc(sizeof(*ht));
    ht->nb = buckets;
    ht->buckets = calloc(buckets, sizeof(node*));
    return ht;
}


void ht_destroy(hashtable_t *ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->nb; ++i) {
        node *n = ht->buckets[i];
        while (n) {
            node *tmp = n->next;
            free(n->key); free(n->val); free(n);
            n = tmp;
        }
    }
    free(ht->buckets); free(ht);
}


int ht_insert(hashtable_t *ht, const char *hash_hex, const char *word) {
    unsigned long h = djb2(hash_hex) % ht->nb;
    node *n = ht->buckets[h];
    while (n) {
        if (strcmp(n->key, hash_hex) == 0) return 0; // déjà présent
        n = n->next;
    }
    node *nn = malloc(sizeof(*nn));
    nn->key = strdup(hash_hex);
    nn->val = strdup(word);
    nn->next = ht->buckets[h];
    ht->buckets[h] = nn;
    return 1;
}


const char *ht_lookup(hashtable_t *ht, const char *hash_hex) {
    unsigned long h = djb2(hash_hex) % ht->nb;
    node *n = ht->buckets[h];
    while (n) {
        if (strcmp(n->key, hash_hex) == 0) return n->val;
        n = n->next;
    }
    return NULL;
}
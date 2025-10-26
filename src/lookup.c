#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

// charge la T3C (format: mot;hexhash) dans une hashtable
hashtable_t *load_t3c(const char *t3c_path) {
    FILE *f = fopen(t3c_path, "r");
    if (!f) return NULL;

    hashtable_t *ht = ht_create(200003); // grand nombre de buckets
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {
        char *sep = strchr(line, ';');
        if (!sep) continue;
        *sep = '\0';
        char *word = line;
        char *hash = sep + 1;

        // supprime \n ou \r en fin de hash
        size_t hl = strlen(hash);
        while (hl > 0 && (hash[hl - 1] == '\n' || hash[hl - 1] == '\r'))
            hash[--hl] = '\0';

        ht_insert(ht, hash, word);
    }

    free(line);
    fclose(f);
    return ht;
}

// lit des hashes depuis stdin et affiche le mot si trouvé
int lookup_from_stdin(hashtable_t *ht) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        size_t l = strlen(line);
        while (l > 0 && (line[l - 1] == '\n' || line[l - 1] == '\r'))
            line[--l] = '\0';
        if (l == 0) continue;

        const char *res = ht_lookup(ht, line);
        if (res)
            printf("%s → %s\n", line, res);
        else
            printf("%s → <NOTFOUND>\n", line);
    }

    free(line);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "hashtable.h"


int generate_from_dict(const char *dict_path, const char *out_path);
hashtable_t *load_t3c(const char *t3c_path);
int lookup_from_stdin(hashtable_t *ht);


void usage(const char *p) {
    fprintf(stderr, "Usage:\n %s G dictionnaire.txt sortie.t3c\n %s L table.t3c < hashes.txt\n", p, p);
}


int main(int argc, char **argv) {
    if (argc < 2) { usage(argv[0]); return 1; }
    if (strcmp(argv[1], "G") == 0) {
        if (argc != 4) { usage(argv[0]); return 2; }
        const char *dict = argv[2];
        const char *out = argv[3];
        int r = generate_from_dict(dict, out);
        if (r != 0) { fprintf(stderr, "Erreur generate: %d\n", r); return 10; }
        return 0;
    } else if (strcmp(argv[1], "L") == 0) {
        if (argc != 3) { usage(argv[0]); return 2; }
        hashtable_t *ht = load_t3c(argv[2]);
        if (!ht) { fprintf(stderr, "Impossible de charger T3C\n"); return 11; }
        lookup_from_stdin(ht);
        ht_destroy(ht);
        return 0;
    } else {
        usage(argv[0]); return 1;
    }
}
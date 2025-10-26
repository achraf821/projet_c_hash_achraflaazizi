#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "hashtable.h"

// prototypes
int generate_from_dict(const char *dict_path, const char *out_path, const char *algo);
hashtable_t *load_t3c(const char *t3c_path);
int lookup_from_stdin(hashtable_t *ht);

void usage(const char *p) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s G dictionnaire.txt sortie.t3c [algo]\n", p);
    fprintf(stderr, "     algo = sha256 (defaut), sha1, md5\n");
    fprintf(stderr, "  %s L table.t3c < hashes.txt\n", p);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    // Mode G : génération de condensats
    if (strcmp(argv[1], "G") == 0) {
        if (argc < 4 || argc > 5) {
            usage(argv[0]);
            return 2;
        }

        const char *dict = argv[2];
        const char *out = argv[3];
        const char *algo = (argc == 5) ? argv[4] : "sha256";

        printf("🧮 Génération des condensats avec l’algo %s...\n", algo);
        int r = generate_from_dict(dict, out, algo);
        if (r != 0) {
            fprintf(stderr, "Erreur generate: %d\n", r);
            return 10;
        }
        printf("✅ Table T3C générée → %s\n", out);
        return 0;
    }

    // Mode L : lookup
    else if (strcmp(argv[1], "L") == 0) {
        if (argc != 3) {
            usage(argv[0]);
            return 2;
        }

        hashtable_t *ht = load_t3c(argv[2]);
        if (!ht) {
            fprintf(stderr, "❌ Impossible de charger T3C\n");
            return 11;
        }

        printf("🔎 Lecture des condensats depuis stdin...\n");
        lookup_from_stdin(ht);
        ht_destroy(ht);
        return 0;
    }

    else {
        usage(argv[0]);
        return 1;
    }
}

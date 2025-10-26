#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "hash.h"

// lit `dict_path`, génère le condensat selon l’algo choisi et écrit mot;hexhash dans out_path
int generate_from_dict(const char *dict_path, const char *out_path, const char *algo) {
    FILE *f = fopen(dict_path, "r");
    if (!f) return -1;
    FILE *o = fopen(out_path, "w");
    if (!o) { fclose(f); return -2; }

    // si aucun algo précisé → sha256 par défaut
    if (!algo) algo = "sha256";

    char *line = NULL; 
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        // enlève les \n et \r
        while (read > 0 && (line[read - 1] == '\n' || line[read - 1] == '\r')) {
            line[--read] = '\0';
        }
        if (read == 0) continue;

        // sélection de l’algorithme de hachage
        char *h = NULL;
        if (strcmp(algo, "md5") == 0)
            h = md5_hex(line);
        else if (strcmp(algo, "sha1") == 0)
            h = sha1_hex(line);
        else
            h = sha256_hex(line); // défaut

        if (!h) {
            free(line);
            fclose(f);
            fclose(o);
            return -3;
        }

        fprintf(o, "%s;%s\n", line, h);
        free(h);
    }

    free(line);
    fclose(f);
    fclose(o);
    return 0;
}

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "hash.h"


// lit `dict_path`, génère le sha256 pour chaque ligne et écrit selon la structure mot;hexsha dans out_path
int generate_from_dict(const char *dict_path, const char *out_path) {
    FILE *f = fopen(dict_path, "r");
    if (!f) return -1;
    FILE *o = fopen(out_path, "w");
    if (!o) { fclose(f); return -2; }


    char *line = NULL; size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) {
        // enlève les \n et les \r
        while (read > 0 && (line[read-1] == '\n' || line[read-1] == '\r')) { line[--read] = '\0'; }
        if (read == 0) continue;
        char *h = sha256_hex(line);
        if (!h) { free(line); fclose(f); fclose(o); return -3; }
        fprintf(o, "%s;%s\n", line, h);
        free(h);
    }
    free(line);
    fclose(f);
    fclose(o);
    return 0;
}
#ifndef HASH_H
#define HASH_H


#include <stddef.h>


// calcule SHA256 de `input` (null-terminated) et retourne une chaîne hex allouée
// L'appelant doit free() la chaîne retournée.

char *sha256_hex(const char *input);
char *sha1_hex(const char *input);
char *md5_hex(const char *input);

#endif // HASH_H
#include "hash.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char *sha256_hex(const char *input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) return NULL;
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);


    char *out = malloc(SHA256_DIGEST_LENGTH*2 + 1);
    if (!out) return NULL;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    sprintf(out + (i * 2), "%02x", hash[i]);
    out[SHA256_DIGEST_LENGTH*2] = '\0';
    return out;
}
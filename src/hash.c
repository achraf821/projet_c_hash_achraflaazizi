#include "hash.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
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


// SHA1
char *sha1_hex(const char *input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, input, strlen(input));
    SHA1_Final(hash, &ctx);

    char *out = malloc(SHA_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(out + (i * 2), "%02x", hash[i]);
    out[SHA_DIGEST_LENGTH * 2] = '\0';
    return out;
}

// MD5
char *md5_hex(const char *input) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, input, strlen(input));
    MD5_Final(hash, &ctx);

    char *out = malloc(MD5_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(out + (i * 2), "%02x", hash[i]);
    out[MD5_DIGEST_LENGTH * 2] = '\0';
    return out;
}
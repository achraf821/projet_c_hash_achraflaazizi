Projet C – Génération et recherche de condensats

Description :

Programme en langage C permettant :

Mode G (Generate) : générer les condensats SHA256 d’un dictionnaire de mots.

Mode L (Lookup) : retrouver les mots d’origine à partir de leurs condensats via un fichier .t3c.

Compilation :

make
ou bien
gcc -std=c17 -O2 -Wall -Wextra -Isrc src/*.c -o prog -lcrypto

Pré-requis : Linux et la bibliothèque OpenSSL (sudo apt install libssl-dev).

Utilisation :

Mode G : Génération

./prog G <fichier_dictionnaire> <fichier_sortie_t3c>

Exemple :

./prog G dict.txt sortie.t3c

Mode L : Recherche

./prog L <fichier_t3c>

Exemples :

echo "2cf24dba5f..." | ./prog L sortie.t3c
cat hashes.txt | ./prog L sortie.t3c

Structure :

README.md
Makefile
src/ (main.c, generate.c, lookup.c, hash.c, hashtable.c, hash.c, hashtable.h)
doc/ (éventuel et optionnel)

Notes :

Utilise getline() (_GNU_SOURCE défini pour compatibilité).

SHA256 via OpenSSL (libcrypto).

Testé sous Linux (Debian/Kali).

Auteur : Achraf LAAZIZI – MSSIS 2025/2026

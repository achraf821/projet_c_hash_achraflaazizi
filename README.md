Génération et Recherche de Condensats Cryptographiques

Auteur : Achraf LAAZIZI
Langage : C
Date : 26 Octobre 2025

1. Objectif du projet

Ce programme permet de générer et de rechercher des condensats (hashes) cryptographiques à partir de chaînes de caractères.
Il propose deux modes de fonctionnement :

Mode G (Generate) : génération des condensats à partir d’un dictionnaire.

Mode L (Lookup) : recherche d’une chaîne d’origine à partir de son condensat.

Le projet met en œuvre les notions de lecture/écriture de fichiers, pointeurs, allocation dynamique, structures, paramètres en ligne de commande et tables de hachage.

2. Fonctionnalités principales
Mode G — Génération

Lecture d’un fichier texte (dictionnaire) contenant une chaîne par ligne.

Calcul du condensat cryptographique pour chaque entrée.

Écriture des couples mot;condensat dans un fichier de sortie (.t3c).

Possibilité de choisir l’algorithme de hachage :

sha256 (par défaut)

sha1

md5

Mode L — Recherche

Chargement d’un fichier .t3c en mémoire dans une table de hachage.

Lecture des condensats depuis l’entrée standard (stdin).

Affichage de la chaîne correspondante si elle est trouvée, ou <NOTFOUND> sinon.


3. Pré-requis

Système d’exploitation : Linux (Debian, Ubuntu, Kali, etc.)

Compilateur : GCC (support du standard C17)

Bibliothèques nécessaires :

OpenSSL (libssl-dev) — utilisée pour les fonctions de hachage (SHA256, SHA1, MD5).

Valgrind (optionnel) — utilisé pour la vérification d’absence de fuites mémoire.

Installation des dépendances :

sudo apt update
sudo apt install -y build-essential gcc make libssl-dev valgrind


Aucun autre pré-requis n’est nécessaire.
Le projet est compilable et exécutable sur toute distribution Linux disposant des dépôts standards Debian.


4. Structure du projet.

├── src/
│   ├── main.c
│   ├── generate.c
│   ├── lookup.c
│   ├── hash.c
│   ├── hashtable.c
│   ├── hash.h
│   └── hashtable.h
├── Makefile
└── README.md


5. Compilation

Compilation via make à la racine du projet :

make


L’exécutable prog est généré à la racine.
Autres commandes disponibles :

make clean   # Supprime les fichiers objets
make fclean  # Supprime les objets et l'exécutable
make re      # Recompile entièrement le projet

6. Utilisation
Mode G — Génération de condensats
./prog G <dictionnaire.txt> <sortie.t3c> [algorithme]


Paramètres :

<dictionnaire.txt> : fichier d’entrée, une chaîne par ligne.

<sortie.t3c> : fichier de sortie contenant les couples mot;condensat.

[algorithme] (optionnel) : sha256 (par défaut), sha1, ou md5.

Exemples :

./prog G dict.txt sortie_sha256.t3c
./prog G dict.txt sortie_sha1.t3c sha1
./prog G dict.txt sortie_md5.t3c md5

Mode L — Recherche de chaînes à partir de condensats
./prog L <table.t3c>


Les condensats sont lus depuis l’entrée standard (stdin).
Chaque ligne doit contenir un condensat, séparé par un saut de ligne.

Exemple :

cat hashes.txt | ./prog L sortie_sha256.t3c

7. Tests de fonctionnement
Exemple simple
echo -e "hello\nworld\npassword123" > test_dict.txt
./prog G test_dict.txt sortie_sha256.t3c
awk -F';' '{print $2}' sortie_sha256.t3c | ./prog L sortie_sha256.t3c

Tests avec les trois algorithmes
./prog G test_dict.txt out_sha256.t3c
./prog G test_dict.txt out_sha1.t3c sha1
./prog G test_dict.txt out_md5.t3c md5

awk -F';' '{print $2}' out_sha256.t3c | ./prog L out_sha256.t3c
awk -F';' '{print $2}' out_sha1.t3c | ./prog L out_sha1.t3c
awk -F';' '{print $2}' out_md5.t3c | ./prog L out_md5.t3c


8. Vérifications de performance et fiabilité
Test sur dictionnaire volumineux

Un test a été effectué avec un extrait de 100 000 mots du fichier rockyou.txt :

head -n 100000 rockyou.txt > rockyou_100k.txt
time ./prog G rockyou_100k.txt sortie_rockyou_100k.t3c


La génération et le lookup se sont déroulés sans erreur, validant la stabilité sur des volumes importants.

Vérification mémoire avec Valgrind

Les tests Valgrind ont été réalisés pour les deux modes (G et L), sur des fichiers de taille moyenne.

Exemple :

valgrind --leak-check=full ./prog G test_dict.txt sortie_valgrind.t3c
valgrind --leak-check=full ./prog L sortie_valgrind.t3c < hashes.txt


Résultat obtenu :

All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts


Aucune fuite mémoire détectée.


9. Architecture du code

main.c : gestion des arguments et sélection du mode (G ou L).

generate.c : lecture du dictionnaire, calcul des condensats, écriture dans la T3C.

lookup.c : chargement de la T3C et recherche par condensat.

hash.c : encapsule les appels OpenSSL pour SHA256, SHA1 et MD5.

hashtable.c : structure de table de hachage dynamique pour le mode L.

L’ensemble du projet est conçu de manière modulaire afin de faciliter l’ajout de nouveaux algorithmes ou structures de données.


10. Approche de développement

Le développement a été réalisé en plusieurs étapes :

Implémentation initiale du mode G et du mode L avec l’algorithme SHA256.

Validation fonctionnelle sur petits fichiers.

Tests de performance sur le dictionnaire rockyou (extrait de 100 000 lignes).

Vérification mémoire complète avec Valgrind.

Extension du module de hachage pour supporter SHA1 et MD5.

Nettoyage du code, structuration du dépôt et documentation finale.


11. Respect des consignes

Le projet respecte l’ensemble des exigences du sujet :

Compilation et exécution sur OS Linux en moins de 15 minutes.

Deux modes (G et L) pleinement opérationnels.

Fichiers sources dans src/.

Présence d’un Makefile et d’un README.md.

Utilisation d’une bibliothèque autorisée (OpenSSL).

Pas de dépendances externes non conformes.


12. Observations complémentaires

Le code est écrit en C standard.

Les lectures de fichiers utilisent getline(), garantissant la compatibilité POSIX.

Les condensats sont produits au format hexadécimal sur 64 caractères pour SHA256.

Le projet a été testé sur environnement Kali Linux (VM VirtualBox) et sur systèmes basés Debian.


13. Informations générales

Auteur : Achraf LAAZIZI
Branche de livraison : master
Langage : C (compilateur gcc)
Licence : Projet académique — INSA / MS SIS
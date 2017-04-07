#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int verifierPermissions(const char *nom);

int main(int argc, char *argv[]){
    char *nom = argv[1];

    if(argc != 2){
        fprintf(stderr, "Nom de repertoire manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if(nftw(nom, verifierPermissions, 1, 0) == -1){
        fprintf(stderr, "Permissions insuffisantes\n");
        return EXIT_FAILURE;
    }

    if(nftw(nom, remove, 1, FTW_DEPTH) == -1){
        fprintf(stderr, "Répertoire introuvable\n");
        return EXIT_FAILURE;
    }

    printf("Répertoire supprimé\n");

    return EXIT_SUCCESS;
}

int verifierPermissions(const char *nom){

    return access(nom, W_OK);
}
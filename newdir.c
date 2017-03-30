#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    char *nom = argv[1];

    if(argc != 2){
        fprintf(stderr, "Nom de répertoire manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if(mkdir(nom, 0755) == -1){
        fprintf(stderr, "Impossible de créer le répertoire\n");
        return EXIT_FAILURE;
    }

    printf("Répertoire créé\n");

    return EXIT_SUCCESS;
}
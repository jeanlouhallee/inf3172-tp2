#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    char *nom = argv[1];

    if(argc != 2){
        fprintf(stderr, "Nom de fichier manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if(open(nom, O_CREAT | O_EXCL, 0644) == -1){
        fprintf(stderr, "Impossible de créer le fichier\n");
        return EXIT_FAILURE;
    }

    return 0;
}
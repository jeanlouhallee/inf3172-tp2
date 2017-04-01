#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>

int nbFichiers = 0;
int taille = 0;

int calculerTaille(const char *nom);

int main(int argc, char *argv[]){
    char *nom = argv[1];

    if(argc != 2){
        fprintf(stderr, "Nom de repertoire manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if(nftw(nom, calculerTaille, 1, 0) == -1){
        fprintf(stderr, "Répertoire introuvable\n");
        return EXIT_FAILURE;
    }

    printf("Le répertoire %s contient %d fichiers pour un total de %d octets.\n", nom, nbFichiers, taille);

    return EXIT_SUCCESS;
}

int calculerTaille(const char *nom){
    struct stat buf;

    stat(nom, &buf);

    if(!S_ISDIR(buf.st_mode)){
        nbFichiers++;
        taille += buf.st_size;
    }

    return 0;
}
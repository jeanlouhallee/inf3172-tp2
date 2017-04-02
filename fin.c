#include <stdlib.h>
#include <stdio.h>

#define MAX_LIGNE 1000 // ???

int main(int argc, char *argv[]){
    FILE* fichier;
    long nbLignes;
    long totalLignes = 0;
    long debutLignes;
    char ligne[MAX_LIGNE];

    if(argc != 3){
        fprintf(stderr, "Arguments manquants ou en trop\n");
        return EXIT_FAILURE;
    }

    if((nbLignes = strtol(argv[1], NULL, 10)) <= 0){
        fprintf(stderr, "Argument invalide\n");
        return EXIT_FAILURE;
    }

    if((fichier = fopen(argv[2], "r")) == NULL){
        fprintf(stderr, "Fichier introuvable\n");
        return EXIT_FAILURE;
    }

    while(fgets(ligne, MAX_LIGNE, fichier) != NULL) totalLignes++;
    debutLignes = totalLignes - nbLignes;
    rewind(fichier);

    for(int i = 0; i < debutLignes; i++)
        fgets(ligne, MAX_LIGNE, fichier);
    while(fgets(ligne, MAX_LIGNE, fichier) != NULL)
        printf("%s", ligne);
    printf("\n");

    fclose(fichier);

    return EXIT_SUCCESS;
}
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    FILE* fichier;
    struct stat buf;
    char *nom = argv[2];
    long nbLignes;
    long totalLignes = 0;
    long debutLignes;
    char c;

    if(argc != 3){
        fprintf(stderr, "Arguments manquants ou en trop\n");
        return EXIT_FAILURE;
    }

    if((nbLignes = strtol(argv[1], NULL, 10)) <= 0){
        fprintf(stderr, "Argument invalide\n");
        return EXIT_FAILURE;
    }

    stat(nom, &buf);
    if((fichier = fopen(argv[2], "r")) == NULL || S_ISDIR(buf.st_mode)){
        fprintf(stderr, "Fichier introuvable\n");
        return EXIT_FAILURE;
    }

    while((c = fgetc(fichier)) != EOF)
        if(c == '\n') ++totalLignes;
    debutLignes = ++totalLignes - nbLignes;
    rewind(fichier);

    for(int i = 0; i < debutLignes; ++i)
        while((c = fgetc(fichier)) != '\n');

    while((c = fgetc(fichier)) != EOF)
        printf("%c", c);
    printf("\n");

    fclose(fichier);

    return EXIT_SUCCESS;
}
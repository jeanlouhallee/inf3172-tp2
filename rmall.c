#include <fts.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    FTS *contenu;
    FTSENT *fichier;
    char *nom[2] = {argv[1], NULL};

    if(argc != 2){
        fprintf(stderr, "Nom de repertoire manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if(access(nom[0], F_OK) == -1){
        fprintf(stderr, "Répertoire introuvable\n");
        return EXIT_FAILURE;
    }

    contenu = fts_open(nom, FTS_NOCHDIR, 0);
    while((fichier = fts_read(contenu))){
        if(access(fichier->fts_path, W_OK) == -1){
            fprintf(stderr, "Permissions insuffisantes\n");
            fts_close(contenu);
            return EXIT_FAILURE;
        }
    }
    fts_close(contenu);

    contenu = fts_open(nom, FTS_NOCHDIR, 0);
    while((fichier = fts_read(contenu))){
        if(fichier->fts_info != FTS_D)
            remove(fichier->fts_path);
    }
    fts_close(contenu);

    printf("Répertoire supprimé\n");

    return EXIT_SUCCESS;
}
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fts.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    FTS *contenu;
    FTSENT *fichier;
    struct stat buf;
    char *nom[2] = {argv[1], NULL};
    int nbFichiers = 0;
    int taille = 0;

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
        stat(fichier->fts_path, &buf);
        if(!S_ISDIR(buf.st_mode)){
            nbFichiers++;
            taille += buf.st_size;
        }
    }
    fts_close(contenu);

    printf("Le répertoire %s contient %d fichiers pour un total de %d octets.\n", nom[0], nbFichiers, taille);

    return EXIT_SUCCESS;
}
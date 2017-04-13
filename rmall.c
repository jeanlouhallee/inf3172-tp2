/*
 * rmall.c : Supprime un repertoire et tout son contenu
 *
 * TP2 : Conception d'un shell
 *
 * Cours : INF3172 Systeme d'exploitation
 *
 * Auteurs : Etienne Bergeron BERE08089101
 *           Jean-Lou Hallee  HALJ05129309
 *
 * Dernières modifications : 16 avril 2017
 */

#include <fts.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    FTS *contenu;
    FTSENT *fichier;
    struct stat buf;
    char *nom[2] = {argv[1], NULL};

    if(argc != 2){
        fprintf(stderr, "Nom de repertoire manquant ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    stat(nom[0], &buf);
    if(access(nom[0], F_OK) == -1 || !S_ISDIR(buf.st_mode)){
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
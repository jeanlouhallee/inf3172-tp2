/*
 * newdir.c : Cree un nouveau repertoire
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
/*
 * new.c : Cree un nouveau fichier
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

    printf("Fichier créé\n");

    return EXIT_SUCCESS;
}
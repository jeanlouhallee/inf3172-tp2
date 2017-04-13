/*
 * list.c : Affiche la liste des fichiers ou repertoires dans le repertoire courant
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
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    DIR* dir;
    struct dirent *ent;
    char cwd[1024];
    
    if(argc > 2 || (argc == 2 && strcmp(argv[1], "-d") != 0)){
        fprintf(stderr, "Option invalide ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if((dir = opendir(".")) == NULL){
        perror("Erreur d'ouverture de repertoire : ");
        return EXIT_FAILURE;
    }

    getcwd(cwd, sizeof(cwd));

    if(argc == 2){
        printf("Sous-répertoires de %s\n", cwd);
        while((ent = readdir(dir)) != NULL){
            if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
                printf("%s\n", ent->d_name);
        }
    }else{
        printf("Fichiers de %s\n", cwd);
        while((ent = readdir(dir)) != NULL){
            if(ent->d_type != DT_DIR)
                printf("%s\n", ent->d_name);
        }
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
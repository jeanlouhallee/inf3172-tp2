#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    DIR* dir;
    struct dirent *ent;
    
    if(argc > 2 || (argc == 2 && strcmp(argv[1], "-d") != 0)){
        fprintf(stderr, "Option invalide ou arguments en trop\n");
        return EXIT_FAILURE;
    }

    if((dir = opendir(".")) == NULL){
        perror("Erreur d'ouverture de repertoire : ");
        return EXIT_FAILURE;
    }

    while((ent = readdir(dir)) != NULL){
        if(argc == 2){
            if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
                printf("%s\n", ent->d_name);
        }else{
            if(ent->d_type != DT_DIR)
                printf("%s\n", ent->d_name);
        }    
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
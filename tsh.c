/*
 * tsh.c : Turbo-Shell
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

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 128 // Longueur maximale des chaines de caracteres

/*
 * Affiche le chemin absolu du répertoire courant
 * 
 * @return void
 */
void cdir(){
    char dir[MAX_SIZE];
    if(getcwd(dir, sizeof(dir)) == NULL){
        perror("Impossible de lire le chemin du répertoire courant ");
    } else{
        printf("Repertoire courant : %s\n", dir);
    }
}

/*
 * Change le repertoire de travail courant
 *
 * @param argv : chemin du repertoire cible
 * 
 * @return void
 */
void cd(char *argv){
    if(chdir(argv) == -1){
        perror("Repertoire introuvable ");
    }
}

/*
 * Permet d'obtenir le chemin absolu du repertoire de travail courant
 *
 * @param path : chaine de caracteres qui contiendra le chemin resultant
 * 
 * @return void
 */
void getPath(char path[]){
    if(getcwd(path, sizeof(char) * MAX_SIZE) == NULL){
        perror("Impossible de lire le chemin du répertoire courant ");
    } else{
        strcat(path, "/"); 
    }
}

/*
 * Separe la chaine de caracteres lue en ligne de commande en ses arguments
 *
 * @param line : chaine de caracteres lue en ligne de commande
 * @param argv : tableau contenants les differents arguments
 * @param nbToken : nombre d'arguments
 * 
 * @return void
 */
void parse(char *line, char *argv[], int nbToken){   
    char *delimiter = " \n\t";
    char *token = strtok(line, delimiter);

    for(int i = 0; i < nbToken; ++i){
        argv[i] = token;
        token = strtok(NULL, delimiter);
    }
    argv[nbToken] = NULL;
}

/*
 * Cree et execute un processus enfant
 *
 * @param argv : tableau des arguments de la ligne de commande
 * @param path : chemin absolu du repertoire de travail courant
 * 
 * @return void
 */
void execute(char *argv[], char *path){
    pid_t pid;
    int status;
    char *envp[] = {NULL};
    char exec[MAX_SIZE];
    strcpy(exec, path);
    strcat(exec, argv[0]);

    if((pid = fork()) < 0){
        perror("Erreur de creation de processus "); 
        exit(1);
    }else if(pid == 0){
        if(execve(exec, argv, envp) < 0){
            perror("Erreur d'execution de processus "); 
            exit(1);
        }
    }else{
        while (wait(&status) != pid);
    }
}

int main(void){
    int  exit = 0;
    char line[MAX_SIZE] = {};
    char path[MAX_SIZE] = {};
    getPath(path);

    while(!exit){
        printf("tsh > ");

        if(fgets(line, sizeof(line), stdin) != NULL){   
            int nbToken = 1;
            for(int i = 0; line[i] != '\0'; ++i)
                if(line[i] == ' ') ++nbToken;

            char *argv[nbToken + 1];
            parse(line, argv, nbToken);

            if(argv[0] != NULL){
                if(strcmp(argv[0], "exit") == 0){
                    exit = 1;
                }else if(strcmp(argv[0], "cdir") == 0){
                    cdir();
                }else if(strcmp(argv[0], "cd") == 0){
                    if(nbToken != 1){
                        cd(argv[1]);
                    }
                }else{ 
                    execute(argv, path);
                }
            }
        }
    }

    return 0;
}
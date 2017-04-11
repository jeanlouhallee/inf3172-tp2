#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 128

void getPath(char path[]){
    if(getcwd(path, sizeof(char) * MAX_SIZE) == NULL){
        perror("Can't get working directory.\n");
    } else{
        strcat(path, "/"); 
    }
}
void cdir(){
    char dir[MAX_SIZE];
    if(getcwd(dir, sizeof(dir)) == NULL){
        perror("Can't get working directory.\n");
    } else{
        printf("Repertoire courant : %s\n", dir);
    }
}
void cd(char *argv){
    if(chdir(argv) == -1){
        perror("Repertoire introuvable.\n");
    }
}

void parse(char *line, char *argv[], int nbToken){   
    char* delimiter = " \n\t";
    
    char *token = strtok(line, delimiter);

    for(int i = 0; i < nbToken; ++i){
        argv[i] = token;
        token = strtok(NULL, delimiter);
    }
    argv[nbToken] = NULL;

    return;
}

void execute(char **argv, char *path){
    pid_t pid;
    int status;
    char *envp[] = {NULL};
    char exec[MAX_SIZE];
    strcpy(exec, path);
    strcat(exec, argv[0]);

    if((pid = fork()) < 0){
        //perror("Erreur de fork\n"); 
        printf("%s\n", strerror(errno));
        exit(1);
    }else if(pid == 0){
        if(execve(exec, argv, envp) < 0){
            //perror("Erreur de execve.\n"); 
            printf("%s\n", strerror(errno));
            exit(1);
        }
    }else{
        while (wait(&status) != pid);
    }

    return;
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
                if(line[i]==' ') ++nbToken;

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
}

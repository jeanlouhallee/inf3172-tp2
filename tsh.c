#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void tokenize(char *string, char *newArgv[], int nbToken){
    int index = 0;
    char *token;
    char *exec;
    for(int i = 0; i <= nbToken; ++i){
        newArgv[i] = calloc(20, sizeof(char));
    }
    token = strtok(string, " ");
    exec = token;
    while(token != NULL){
        token = strtok(NULL, " ");
        newArgv[index] = token;
        ++index;
    }
    newArgv[nbToken] = "NULL";
    for(int i = 0; i <= nbToken; ++i){
        if(newArgv[i] != NULL){
            printf("ARGV: %s\n", newArgv[i]);
        }else{
            printf("ARGV: NULLL\n");
        }
    }
    exec[strlen(exec)] = '\0';
    string = exec;
}

int main(void){
    pid_t id;
    int nbToken;
    //int statut;
    char *allo[] = {NULL, "-d", NULL};
    char input[56];
    char path[56];
    char *envp[] = {NULL};

    while(1){
        printf("tsh> ");

        char *exe = fgets(input, sizeof(input), stdin);
        
        if(exe != NULL && strcmp(exe, "\n")){
            exe[strlen(input) - 1] = '\0';
            if(!strcmp(input, "exit")) exit(0);
            char *temp = malloc(sizeof(char) * strlen(exe));
            strcpy(temp, exe);
        
            for(nbToken = 0; temp[nbToken]; temp[nbToken]==' ' ? ++nbToken : *temp++);
        
            char *newArgv[nbToken + 1];
            tokenize(exe, newArgv, nbToken);

            if(strcmp(exe, "\0")){
                memset(path, 0, sizeof(path));
                strcpy(path, "/home/jon/inf3172/bin/");
                strcat(path, input);
                id = fork();
                if(id != 0){
                    wait(NULL);

                }else{
                    if(execve(path, allo, envp) == -1){
                        printf("Commande introuvable.\n");
                        kill(getpid(), SIGKILL);
                    }
                } 
            }
        }
    }
    printf("Process %d terminating.\n", getpid());
    return 0;
}


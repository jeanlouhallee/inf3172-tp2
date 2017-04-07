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
    for(int i = 0; i < nbToken; ++i){
        tokens[i] = calloc(20, sizeof(char));
    }
    token = strtok(string, " ");
    tokens[index] = token;
    ++index;
    printf("Token: %s\n", token);
    while(token != NULL){
        token = strtok(NULL, " ");
        tokens[index] = token;
        printf("Token: %s\n", token);
        ++index;
    }
    for(int i = 0; i <= nbToken; ++i){
        printf("%s\n", tokens[i]);
    }
    
}

int main(int argc, char *argv[]){
    pid_t id;
    int nbToken;
    int statut;
    char *temp;
    char input[56];
    char path[56];
    char *newArgv[];
    char *envp[] = {NULL};

    while(1){
        printf("tsh> ");
        char *exe = fgets(input, sizeof(input), stdin);
        strcpy(temp, exe);
        for(nbToken = 0; temp[nbToken]; temp[nbToken]==' ' ? ++nbToken : *temp++);
        
        char *tokens[nbToken + 1];
        printf("Nb de token: %d\n", nbToken);
        printf("test1\n");
    
        tokenize(exe, tokens, nbToken);


        if(exe != NULL){
            exe[strlen(input) - 1] = '\0';
            if(!strcmp(input, "exit")) exit(0);
            
            if(strcmp(exe, "\0")){
                memset(path, 0, sizeof(path));
                strcpy(path, "/home/jon/inf3172/bin/");
                strcat(path, input);
                id = fork();
                if(id != 0){
                    wait(NULL);

                }else{
                    if(execve(path, newArgv, envp) == -1){
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


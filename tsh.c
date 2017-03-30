#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t id;
    int statut;
    char input[56];
    char path[56];
    char *newArgv[] = {NULL};
    char *envp[] = {NULL};
    
    while(1){
        printf("tsh> ");
        char *exe = fgets(input, sizeof(input), stdin);
        
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t id;
    int statut;
    char commande[56];
    char *newArgv[] = {NULL};
    char *envp[] = {NULL};
    while(1){
        printf("tsh> ");
        char *exe = fgets(commande, sizeof(commande), stdin);
        
        if(exe != NULL){
            exe[strlen(commande) - 1] = '\0';
            if(!strcmp(commande, "exit")) exit(0);
            
            if(strcmp(exe, "\0")){
                id = fork();

                if(id != 0){
                    wait(NULL);

                }else{
                    if(execve(commande, newArgv, envp) == -1){
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


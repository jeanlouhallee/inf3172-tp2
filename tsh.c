#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

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
            id = fork();

            if(!strcmp(commande, "exit")) exit(0);

            if(id != 0){
                printf("Parent: %d \n", getpid());
                wait(NULL);
            }else{
                printf("Enfant: %d\n", getpid());
                if(execve(commande, newArgv, envp) == -1){
                    kill(getpid(), SIGKILL);
                }
            }
            //free(commande);
            //system("ps");
            //system("ps");
            
        }
    }
    printf("Process %d terminating.\n", getpid());
    return 0;
}


#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void cd(char *argv){
    if(chdir(argv) == -1){
        printf("%s\n", strerror(errno));
    }
}

void parse(char *line, char *argv[], int nbToken){   
    char* delimiter = " \n\t";
    
    char *token = strtok(line, delimiter);

    for(int i = 0; i < nbToken; ++i){
        argv[i] = token;
        token = strtok(NULL, delimiter);

        //printf("ARGV %d : %s\n", i, argv[i]);
    }
    argv[nbToken] = NULL;

    return;
}

void execute(char **argv){
    pid_t pid;
    int status;
    char *envp[] = {"PATH=/home/jon/inf3172/bin", NULL};

    if((pid = fork()) < 0){
        //perror("Erreur de fork\n"); //
        printf("%s\n", strerror(errno));
        exit(1);
    }else if(pid == 0){
        if(execve(argv[0], argv, envp) < 0){
            //perror("Erreur de execve.\n"); //
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
    char line[1024];
    char dir[1024];

    while(!exit){
        if(getcwd(dir, sizeof(dir)) == NULL){
            perror("Problem with curring working directory.\n");
        }
        printf("tsh %s> ", dir);

        if(fgets(line, sizeof(line), stdin) != NULL){   
            int nbToken = 1;
            for(int i = 0; line[i] != '\0'; ++i)
                if(line[i]==' ') ++nbToken;

            char *argv[nbToken + 1];

            parse(line, argv, nbToken);

            if(argv[0] != NULL){
                if(strncmp(argv[0], "exit", 4) == 0)
                    exit = 1;
                else if(strncmp(argv[0], "cd", 2) == 0)
                    cd(argv[1]);
                else 
                    execute(argv);
            }
        }
    }
}

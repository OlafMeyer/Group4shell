#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#define BUFFER_SIZE 1<<16
#define ARR_SIZE 1<<16


void pipe_cmd(char** cmd1, char** cmd2, int pfd[]) {
    int pid;

    switch (pid = fork()) {

    case 0: /* child */
        dup2(pfd[0], 0);
        close(pfd[1]);  /* the child does not need this end of the pipe */
        execvp(cmd2[0], cmd2);
        perror(cmd2[0]);

    default: /* parent */
        dup2(pfd[1], 1);
        close(pfd[0]);  /* the parent does not need this end of the pipe */
        execvp(cmd1[0], cmd1);
        perror(cmd1[0]);

    case -1:
        perror("fork");
        exit(1);
    }
}

void red_cmd(char** cmd1, char** cmd2, int pfd[]) {
    int pid;

    switch (pid = fork()) {

    case 0:
        dup2(pfd[0],1);
        execvp(cmd1[0], cmd1);

    case -1:
        perror("fork");
        exit(1);
    }
}

void parse_args(char *buffer, char** args, size_t args_size, size_t *nargs)
{
    char *buf_args[args_size];
    char **cp;
    char *wbuf;
    size_t i, j;
    
    wbuf=buffer;
    buf_args[0]=buffer; 
    args[0] =buffer;
    
    for(cp=buf_args; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
        if ((*cp != '\0') && (++cp >= &buf_args[args_size]))
            break;
    }
    
    for (j=i=0; buf_args[i]!=NULL; i++){
        if(strlen(buf_args[i])>0)
            args[j++]=buf_args[i];
    }
    

    *nargs=j;
    args[j]=NULL;
}




int main(int argc, char *argv[], char *envp[]){
    char buffer[BUFFER_SIZE];
    char *args[ARR_SIZE];

    int *ret_status;
    size_t nargs;
    pid_t pid;
    int a, b, k;
    char *command1[100];
    char *command2[100];
    int fd[2];
    FILE *foutput;

    pipe(fd);
    
    while(1){
        printf("[MY_SHELL]$ ");
        fgets(buffer, BUFFER_SIZE, stdin);
        parse_args(buffer, args, ARR_SIZE, &nargs); 

        if (nargs==0) continue;
        if (!strcmp(args[0], "exit" )) exit(0);       
        pid = fork();
        if (pid){
            //printf("Waiting for child (%d)\n", pid);
            pid = wait(ret_status);
            //printf("Child (%d) finished\n", pid);
        } else {
            int split = -1;
            for(a=0; args[a]!=NULL; a++){
                if(strstr (args[a], "|") != NULL ||
                   strstr (args[a], ">") != NULL ){
                    split = a;

                    for(b=0; b<split; b++)
                       command1[b] = args[b];
                    int num=0;
                    for(k=split+1; args[k]!=NULL; k++){
                        command2[num] = args[k];
                        num++;
                    }
                    command1[split] = NULL;
                    command2[num+1] = NULL;
                    if(strstr (args[a], "|") != NULL) {
                        pipe_cmd(command1, command2, fd);
                    }
                    if(strstr (args[a], ">") != NULL) {
                        foutput = fopen(args[a+1], "w");
                        fd[0] = fileno(foutput);
                        red_cmd(command1, command2, fd);
                    }
                    
                }
            }
            if( execvp(args[0], args)) {
                puts(strerror(errno));
                exit(127);
            }
        }
    }    
    return 0;
}
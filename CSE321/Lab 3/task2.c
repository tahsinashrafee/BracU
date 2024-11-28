#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg{
	long int type;
	char txt[6];
};



int main(){
        char workspace[100];
        char txt[100];
        int id;
        struct msg message;
        id=msgget((key_t)12,0666|IPC_CREAT);
        
        printf("Please enter the workspace name:\n");
        scanf("%s", workspace);

        if (strcmp(workspace, "cse321")) {
        printf("Invalid workspace name\n");
        return 0;
        }
        pid_t pid = fork();

        if (pid == 0) {
          msgrcv(id,(void *)&message,sizeof(message.txt),1,IPC_NOWAIT);
          
          printf("OTP generator received workspace name from log in: %s\n\n", message.txt);
          
          pid_t otp = getpid();
          sprintf(txt, "%d", otp);
          message.type=9;
          strcpy(message.txt,txt);
          msgsnd(id,(void *)&message,sizeof(message.txt),0);
          printf("OTP sent to log in from OTP generator: %s\n", txt);
        
          pid_t child_pid = fork();

          if (child_pid == 0) {
              msgrcv(id,(void *)&message,sizeof(message.txt),7,IPC_NOWAIT);
              message.type=8;
              msgsnd(id,(void *)&message,sizeof(message.txt),0);
              printf("OTP sent to log in from mail: %s\n", message.txt);

          } else {
              message.type=7;
              strcpy(message.txt,txt);
              msgsnd(id,(void *)&message,sizeof(message.txt),0);
              printf("OTP sent to mail from OTP generator: %s\n", txt);
              wait(NULL);
          }
        }
        else {
            message.type=1;
            strcpy(message.txt,workspace);
            msgsnd(id,(void *)&message,sizeof(message.txt),0);
            printf("Workspace name sent to otp generator from log in: %s\n\n", workspace);
            wait(NULL);
            
            msgrcv(id,(void *)&message,sizeof(message.txt),9,IPC_NOWAIT);
            char* otp_g = (char*)malloc(sizeof(message.txt) + 1);
            strncpy(otp_g, message.txt, sizeof(message.txt));
            printf("Log in received OTP from OTP generator: %s\n", message.txt);
            
            msgrcv(id,(void *)&message,sizeof(message.txt),8,IPC_NOWAIT);
            char* otp_m = (char*)malloc(sizeof(message.txt) + 1);
            strncpy(otp_m, message.txt, sizeof(message.txt));
            printf("Log in received OTP from mail: %s\n", message.txt);
            
            if (strcmp(otp_g, otp_m) == 0) {
              printf("OTP Verified\n");
            } 
            else {
                printf("OTP Incorrect\n");
            }
            
          }

	return 0;
}


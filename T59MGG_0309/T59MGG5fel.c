#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void pr_exit(int status);

int main(void)
{
	int status;
	pid_t	pid;
	if(pid=fork()<0)
		perror("fork error");
	else if(pid==0){
		if(execl("./child.out","child",(char*)NULL)<0)
			perror("execl error");
	}
	if(waitpid(pid,	NULL,0)<0)
		perror("wait error");

	if((pid=fork())<0) perror("fork hiba");
        else if(pid==0)
                exit(7);
        if(wait(&status)!=pid) perror("wait hiba");
        if(WIFSIGNALED(status))
                printf("Normalis befejezodes, a visszaadott ertek = %d\n",WEXITSTATUS(status));




	if((pid=fork())<0) perror("fork hiba");
	else if(pid==0)
		abort();
	if(wait(&status)!=pid) perror("wait hiba");
	if(WIFSIGNALED(status))
		printf("abnormalis befejeződés a szignál a sorszama = %d  \n",WEXITSTATUS(status));


	exit(0);
}


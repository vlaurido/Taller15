#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFLEN 1000000

int main(int argc, char* argv[]){
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Fallo de fork\n");
        exit(1);
    }
    if (pid > 0) {
        printf("Id del proceso hijo: %d\n",pid);
        exit(0);
    }

    umask(0);

    int fd = open("log_cpu.log", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    int sid = setsid();
    if (sid < 0) {
        exit(1);
    }

    close(0);
    close(1);
    close(2);

    while(1) {
        void *buf = malloc(BUFLEN*sizeof(void *));

        FILE *fp = popen("top -bn2 | grep '%Cpu' | tail -1", "r");
        fread(buf,100,1,fp);

        write(fd,buf,strlen(buf));
    }

    return 0;
}
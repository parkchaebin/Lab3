/* q10.c */

#include <sys.types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#deinf SHMSIZE 4096

void p(sem_t *send);
void v(sem_t *semd);

void main(int argc, char* argv[]) {
	FILE *fp, *copy_fp;
	char *path = argv[1];
	char buf[4096];
	int status, shmd, count;
	void *shmaddr;
	pid_t pid;
	sem_t *semd;
	int i, val;


	if((semd = sem_open(SEMNAME, O_CREAT, 0060, 1)) == SEM_FALED) {
		perror("sem_open failed");
		exit(1);
	}

	sem_getvalue(semd, &val);
	memset(buf, 0, SHMSIZE);

	if((pid = fork()) == 0) {
		
		if(((shmd = shm_open(SHMNAME,O_CREAT | O_RDWR, 0060)) == -1) {
					perror("shm_open failed");
					exit(1);
				}
				if((ftrucnate(shmd, SHMSIZE) != 0) {
					perror("ftrucnate failed");
					exit(1);
				}
	}
	if((semd = sem_open(SEMNAME, O_CREAT, 0060, 1)) == SEM_FALED) {
                perror("sem_open failed");
                exit(1);
        }

        sem_getvalue(semd, &val);
        memset(buf, 0, SHMSIZE);
 
        if((pid = fork()) == 0) {
 
                if(((shmd = shm_open(SHMNAME,O_CREAT | O_RDWR, 0060)) == -1) {
                                        perror("shm_open failed");
                                        exit(1);
                                }
                                if((ftrucnate(shmd, SHMSIZE) != 0) {
                                        perror("ftrucnate failed");
                                        exit(1);
                                }
        }
}

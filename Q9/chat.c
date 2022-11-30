#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	mpd_t qd;
	struct mq_attr q_attr;
	char send_data[32];
	int status;
	pid_t pid;

	q_attr.dq_maxmsg = 10;
	q_attr.mq_msgsize = 32;

	while(1) {
		if((pid = fork())== 0) {
			
			memset(send_data, 0, 32);
			printf("Enter : ");
			scanf("%[^\n]", &send_data);

			if(((qd = mq_open("/MY_QUEUE", O_RDWR | O_NONBLOCK, 0600, NULL)) == -1) {
						perror("faild");
						exit(1);
					}
					q_attr.dq_flags = 0;

					if(mq_setattr(qd, &q_attr, NULL)) {
						exit(1);
					}
					if(mq_getattr(qd, &old_q_attr)) {
						perror("faild");
						exit(1);
					}

					if(!(old_q_attr.mq_flags & O_NONBLOCK));

					if((mq_receive(qd, recv_data, 32, &prio) == -1) {
							perror("failed");
							exit(1);
						}
		}
	}
}

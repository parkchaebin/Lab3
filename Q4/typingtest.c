/* typingtest.c */

#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void result(int time1, int time2, char text1[], int errcnt){
	int time_tmp;
	float typing_time;

	time_tmp = time2 - time1;
	printf("걸린 시간 : %d초\n", time_tmp);

	typing_time = ((strlen(text1) - errcnt) / time_tmp) * 60;
	printf("분당타수 : %.lf타\n", typing_time);
}

int main(void)
{
	int fd;
	int nread, cnt=0, errcnt=0;
	char ch, text[] = "The magic thing is that you can change it.";
	struct termios init_attr, new_attr;
	time_t time1, time2;
	fd = open(ttyname(fileno(stdin)), O_RDWR);
	tcgetattr(fd, &init_attr);
	
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO; 
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	
	if (tcsetattr(fd, TCSANOW, &new_attr) != 0) {
		fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
	}
	
	time(&time1);

	printf("다음 문장을 그대로 입력하세요.\n%s\n", text);
	while ((nread=read(fd, &ch, 1)) > 0 && ch != '\n') {
		if (ch == text[cnt++])
			write(fd, &ch, 1);
		else {
			write(fd, "*", 1);
			errcnt++;
		}
	}
	
	printf("\n타이핑 오류의 횟수는 %d\n", errcnt);
	time(&time2);
	tcsetattr(fd,TCSANOW, &init_attr);
	close(fd);

	result(time1, time2,text,  errcnt);

}

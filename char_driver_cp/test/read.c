#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

#define DATA_NUM 32

int main(void){
	int fd,i;
	int r_len, w_len;
	fd_set fdset;
	char rbuf[DATA_NUM];
	memset(rbuf, 0, DATA_NUM);
	fd = open("/dev/ychar_dev", O_RDWR);
	if (fd==-1){
		perror("open file error.");
		return -1;
	}
	else {
		printf("open succeed");		
	}
	r_len = read(fd, rbuf, DATA_NUM);
	if(r_len==-1){
		perror("read error.\n");
		return -1;
	}
	printf("read lenght is: %d\n", r_len);
	printf("Read buf: %s\n", rbuf);
	close(fd);
	return 0;
}
